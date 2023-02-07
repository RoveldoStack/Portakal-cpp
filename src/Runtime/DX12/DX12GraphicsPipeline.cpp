#include "DX12GraphicsPipeline.h"
#include <Runtime/DX12/DX12PipelineUtils.h>
#include <Runtime/DX12/DX12Device.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/DX12/DX12Shader.h>
#include <Runtime/Graphics/PipelineUtils.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	DX12GraphicsPipeline::DX12GraphicsPipeline(const GraphicsPipelineCreateDesc& desc, DX12Device* pDevice) : Pipeline(desc)
	{
		ID3D12Device* pDXDevice = pDevice->GetDXDevice();

		/*
		* Start creating root signature
		*/
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		Array<D3D12_ROOT_PARAMETER> rootParameters;
		Array<D3D12_DESCRIPTOR_RANGE*> descriptorRangeCache;
		Array<D3D12_STATIC_SAMPLER_DESC> staticSamplers;

		/*
		* Create root parameters using table entries
		*/
		for (unsigned int tableIndex = 0; tableIndex < desc.ResourceState.Slots.GetCursor(); tableIndex++)
		{
			const PipelineResourceTableDesc& table = desc.ResourceState.Slots[tableIndex];
			unsigned int currentStageConstantBufferCount = 0;
			unsigned int currentStageTextureCount = 0;
			unsigned int currentStageSamplerCount = 0;

			/*
			* Count table resources
			*/
			for (unsigned int resourceIndex = 0; resourceIndex < table.Slots.GetCursor(); resourceIndex++)
			{
				const PipelineResourceEntry& resourceSlot = table.Slots[resourceIndex];


				switch (resourceSlot.Type)
				{
					case Portakal::PipelineResourceType::ConstantBuffer:
					{
						currentStageConstantBufferCount++;
						break;
					}
					case Portakal::PipelineResourceType::TextureReadOnly:;
					case Portakal::PipelineResourceType::TextureReadWrite:
					{
						currentStageTextureCount++;
						break;
					}
					case Portakal::PipelineResourceType::Sampler:
					{
						currentStageSamplerCount++;
						break;
					}
					default:
						break;
				}

				/*
				* Create descriptor range cache
				*/
				const unsigned int descriptorRangeCount = (currentStageConstantBufferCount != 0 ? 1 : 0) + (currentStageTextureCount != 0 ? 1 : 0) + (currentStageSamplerCount != 0 ? 1 : 0);

				D3D12_DESCRIPTOR_RANGE* pDescriptorRanges = descriptorRangeCount == 0 ? nullptr : new D3D12_DESCRIPTOR_RANGE[descriptorRangeCount];

				if (pDescriptorRanges != nullptr)
					descriptorRangeCache.Add(pDescriptorRanges);

				/*
				* Start creating root parameter
				*/
				D3D12_ROOT_PARAMETER rootParameter = {};
				rootParameter.ShaderVisibility = DX12PipelineUtils::GetShaderStageVisibility(table.Stage);
				rootParameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;

				/*
				* Create descriptor table
				*/
				D3D12_ROOT_DESCRIPTOR_TABLE descriptorTable = {};

				/*
				* Create constant buffer range
				*/
				unsigned int descriptorRangeIndex = 0;
				if (currentStageConstantBufferCount > 0)
				{
					D3D12_DESCRIPTOR_RANGE& range = pDescriptorRanges[descriptorRangeIndex];
					range.NumDescriptors = currentStageConstantBufferCount;
					range.BaseShaderRegister = 0;
					range.RegisterSpace = 0;
					range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
					range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;

					descriptorRangeIndex++;
				}
				
				/*
				* Create texture range
				*/
				if (currentStageTextureCount > 0)
				{
					D3D12_DESCRIPTOR_RANGE& range = pDescriptorRanges[descriptorRangeIndex];
					range.NumDescriptors = currentStageTextureCount;
					range.BaseShaderRegister = 0;
					range.RegisterSpace = 0;
					range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
					range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;

					descriptorRangeIndex++;
				}

				/*
				* Create sampler range
				*/
				if (currentStageSamplerCount > 0)
				{
					if (currentStageTextureCount > 0)
					{
						D3D12_DESCRIPTOR_RANGE& range = pDescriptorRanges[descriptorRangeIndex];
						range.NumDescriptors = currentStageSamplerCount;
						range.BaseShaderRegister = 0;
						range.RegisterSpace = 0;
						range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
						range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;

						descriptorRangeIndex++;
					}
				}

				descriptorTable.NumDescriptorRanges = descriptorRangeCount;
				descriptorTable.pDescriptorRanges = pDescriptorRanges;

				rootParameter.DescriptorTable = descriptorTable;

				rootParameters.Add(rootParameter);
			}

		}

		rootSignatureDesc.NumParameters = rootParameters.GetCursor();
		rootSignatureDesc.pParameters = rootParameters.GetData();
		rootSignatureDesc.NumStaticSamplers = 0;
		rootSignatureDesc.pStaticSamplers = nullptr;

		/*
		* Serialize root signature
		*/
		ASSERT(SUCCEEDED(D3D12SerializeRootSignature(
			&rootSignatureDesc,
			D3D_ROOT_SIGNATURE_VERSION_1,
			&mRootSignatureBlob, &mRootSignatureErrorBlob)), "DX12Pipeline failed to serialize the signature blob with logs: %s", (const char*)mRootSignatureBlob->GetBufferPointer());

		/*
		* Create root signature
		*/
		ASSERT(SUCCEEDED(pDXDevice->CreateRootSignature(0, mRootSignatureBlob->GetBufferPointer(), mRootSignatureBlob->GetBufferSize(), IID_PPV_ARGS(mRootSignature.GetAddressOf()))), "DX12Pipeline", "Failed to create a root signature");

		/*
		* Clean up descriptor table ranges
		*/
		for (unsigned int i = 0; i < descriptorRangeCache.GetCursor(); i++)
		{
			delete descriptorRangeCache[i];
		}

		/*
		* Create input layout
		*/
		unsigned char semanticCache[(unsigned int)InputElementSemantic::Color];
		for (unsigned char i = 0; i < (unsigned char)InputElementSemantic::Color; i++)
			semanticCache[i] = 0;

		D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};

		Array<D3D12_INPUT_ELEMENT_DESC> inputElements;
		Array<InputElementDesc> inputElementDescs = desc.InputLayout.Elements; // TODO: implement multiple input layouts
		Array<String> semanticTextCache;
		unsigned int offset = 0;

		for (unsigned int i = 0; i < inputElementDescs.GetCursor(); i++)
		{
			const InputElementDesc& inputElementDesc = inputElementDescs[i];
			
			const String semanticText = DX12PipelineUtils::GetInputElementSemanticName(inputElementDesc.Semantic);
			semanticTextCache.Add(semanticText);

			D3D12_INPUT_ELEMENT_DESC inputElement
			{
				*semanticTextCache[i],
				semanticCache[(unsigned int)inputElementDesc.Semantic],
				DXGIUtils::GetInputElementFormat(inputElementDesc.Format),
				0,
				offset,
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
				desc.InputLayout.InstanceStepRate
			};

			semanticCache[(unsigned int)inputElementDesc.Semantic]++;

			offset += PipelineUtils::GetInputElementDataSize(inputElementDesc.Format);

			inputElements.Add(inputElement);
		}

		inputLayoutDesc.NumElements = inputElements.GetCursor();
		inputLayoutDesc.pInputElementDescs = inputElements.GetData();

		/*
		* Start creating pso
		*/
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};

		for (unsigned int i = 0; i < desc.Shaders.GetCursor(); i++)
		{
			const DX12Shader* pShader = (const DX12Shader*)desc.Shaders[i];

			ID3DBlob* pBlob = pShader->GetDXShaderBlob();

			D3D12_SHADER_BYTECODE  byteCode = {};
			byteCode.pShaderBytecode = pBlob->GetBufferPointer();
			byteCode.BytecodeLength = pBlob->GetBufferSize();

			switch (pShader->GetStage())
			{
				case Portakal::ShaderStage::None:
					ASSERT(false, "DX12Pipeline", "Invalid shader stage for GraphicsPipeline!");
					break;
				case Portakal::ShaderStage::Vertex:
				{
					psoDesc.VS = byteCode;
					break;
				}
				case Portakal::ShaderStage::Fragment:
				{
					psoDesc.PS = byteCode;
					break;
				}
				case Portakal::ShaderStage::TesellationEval:
				{
					psoDesc.DS = byteCode;
					break;
				}
				case Portakal::ShaderStage::TesellationControl:
				{
					psoDesc.HS = byteCode;
					break;
				}
				default:
					ASSERT(false, "DX12Pipeline", "Invalid unknown shader stage for GraphicsPipeline!");
					break;
			}
		}

		/*
		* Set input layout
		*/
		psoDesc.InputLayout = inputLayoutDesc;

		/*
		* Set root signature
		*/
		psoDesc.pRootSignature = mRootSignature.Get();

		/*
		* Set output desc
		*/
		psoDesc.NumRenderTargets = desc.OutputDesc.ColorAttachments.GetCursor();
		for (unsigned int i = 0; i < desc.OutputDesc.ColorAttachments.GetCursor(); i++)
		{
			psoDesc.RTVFormats[i] = DXGIUtils::GetTextureFormat(desc.OutputDesc.ColorAttachments[i].Format);
		}
		psoDesc.DSVFormat = desc.OutputDesc.DepthStencilAttachment.Format == TextureFormat::None ? DXGI_FORMAT_UNKNOWN : DXGIUtils::GetTextureFormat(desc.OutputDesc.DepthStencilAttachment.Format);

		/*
		* Set reasterizer state
		*/
		D3D12_RASTERIZER_DESC rasterizerStateDesc = {};
		rasterizerStateDesc.FrontCounterClockwise = desc.RasterizerState.FrontFace == FrontFaceDirection::CounterClockwise;
		rasterizerStateDesc.CullMode = DX12PipelineUtils::GetCullMode(desc.RasterizerState.CullMode);
		rasterizerStateDesc.FillMode = DX12PipelineUtils::GetFillMode(desc.RasterizerState.ShadeMode);
		rasterizerStateDesc.AntialiasedLineEnable = false;
		rasterizerStateDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
		rasterizerStateDesc.DepthBias = 0;
		rasterizerStateDesc.DepthBiasClamp = 0;
		rasterizerStateDesc.DepthClipEnable = desc.RasterizerState.bDepthClipEnabled;
		rasterizerStateDesc.ForcedSampleCount = 0;
		rasterizerStateDesc.MultisampleEnable = false;
		rasterizerStateDesc.SlopeScaledDepthBias = 0;

		psoDesc.RasterizerState = rasterizerStateDesc;

		/*
		* Set depth stencil state
		*/
		D3D12_DEPTH_STENCIL_DESC depthStencilStateDesc = {};
		depthStencilStateDesc.DepthEnable = desc.DepthStencilState.bDepthTestEnabled;
		depthStencilStateDesc.DepthWriteMask = desc.DepthStencilState.bDepthWriteEnabled ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO;
		depthStencilStateDesc.DepthFunc = DX12PipelineUtils::GetDepthFunction(desc.DepthStencilState.DepthComparision);
		depthStencilStateDesc.StencilEnable = desc.DepthStencilState.bStencilTestEnabled;
		depthStencilStateDesc.StencilReadMask = 1;
		depthStencilStateDesc.StencilWriteMask = 1;


		D3D12_DEPTH_STENCILOP_DESC stencilFrontFace = DX12PipelineUtils::GetStencilFaceDesc(desc.DepthStencilState.StencilFrontFace);

		D3D12_DEPTH_STENCILOP_DESC stencilBackFace = DX12PipelineUtils::GetStencilFaceDesc(desc.DepthStencilState.StencilBackFace);

		depthStencilStateDesc.FrontFace = stencilFrontFace;
		depthStencilStateDesc.BackFace = stencilBackFace;

		psoDesc.DepthStencilState = depthStencilStateDesc;

		/*
		* Set blending state
		*/
		D3D12_BLEND_DESC blendingStateDesc = {};
		blendingStateDesc.AlphaToCoverageEnable = desc.BlendingState.bAlphaToCoverageEnabled;
		blendingStateDesc.IndependentBlendEnable = true;
		for (unsigned int i = 0; i < desc.BlendingState.Attachments.GetCursor(); i++)
		{
			D3D12_RENDER_TARGET_BLEND_DESC attachmentDesc = DX12PipelineUtils::GetBlendingAttachmentDesc(desc.BlendingState.Attachments[i]);

			blendingStateDesc.RenderTarget[i] = attachmentDesc;
		}

		psoDesc.BlendState = blendingStateDesc;

		/*
		* Set topology
		*/
		psoDesc.PrimitiveTopologyType = DX12PipelineUtils::GetTopologyType(desc.MeshTopology);
		mTopology = DX12PipelineUtils::GetTopology(desc.MeshTopology);

		/*
		* Misc
		*/
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.SampleDesc.Count = 1;
		psoDesc.SampleDesc.Quality = 0;


		ASSERT(SUCCEEDED(pDXDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPso))), "DX12Pipeline", "Failed to create the pipeline state object (PSO)");

	}
	DX12GraphicsPipeline::~DX12GraphicsPipeline()
	{
		mPso.Reset();
		mRootSignature.Reset();
		mRootSignatureBlob.Reset();
		mRootSignatureErrorBlob.Reset();
	}
	void DX12GraphicsPipeline::OnDestroy()
	{
		mPso.Reset();
		mRootSignature.Reset();
		mRootSignature.Reset();
		mRootSignatureErrorBlob.Reset();

	}
}