#include "ImGuiRenderPass.h"
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Rendering/InputOutputs.h>
#include <Runtime/Resource/Mesh/MeshResource.h>
#include <Runtime/Resource/Material/MaterialResource.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Math/Vector2.h>
#include <Editor/Renderer/ImGuiTextureBinding.h>
#include <Runtime/Rendering/RenderingPathCache.h>
#include <Runtime/Rendering/RenderGraph.h>
#include <Runtime/Graphics/Resource/ResourceTable.h>




namespace Portakal
{
	/*
	* Vertex shader for imgui
	*/
	static const char* vertexShaderSource =
		"cbuffer vertexBuffer : register(b0) \
            {\
              float4x4 ProjectionMatrix; \
            };\
            struct VS_INPUT\
            {\
              float2 pos : POSITION;\
              float4 col : COLOR0;\
              float2 uv  : TEXCOORD0;\
            };\
            \
            struct PS_INPUT\
            {\
              float4 pos : SV_POSITION;\
              float4 col : COLOR0;\
              float2 uv  : TEXCOORD0;\
            };\
            \
            PS_INPUT main(VS_INPUT input)\
            {\
              PS_INPUT output;\
              output.pos = mul( ProjectionMatrix, float4(input.pos.xy, 0.f, 1.f));\
              output.col = input.col;\
              output.uv  = input.uv;\
              return output;\
            }";

	/*
	* Pixel shader for imgui
	*/
	static const char* pixelShaderSource =
		"struct PS_INPUT\
            {\
            float4 pos : SV_POSITION;\
            float4 col : COLOR0;\
            float2 uv  : TEXCOORD0;\
            };\
            sampler sampler0;\
            Texture2D texture0;\
            \
            float4 main(PS_INPUT input) : SV_Target\
            {\
            float4 out_col = input.col * texture0.Sample(sampler0, input.uv); \
            return out_col; \
            }";

	ImGuiRenderPass::ImGuiRenderPass() : mConstantBuffer(nullptr),mDevice(nullptr),mVertexShader(nullptr),mFragmentShader(nullptr),mPipeline(nullptr)
	{
		CreateInput<RenderTargetInputOutput>("rtIn");
	}
	ImGuiRenderPass::~ImGuiRenderPass()
	{
	}
	
	void ImGuiRenderPass::Initialize()
	{
		/*
		* Get default device
		*/
		mDevice = GraphicsDeviceAPI::GetDefaultDevice();
		ASSERT(mDevice != nullptr, "ImGuiRenderPass", "Failed to initialize render pass due to the default graphics device is invalid");

		/*
		* Create constant buffer
		*/
		GraphicsBufferCreateDesc constantBufferDesc = {};
		constantBufferDesc.Type = GraphicsBufferType::ConstantBuffer;
		constantBufferDesc.SubItemCount = 1;
		constantBufferDesc.SubItemSize = 64;

		GraphicsBuffer* pConstantBuffer = mDevice->CreateBuffer(constantBufferDesc);
		mConstantBuffer = pConstantBuffer;

		/*
		* Create shader objects
		*/
		mVertexShader = new ShaderResource();
		mVertexShader->Compile("main", vertexShaderSource, ShaderStage::Vertex);

		mFragmentShader = new ShaderResource();
		mFragmentShader->Compile("main", pixelShaderSource, ShaderStage::Fragment);
		Array<Shader*> shaders = { mVertexShader->GetShader(),mFragmentShader->GetShader() };
		
		/*
		* Create font texture
		*/
		ImGuiIO& io = ImGui::GetIO();

		unsigned char* pFontData = nullptr;
		int width;
		int height;
		int channelCount;
		io.Fonts->GetTexDataAsRGBA32(&pFontData, &width, &height, &channelCount);

		ASSERT(pFontData != nullptr && width != 0 && height != 0 && channelCount != 0, "ImguiRenderer", "Failed to fetch font texture");

		TextureResource* pFontTexture = new TextureResource(TextureType::Texture2D, TextureUsage::Sampled | TextureUsage::CpuWrite, TextureFormat::R8_G8_B8_A8_UNorm, width, height, 1);
		pFontTexture->UpdateTexture(pFontData, 0, 0, 0);
		io.Fonts->ClearTexData();

		/*
		* Create sampler
		*/
		SamplerCreateDesc samplerDesc = {};
		samplerDesc.AddressU = SamplerAddress::Wrap;
		samplerDesc.AddressV = SamplerAddress::Wrap;
		samplerDesc.AddressW = SamplerAddress::Wrap;
		samplerDesc.Filtering = SamplerFiltering::MinLinear_MagLinear_MipLinear;
		samplerDesc.LodBias = 0;
		samplerDesc.Comparision = ComparisionMethod::Always;
		samplerDesc.MinLod = 0;
		samplerDesc.MaxLod = 0;
		samplerDesc.MaxAnisotropy = 0;

		mSampler = new SamplerResource();
		mSampler->Create(samplerDesc);

		/*
		* Create input layout
		*/
		InputLayoutDesc inputLayoutDesc = {};
		inputLayoutDesc.InstanceStepRate = 0;
		inputLayoutDesc.Elements =
		{
			{"pos",InputElementSemantic::Position,InputElementDataFormat::Float2},
			{"uv",InputElementSemantic::TextureCoordinate,InputElementDataFormat::Float2},
			{"col",InputElementSemantic::Color,InputElementDataFormat::Byte4_Norm}
		};

		/*
		* Create mesh
		*/
		mMesh = new MeshResource();
		mMesh->AllocateVertexes(sizeof(ImDrawVert), 1, inputLayoutDesc);
		mMesh->AllocateIndexes(MeshIndexType::Bit16, 1);


		/*
		* Create pipeline
		*/

		/*
		* Create blending state
		*/
		BlendingStateDesc blendingStateDesc = {};
		blendingStateDesc.bAlphaToCoverageEnabled = false;
		BlendingAttachmentDesc blendingAttachment = {};
		blendingAttachment.bEnabled = true;
		blendingAttachment.SourceColorFactor = BlendFactor::SourceAlpha;
		blendingAttachment.DestinationColorFactor = BlendFactor::InverseSourceAlpha;
		blendingAttachment.ColorFunction = BlendFunction::Add;
		blendingAttachment.SourceAlphaFactor = BlendFactor::One;
		blendingAttachment.DestinationAlphaFactor = BlendFactor::InverseSourceAlpha;
		blendingAttachment.bEnableLogicOp = false;
		blendingAttachment.WriteMask = BlendingColorWriteFlags::All;
		blendingStateDesc.Attachments.Add(blendingAttachment);

		/*
		* Create rasterizer state
		*/
		RasterizerStateDesc rasterizerStateDesc = {};
		rasterizerStateDesc.bScissorTestEnabled = true;
		rasterizerStateDesc.bDepthClipEnabled = true;
		rasterizerStateDesc.CullMode = FaceCullMode::None;
		rasterizerStateDesc.ShadeMode = MeshShadeMode::Solid;
		rasterizerStateDesc.DepthBias = 0;
		rasterizerStateDesc.DepthBiasClamp = 0;
		rasterizerStateDesc.DepthBiasSlope = 0;
		rasterizerStateDesc.FrontFace = FrontFaceDirection::Clockwise;

		/*
		* Create depth stencil state
		*/
		DepthStencilStateDesc depthStencilStateDesc = {};
		depthStencilStateDesc.bDepthTestEnabled = false;
		depthStencilStateDesc.bDepthWriteEnabled = false;
		depthStencilStateDesc.bStencilTestEnabled = false;
		depthStencilStateDesc.DepthComparision = ComparisionMethod::Always;
		depthStencilStateDesc.StencilReadMask = 0;
		depthStencilStateDesc.StencilReference = 0;
		depthStencilStateDesc.StencilWriteMask = 0;

		/*
		* Create resource layout
		*/
		ResourceStateDesc resourceStateDesc = {};
		PipelineResourceTableDesc table0Desc = {};
		table0Desc.Stage = ShaderStage::Vertex;
		table0Desc.Buffers.Add({ "vertexBuffer" });

		PipelineResourceTableDesc table1Desc = {};
		table1Desc.Stage = ShaderStage::Fragment;
		table1Desc.Samplers.Add({ "sampler0" });

		PipelineResourceTableDesc table2Desc = {};
		table2Desc.Stage = ShaderStage::Fragment;
		table2Desc.Textures.Add({ "texture0" });

		resourceStateDesc.Tables.Add(table0Desc);
		resourceStateDesc.Tables.Add(table1Desc);
		resourceStateDesc.Tables.Add(table2Desc);

		GraphicsPipelineCreateDesc pipelineDesc = {};
		pipelineDesc.RasterizerState = rasterizerStateDesc;
		pipelineDesc.DepthStencilState = depthStencilStateDesc;
		pipelineDesc.BlendingState = blendingStateDesc;
		pipelineDesc.InputLayout = inputLayoutDesc;
		pipelineDesc.MeshTopology = MeshTopology::TriangleList;
		pipelineDesc.Shaders = shaders;
		pipelineDesc.OutputDesc.ColorAttachments.Add({ TextureFormat::R8_G8_B8_A8_UNorm });
		pipelineDesc.ResourceState = resourceStateDesc;

		mPipeline = mDevice->CreateGraphicsPipeline(pipelineDesc);

		/*
		* Create resource tables
		*/
		ResourceTableCreateDesc vertexResourceTableDesc = {};
		vertexResourceTableDesc.Buffers.Add(mConstantBuffer);
		
		ResourceTableCreateDesc samplerResourceTableDesc = {};
		samplerResourceTableDesc.Samplers.Add(mSampler->GetSampler());

		ResourceTableCreateDesc fontResourceTableDesc = {};
		fontResourceTableDesc.Textures.Add(pFontTexture->GetTexture());

		mBufferResourceTable = mDevice->CreateResourceTable(vertexResourceTableDesc);
		mSamplerResourceTable = mDevice->CreateResourceTable(samplerResourceTableDesc);
		mFontResourceTable = mDevice->CreateResourceTable(fontResourceTableDesc);
		mFontTexture = pFontTexture;
	}
	void ImGuiRenderPass::Finalize()
	{

	}
	void ImGuiRenderPass::Execute(CommandList* pCmdList) const
	{
		RenderingPathCache* pCache = GetOwnerGraph()->GetRenderingPathCache();

		/*
		* Get material and mesh
		*/
		RenderTargetResource* pRenderTarget = (RenderTargetResource*)GetInput("rtIn")->GetIOData();

		ImGuiIO& io = ImGui::GetIO();

		/*
		* Get draw data and validate if there are some data to render into
		*/
		ImDrawData* pDrawData = ImGui::GetDrawData();
		if (pDrawData->DisplaySize.x > 0 && pDrawData->DisplaySize.y > 0 && pDrawData->CmdListsCount > 0)
		{
			/*
			* Check if vertex buffer needs an resize
			*/
			if (pDrawData->TotalVtxCount > mMesh->GetVertexBufferItemCount())
			{
				LOG("ImGuiRenderer", "Vertex buffer will be resized");

				/*
				* Allocate new vertexes
				*/
				mMesh->AllocateVertexes(sizeof(ImDrawVert), pDrawData->TotalVtxCount + 50);
			}

			/*
			* Check if index buffer needs an resize
			*/
			if (pDrawData->TotalIdxCount > mMesh->GetIndexBufferItemCount())
			{
				LOG("ImGuiRenderer", "Index buffer will be resized");

				/*
				* Allocate new indexes
				*/
				mMesh->AllocateIndexes(MeshIndexType::Bit16, pDrawData->TotalIdxCount + 50);
			}

			/*
			* Draw
			*/
			pCmdList->BindFramebuffer(pRenderTarget->GetFramebuffer());
			pCmdList->ClearColor(0, ColorRgbaF::CornflowerBlue());

			/*
			* SUpdate vertex&index buffers
			*/
			unsigned int vertexOffset = 0;
			unsigned int indexOffset = 0;
			for (unsigned int cmdListIndex = 0; cmdListIndex < pDrawData->CmdListsCount; cmdListIndex++)
			{
				ImDrawList* pDrawList = pDrawData->CmdLists[cmdListIndex];

				const unsigned int vertexBufferSize = pDrawList->VtxBuffer.Size * sizeof(ImDrawVert);
				const unsigned int indexBufferSize = pDrawList->IdxBuffer.Size * sizeof(unsigned short);

				/*
				* Update buffers
				*/
				GraphicsBufferUpdateDesc vertexBufferUpdateDesc = {};
				vertexBufferUpdateDesc.pData = (Byte*)pDrawList->VtxBuffer.Data;
				vertexBufferUpdateDesc.Offset = vertexOffset;
				vertexBufferUpdateDesc.Size = vertexBufferSize;

				GraphicsBufferUpdateDesc indexBufferUpdateDesc = {};
				indexBufferUpdateDesc.pData = (Byte*)pDrawList->IdxBuffer.Data;
				indexBufferUpdateDesc.Offset = indexOffset;
				indexBufferUpdateDesc.Size = indexBufferSize;

				mMesh->UpdateVertexes(vertexBufferUpdateDesc.pData, vertexBufferUpdateDesc.Offset, vertexBufferUpdateDesc.Size, pCmdList);
				mMesh->UpdateIndexes(indexBufferUpdateDesc.pData, indexBufferUpdateDesc.Offset, indexBufferUpdateDesc.Size, pCmdList);

				/*
				* Increment offsets
				*/
				vertexOffset += vertexBufferSize;
				indexOffset += indexBufferSize;
			}

			/*
			* Setup and update orho projection constant buffer
			*/
			const float L = pDrawData->DisplayPos.x;
			const float R = pDrawData->DisplayPos.x + pDrawData->DisplaySize.x;
			const float T = pDrawData->DisplayPos.y;
			const float B = pDrawData->DisplayPos.y + pDrawData->DisplaySize.y;
			float projectionData[] =
			{
				2.0f / (R - L),
				0,
				0,
				0,
				0,
				2.0f / (T - B),
				0,
				0,
				0,
				0,
				0.5f,
				0,
				(R + L) / (L - R),
				(T + B) / (B - T),
				0.5f,
				1.0f
			};

			GraphicsBufferUpdateDesc projectionBufferUpdateDesc = {};
			projectionBufferUpdateDesc.pData = (Byte*)projectionData;
			projectionBufferUpdateDesc.Offset = 0;
			projectionBufferUpdateDesc.Size = sizeof(projectionData);

			pCmdList->UpdateBuffer(projectionBufferUpdateDesc, mConstantBuffer);

			/*
			* Set pipeline state
			*/
			pCmdList->BindPipeline(mPipeline);
			pCmdList->SetVertexBuffer(mMesh->GetVertexBuffer());
			pCmdList->SetIndexBuffer(mMesh->GetIndexBuffer());
			pCmdList->CommitResourceTable(0, mBufferResourceTable);
			pCmdList->CommitResourceTable(1, mSamplerResourceTable);

			/*
			* Scale clip rects
			*/
			pDrawData->ScaleClipRects(io.DisplayFramebufferScale);

			/*
			* Set viewport
			*/
			ViewportDesc viewportDesc = {};
			viewportDesc.Width = pDrawData->DisplaySize.x;
			viewportDesc.Height = pDrawData->DisplaySize.y;
			viewportDesc.MinDepth = 0;
			viewportDesc.MaxDepth = 1.0f;
			viewportDesc.X = 0;
			viewportDesc.Y = 0;

			pCmdList->SetViewport(viewportDesc);

			/*
			* Start draw
			*/
			unsigned int drawVertexOffset = 0;
			unsigned int drawIndexOffset = 0;
			const Vector2F clipOff = { pDrawData->DisplayPos.x,pDrawData->DisplayPos.y };
			for (unsigned int cmdListIndex = 0; cmdListIndex < pDrawData->CmdListsCount; cmdListIndex++)
			{
				ImDrawList* pDrawList = pDrawData->CmdLists[cmdListIndex];
				for (unsigned int cmdIndex = 0; cmdIndex < pDrawList->CmdBuffer.Size; cmdIndex++)
				{
					ImDrawCmd& cmd = pDrawList->CmdBuffer[cmdIndex];

					const Vector2F clipMin = {
						cmd.ClipRect.x - clipOff.X,
						cmd.ClipRect.y - clipOff.Y };
					const Vector2F clipMax = {
						cmd.ClipRect.z - clipOff.X,
						cmd.ClipRect.w - clipOff.Y };

					if (clipMax.X <= clipMin.X || clipMax.Y <= clipMin.Y)
						continue;

					/*
					* Set scissor rect
					*/
					ScissorDesc scissorDesc = {};
					scissorDesc.Left = clipMin.X;
					scissorDesc.Top = clipMin.Y;
					scissorDesc.Right = clipMax.X;
					scissorDesc.Bottom = clipMax.Y;

					pCmdList->SetScissor(scissorDesc);


					/*
					* Commit resource table
					*/
					//pCmdList->CommitResourceTable(pMaterial->GetResourceTable());

					/*
					* Set texture resource
					*/
					if (cmd.TextureId == nullptr)
					{
						pCmdList->CommitResourceTable(2, mFontResourceTable);
					}
					else
					{
						ImGuiTextureBinding* pBinding = (ImGuiTextureBinding*)cmd.TextureId;
						pCmdList->CommitResourceTable(2, pBinding->GetTable());

					}


					pCmdList->DrawIndexed(cmd.ElemCount, (drawIndexOffset + cmd.IdxOffset), (drawVertexOffset + cmd.VtxOffset));
				}

				drawVertexOffset += pDrawList->VtxBuffer.Size;
				drawIndexOffset += pDrawList->IdxBuffer.Size;
			}
		}
		pCmdList->Unlock();
	}
}