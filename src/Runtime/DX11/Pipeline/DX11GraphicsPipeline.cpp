#include "DX11GraphicsPipeline.h"
#include <Runtime/DX11/DX11Device.h>
#include <Runtime/DX11/Pipeline/DX11PipelineUtils.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/DX11/Shader/DX11Shader.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Graphics/Pipeline/PipelineUtils.h>

namespace Portakal
{
	DX11GraphicsPipeline::DX11GraphicsPipeline(const GraphicsPipelineCreateDesc& desc,DX11Device* pDevice) : Pipeline(desc)
	{
		/*
		* Get vertex shader for input layout
		*/
		DX11Shader* pVertexShader = nullptr;
		for (unsigned int i = 0; i < desc.Shaders.GetCursor(); i++)
		{
			Shader* pShader = desc.Shaders[i];
			if (pShader->GetStage() == ShaderStage::Vertex)
			{
				pVertexShader = (DX11Shader*)pShader;
				break;
			}
		}
		ASSERT(pVertexShader != nullptr, "DX11GraphicsPipeline", "Invalid pipeline shader state, there is no vertex shader bound to the pipeline!");

		/*
		* Create input layout
		*/
		{
			Array<D3D11_INPUT_ELEMENT_DESC> inputElements;
			Array<unsigned int> semanticIndexCache;
			for (unsigned char i = 0; i < (unsigned char)InputElementSemantic::COUNT; i++)
			{
				semanticIndexCache.Add(0);
			}

			unsigned int offset = 0;
			for (unsigned int i = 0; i < desc.InputLayout.Elements.GetCursor(); i++)
			{
				InputElementDesc& element = desc.InputLayout.Elements[i];

				D3D11_INPUT_ELEMENT_DESC elementDesc = {};
				elementDesc.Format = DXGIUtils::GetInputElementFormat(element.Format);
				elementDesc.AlignedByteOffset = offset;
				elementDesc.SemanticName = DX11PipelineUtils::GetSemanticName(element.Semantic).GetSourceCopy();
				elementDesc.SemanticIndex = semanticIndexCache[(unsigned int)element.Semantic];
				semanticIndexCache[(unsigned int)element.Semantic]++;

				elementDesc.InstanceDataStepRate = desc.InputLayout.InstanceStepRate;
				elementDesc.InputSlot = 0;
				elementDesc.InputSlotClass = desc.InputLayout.InstanceStepRate == 0 ? D3D11_INPUT_PER_VERTEX_DATA : D3D11_INPUT_PER_INSTANCE_DATA;

				inputElements.Add(elementDesc);

				offset += PipelineUtils::GetInputElementDataSize(element.Format);
			}

			const ByteBlock vertexShaderBlob = pVertexShader->GetBytes();
			ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateInputLayout(inputElements.GetData(), inputElements.GetCursor(), vertexShaderBlob.GetBlockDataPtr(), vertexShaderBlob.GetBlockSizeInBytes(), mInputLayout.GetAddressOf())), "DX11GraphicsPipeline", "Failed to create input layout");

			/*
			* Delete names
			*/
			for (unsigned int i = 0; i < inputElements.GetCursor(); i++)
			{
				delete inputElements[i].SemanticName;
			}
		}

		/*
		* Create rasterizer state
		*/
		{
			D3D11_RASTERIZER_DESC rasterizerDesc = {};
			rasterizerDesc.AntialiasedLineEnable = false;
			rasterizerDesc.DepthClipEnable = desc.RasterizerState.bDepthClipEnabled;
			rasterizerDesc.MultisampleEnable = false;
			rasterizerDesc.ScissorEnable = desc.RasterizerState.bScissorTestEnabled;
			rasterizerDesc.FrontCounterClockwise = desc.RasterizerState.FrontFace == FrontFaceDirection::CounterClockwise;
			rasterizerDesc.CullMode = DX11PipelineUtils::GetCullMode(desc.RasterizerState.CullMode);
			rasterizerDesc.DepthBias = desc.RasterizerState.DepthBias;
			rasterizerDesc.DepthBiasClamp = desc.RasterizerState.DepthBiasClamp;
			rasterizerDesc.SlopeScaledDepthBias = desc.RasterizerState.DepthBiasSlope;
			rasterizerDesc.FillMode = DX11PipelineUtils::GetFillMode(desc.RasterizerState.ShadeMode);

			ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateRasterizerState(&rasterizerDesc, mRasterizerState.GetAddressOf())),"DX11GraphicsPipeline","Failed to create rasterizer state");
		}

		/*
		* Create depth stencil state
		*/
		{
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
			depthStencilDesc.DepthEnable = desc.DepthStencilState.bDepthTestEnabled;
			depthStencilDesc.DepthWriteMask = desc.DepthStencilState.bDepthWriteEnabled ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
			depthStencilDesc.DepthFunc = DX11PipelineUtils::GetComparision(desc.DepthStencilState.DepthComparision);
			depthStencilDesc.StencilWriteMask = desc.DepthStencilState.StencilWriteMask;
			depthStencilDesc.StencilReadMask = desc.DepthStencilState.StencilReadMask;
			depthStencilDesc.StencilEnable = desc.DepthStencilState.bStencilTestEnabled;

			depthStencilDesc.FrontFace = DX11PipelineUtils::GetStencilFaceDesc(desc.DepthStencilState.StencilFrontFace);
			depthStencilDesc.BackFace = DX11PipelineUtils::GetStencilFaceDesc(desc.DepthStencilState.StencilBackFace);

			ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateDepthStencilState(&depthStencilDesc, mDepthStencilState.GetAddressOf())),"DX11GraphicsPipeline","Failed to create depth stencil state");
		}

		/*
		* Create blending state
		*/
		{
			D3D11_BLEND_DESC blendingDesc = {};
			blendingDesc.IndependentBlendEnable = true;
			blendingDesc.AlphaToCoverageEnable = desc.BlendingState.bAlphaToCoverageEnabled;

			for (unsigned int i = 0; i < desc.BlendingState.Attachments.GetCursor(); i++)
			{
				const BlendingAttachmentDesc& attachment = desc.BlendingState.Attachments[i];

				blendingDesc.RenderTarget[i] = DX11PipelineUtils::GetBlendingAttachmentDesc(attachment);
			}

			ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateBlendState(&blendingDesc, mBlendingState.GetAddressOf())),"DX11GraphicsPipeline","Failed to create blending state");
		}

		/*
		* Set topology
		*/
		mTopology = DX11PipelineUtils::GetTopology(desc.MeshTopology);

		/*
		* Create shaders
		*/
		for (unsigned int i = 0; i < desc.Shaders.GetCursor(); i++)
		{
			DX11Shader* pShader = (DX11Shader*)desc.Shaders[i];

			switch (pShader->GetStage())
			{
				case Portakal::ShaderStage::None:
				{
					break;
				}
				case Portakal::ShaderStage::Vertex:
				{
					mVertexShader = pShader->GetDXVertexShader();
					break;
				}
				case Portakal::ShaderStage::Fragment:
				{
					mPixelShader = pShader->GetDXPixelShader();
				}
				case Portakal::ShaderStage::TesellationEval:
				{
					mDomainShader = pShader->GetDXDomainShader();
					break;
				}
				case Portakal::ShaderStage::TesellationControl:
				{
					mHullShader = pShader->GetDXHullShader();
					break;
				}
				case Portakal::ShaderStage::Compute:
				{
					mComputeShader = pShader->GetDXComputeShader();
					break;
				}
				default:
					ASSERT(false, "DX11GraphicsPipeline", "Invalid shader in the pipeline!");
					break;
			}
		}
	}
	DX11GraphicsPipeline::~DX11GraphicsPipeline()
	{

	}
	void DX11GraphicsPipeline::OnDestroy()
	{

	}
	void DX11GraphicsPipeline::SetDeviceObjectNameCore(const String& name)
	{
		/*
		* Set rasterizer
		*/
		const String rasterizerName = name + " RasterizerState";
		mRasterizerState->SetPrivateData(WKPDID_D3DDebugObjectName, rasterizerName.GetCursor(), rasterizerName.GetSource());

		/*
		* Set depth stencil
		*/
		const String depthStencilName = name + " DepthStencilState";
		mDepthStencilState->SetPrivateData(WKPDID_D3DDebugObjectName, depthStencilName.GetCursor(), depthStencilName.GetSource());

		/*
		* Set blending
		*/
		const String blendingName = name + " BlendingState";
		mBlendingState->SetPrivateData(WKPDID_D3DDebugObjectName, blendingName.GetCursor(), blendingName.GetSource());
	}
}