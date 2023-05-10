#include "ImGuiRenderer.h"
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Editor/Renderer/ImGuiAPI.h>
#include <Runtime/Window/Window.h>
#include <Runtime/Input/Keys.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Window/WindowEvents.h>
#include <Runtime/Platform/PlatformClipboard.h>
#include <Editor/Renderer/ImGuiKeys.h>
#include <Runtime/HLSL/HLSLCompiler.h>
#include <Runtime/Graphics/Shader/Shader.h>
#include <Runtime/Graphics/Pipeline/Pipeline.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Graphics/Sampler/Sampler.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>,
#include <Runtime/Graphics/Resource/ResourceTable.h>
#include <Runtime/Graphics/Command/CommandList.h>
#include <Runtime/Object/GarbageCollector.h>
#include <Editor/Renderer/ImGuiTextureBinding.h>
#include <Runtime/Math/Vector2.h>


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

	
	void SetClipboardTextCallback(void* pUserData,const char* pText)
	{
		PlatformClipboard::SetClipboard(pText);
	}
	const char* GetClipboardTextCallback(void* pUserData)
	{
		return PlatformClipboard::GetClipboard().GetSourceCopy();
	}
	ImGuiRenderer::ImGuiRenderer(GraphicsDevice* pDevice) : 
		mDevice(nullptr),mFontTexture(nullptr),mVertexShader(nullptr),mFragmentShader(nullptr),mVertexBuffer(nullptr),mIndexBuffer(nullptr),mConstantBuffer(nullptr),
		mFontTable(nullptr),mSamplerTable(nullptr),mProjectionTable(nullptr),mSampler(nullptr), mCmdList(nullptr),mPipeline(nullptr)
	{
		/*
		* Get window
		*/
		Window* pWindow = pDevice->GetOwnerWindow();

		/*
		* Create context
		*/
		mContext = ImGui::CreateContext();
		ImGui::SetCurrentContext(mContext);

		/*
		* Setup configs
		*/
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags = ImGuiBackendFlags_None;
		io.ConfigFlags = ImGuiConfigFlags_DockingEnable; // enables docking

		/*
		* Setup display config
		*/
		io.DisplaySize = ImVec2(pWindow->GetWidth(),pWindow->GetHeight());
		io.DisplayFramebufferScale = ImVec2(1, 1);

		/*
		* Setup clipboard
		*/
		io.SetClipboardTextFn = SetClipboardTextCallback;
		io.GetClipboardTextFn = GetClipboardTextCallback;

		/*
		* Setup default theme
		*/
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowPadding = ImVec2(15, 15);
		style->WindowRounding = 5.0f;
		style->FramePadding = ImVec2(5, 5);
		style->FrameRounding = 4.0f;
		style->ItemSpacing = ImVec2(12, 8);
		style->ItemInnerSpacing = ImVec2(8, 6);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 15.0f;
		style->ScrollbarRounding = 9.0f;
		style->GrabMinSize = 5.0f;
		style->GrabRounding = 3.0f;

		style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);

		
		/*
		* Create imgui device resources...
		*/


		/*
		* Compile shaders
		*/
		ByteBlock vertexBytes;
		String vertexErrors;
		HLSLCompiler::Compile(vertexShaderSource, "main", ShaderStage::Vertex, 4, 0, vertexBytes, vertexErrors);

		ByteBlock fragmentBytes;
		String fragmentErrors;
		HLSLCompiler::Compile(pixelShaderSource, "main", ShaderStage::Fragment, 4, 0, fragmentBytes, fragmentErrors);
	
		/*
		* Validate shaders
		*/
		if (vertexErrors.GetCursor() > 0)
		{
			LOG("ImGuiRenderer", "Failed to compile imgui vertex shader with logs: %s", *vertexErrors);
			return;
		}
		if (fragmentErrors.GetCursor() > 0)
		{
			LOG("ImGuiRenderer", "Failed to compile imgui fragment shader with logs: %s", *fragmentErrors);
			return;
		}


		/*
		* Create shader objects
		*/
		ShaderCreateDesc vertexShaderDesc = {};
		vertexShaderDesc.EntryPointMethod = "main";
		vertexShaderDesc.Bytes = vertexBytes;
		vertexShaderDesc.Stage = ShaderStage::Vertex;
		Shader* pVertexShader = pDevice->CreateShader(vertexShaderDesc);

		ShaderCreateDesc fragmentShaderDesc = {};
		fragmentShaderDesc.EntryPointMethod = "main";
		fragmentShaderDesc.Bytes = fragmentBytes;
		fragmentShaderDesc.Stage = ShaderStage::Fragment;
		Shader* pFragmentShader = pDevice->CreateShader(fragmentShaderDesc);

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
		* Create output state
		*/
		OutputDesc outputStateDesc = {};
		outputStateDesc.ColorAttachments =
		{
			{TextureFormat::R8_G8_B8_A8_UNorm}
		};
		outputStateDesc.SampleCount = 1;

		/*
		* Create resource state
		*/
		ResourceStateDesc resourceStateDesc = {};

		resourceStateDesc.Slots.Add(
			PipelineResourceTableDesc(ShaderStage::Vertex,
				{
					{"vertexBuffer",PipelineResourceType::ConstantBuffer}
				})
		);
		resourceStateDesc.Slots.Add(
			PipelineResourceTableDesc(ShaderStage::Fragment,
				{
					{"sampler0",PipelineResourceType::Sampler}
				})
		);
		resourceStateDesc.Slots.Add(
			PipelineResourceTableDesc(ShaderStage::Fragment,
				{
					{"texture0",PipelineResourceType::ResourceView}
				})
		);

		GraphicsPipelineCreateDesc pipelineDesc = {};
		pipelineDesc.RasterizerState = rasterizerStateDesc;
		pipelineDesc.DepthStencilState = depthStencilStateDesc;
		pipelineDesc.BlendingState = blendingStateDesc;
		pipelineDesc.ResourceState = resourceStateDesc;
		pipelineDesc.MeshTopology = MeshTopology::TriangleList;
		pipelineDesc.OutputDesc = outputStateDesc;
		pipelineDesc.InputLayout = inputLayoutDesc;
		pipelineDesc.Shaders = { pVertexShader,pFragmentShader };

		Pipeline* pPipeline = pDevice->CreateGraphicsPipeline(pipelineDesc);
		
		/*
		* Create font texture
		*/
		unsigned char* pFontData = nullptr;
		int width;
		int height;
		int channelCount;
		io.Fonts->GetTexDataAsRGBA32(&pFontData,&width,&height,&channelCount);
		
		ASSERT(pFontData != nullptr && width != 0 && height != 0 && channelCount != 0,"ImguiRenderer","Failed to fetch font texture");

		TextureResource* pTexture = new TextureResource(TextureType::Texture2D,TextureUsage::Sampled | TextureUsage::CpuWrite,TextureFormat::R8_G8_B8_A8_UNorm,width,height,1);
		pTexture->UpdateTexture(pFontData, 0, 0, 0);
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

		Sampler* pSampler = pDevice->CreateSampler(samplerDesc);

		/*
		* Create vertex index and constant buffer
		*/
		struct ImDrawVert
		{
			ImVec2  pos;
			ImVec2  uv;
			ImU32   col;
		};
		GraphicsBufferCreateDesc vertexBufferDesc = {};
		vertexBufferDesc.Type = GraphicsBufferType::VertexBuffer;
		vertexBufferDesc.SubItemCount = 1;
		vertexBufferDesc.SubItemSize = sizeof(ImDrawVert);

		GraphicsBufferCreateDesc indexBufferDesc = {};
		indexBufferDesc.Type = GraphicsBufferType::IndexBuffer;
		indexBufferDesc.SubItemCount = 1;
		indexBufferDesc.SubItemSize = sizeof(unsigned short);

		GraphicsBufferCreateDesc constantBufferDesc = {};
		constantBufferDesc.Type = GraphicsBufferType::ConstantBuffer;
		constantBufferDesc.SubItemCount = 1;
		constantBufferDesc.SubItemSize = 64;

		GraphicsBuffer* pVertexBuffer = pDevice->CreateBuffer(vertexBufferDesc);
		GraphicsBuffer* pIndexBuffer = pDevice->CreateBuffer(indexBufferDesc);
		GraphicsBuffer* pConstantBuffer = pDevice->CreateBuffer(constantBufferDesc);

		/*
		* Create resource tables
		*/
		ResourceTableCreateDesc samplerResourceTable = {};
		samplerResourceTable.Resources = { pSampler };

		ResourceTableCreateDesc textureResourceTable = {};
		textureResourceTable.Resources = { (GraphicsDeviceObject*)pTexture->GetTexture()};

		ResourceTableCreateDesc projectionResourceTable = {};
		projectionResourceTable.Resources = {pConstantBuffer};

		ResourceTable* pSamplerTable = pDevice->CreateResourceTable(samplerResourceTable);
		ResourceTable* pTextureTable = pDevice->CreateResourceTable(textureResourceTable);
		ResourceTable* pProjectionTable = pDevice->CreateResourceTable(projectionResourceTable);

		mFontTexture = pTexture;
		mVertexBuffer = pVertexBuffer;
		mIndexBuffer = pIndexBuffer;
		mSampler = pSampler;
		mConstantBuffer = pConstantBuffer;
		mSamplerTable = pSamplerTable;
		mFontTable = pTextureTable;
		mProjectionTable = pProjectionTable;
		mPipeline = pPipeline;
		mVertexShader = pVertexShader;
		mFragmentShader = pFragmentShader;
		mCmdList = pDevice->CreateGraphicsCommandList({});
		mDevice = pDevice;
	}
	ImGuiRenderer::~ImGuiRenderer()
	{
		/*
		* Delete resources
		*/
		mFontTexture->Destroy();
		mVertexBuffer->Destroy();
		mIndexBuffer->Destroy();
		mConstantBuffer->Destroy();
		mSamplerTable->Destroy();
		mFontTable->Destroy();
		mProjectionTable->Destroy();
		mPipeline->Destroy();
		mVertexShader->Destroy();
		mFragmentShader->Destroy();
		mCmdList->Destroy();
		mFontTexture = nullptr;
		mVertexBuffer = nullptr;
		mIndexBuffer = nullptr;
		mConstantBuffer = nullptr;
		mSamplerTable = nullptr;
		mSampler = nullptr;
		mFontTable = nullptr;
		mProjectionTable = nullptr;
		mPipeline = nullptr;
		mVertexShader = nullptr;
		mFragmentShader = nullptr;
		mCmdList = nullptr;
		mDevice = nullptr;

		GarbageCollector::Collect();

		/*
		* Delete context
		*/
		ImGui::DestroyContext(mContext);
	}
	ImGuiTextureBinding* ImGuiRenderer::GetOrCreateTextureBinding(TextureResource* pTexture)
	{
		const int index = mTextureBindings.FindIndex(pTexture);

		RegistryEntry<TextureResource*, ImGuiTextureBinding*> entry = {};
		if (index == -1) // create
		{
			ImGuiTextureBinding* pBinding = new ImGuiTextureBinding(pTexture);
			entry = mTextureBindings.Register(pTexture, pBinding);
		}
		else
		{
			entry = mTextureBindings.GetEntryViaIndex(index);
		}

		return entry.Value;
	}
	void ImGuiRenderer::DeleteTextureBinding(TextureResource* pTexture)
	{
		const int index = mTextureBindings.FindIndex(pTexture);
		if (index == -1)
			return;

		RegistryEntry<TextureResource*, ImGuiTextureBinding*> entry = mTextureBindings.GetEntryViaIndex(index);

		mTextureBindings.Remove(pTexture);

		delete entry.Value;
	}
	void ImGuiRenderer::StartRendering(const float deltaTime)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = deltaTime / 1000.0f;
		io.DisplaySize = { (float)mDevice->GetOwnerWindow()->GetWidth(),(float)mDevice->GetOwnerWindow()->GetHeight() };

		ImGui::NewFrame();
	}
	void ImGuiRenderer::FinalizeRendering(Framebuffer* pFramebuffer)
	{
		ImGuiIO& io = ImGui::GetIO();

		/*
		* Render imgui
		*/
		ImGui::Render();

		/*
		* Get draw data and validate if there are some data to render into
		*/
		ImDrawData* pDrawData = ImGui::GetDrawData();
		if (pDrawData->DisplaySize.x > 0 && pDrawData->DisplaySize.y > 0 && pDrawData->CmdListsCount > 0)
		{
			/*
			* Check if vertex buffer needs an resize
			*/
			if (pDrawData->TotalVtxCount > mVertexBuffer->GetSubItemCount())
			{
				LOG("ImGuiRenderer", "Vertex buffer will be resized");

				/*
				* Destroy former buffer
				*/
				mVertexBuffer->Destroy();
				mVertexBuffer = nullptr;

				GraphicsBufferCreateDesc createDesc = {};
				createDesc.Type = GraphicsBufferType::VertexBuffer;
				createDesc.SubItemCount = pDrawData->TotalVtxCount + 50;
				createDesc.SubItemSize = sizeof(ImDrawVert);

				mVertexBuffer = mDevice->CreateBuffer(createDesc);
			}

			/*
			* Check if index buffer needs an resize
			*/
			if (pDrawData->TotalIdxCount > mIndexBuffer->GetSubItemCount())
			{
				LOG("ImGuiRenderer", "Index buffer will be resized");

				/*
				* Destroy former buffer
				*/
				mIndexBuffer->Destroy();
				mIndexBuffer = nullptr;

				GraphicsBufferCreateDesc createDesc = {};
				createDesc.Type = GraphicsBufferType::IndexBuffer;
				createDesc.SubItemCount = pDrawData->TotalIdxCount + 50;
				createDesc.SubItemSize = sizeof(unsigned short);

				mIndexBuffer = mDevice->CreateBuffer(createDesc);
			}

			/*
			* Draw
			*/
			mCmdList->Lock();
			mCmdList->BindFramebuffer(pFramebuffer);
			mCmdList->ClearColor(0, ColorRgbaF::CornflowerBlue());

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
				
				mCmdList->UpdateBuffer(vertexBufferUpdateDesc, mVertexBuffer);
				mCmdList->UpdateBuffer(indexBufferUpdateDesc, mIndexBuffer);

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

			mCmdList->UpdateBuffer(projectionBufferUpdateDesc, mConstantBuffer);

			/*
			* Set pipeline state
			*/
			mCmdList->BindPipeline(mPipeline);
			mCmdList->SetVertexBuffer(mVertexBuffer);
			mCmdList->SetIndexBuffer(mIndexBuffer);
			mCmdList->CommitResourceTable(0, mProjectionTable);
			mCmdList->CommitResourceTable(1, mSamplerTable);

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

			mCmdList->SetViewport(viewportDesc);

			/*
			* Start draw
			*/
			unsigned int drawVertexOffset = 0;
			unsigned int drawIndexOffset = 0;
			const Vector2F clipOff = { pDrawData->DisplayPos.x,pDrawData->DisplayPos.y};
			for (unsigned int cmdListIndex = 0; cmdListIndex < pDrawData->CmdListsCount; cmdListIndex++)
			{
				ImDrawList* pDrawList = pDrawData->CmdLists[cmdListIndex];
				for (unsigned int cmdIndex = 0; cmdIndex < pDrawList->CmdBuffer.Size; cmdIndex++)
				{
					ImDrawCmd& cmd = pDrawList->CmdBuffer[cmdIndex];

					const Vector2F clipMin = {
						cmd.ClipRect.x - clipOff.X,
						cmd.ClipRect.y - clipOff.Y};
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

					mCmdList->SetScissor(scissorDesc);

					/*
					* Set texture resource
					*/
					if (cmd.TextureId == nullptr)
					{
						mCmdList->CommitResourceTable(2, mFontTable);
					}
					else
					{
						ImGuiTextureBinding* pBinding = (ImGuiTextureBinding*)cmd.TextureId;
						mCmdList->CommitResourceTable(2, pBinding->GetTable());
					}

					mCmdList->DrawIndexed(cmd.ElemCount,(drawIndexOffset + cmd.IdxOffset),(drawVertexOffset + cmd.VtxOffset));
				}

				drawVertexOffset += pDrawList->VtxBuffer.Size;
				drawIndexOffset += pDrawList->IdxBuffer.Size;
			}
		}
		mCmdList->Unlock();

		mDevice->SubmitCommands(mCmdList);
		mDevice->WaitForFinish();


	}
	void ImGuiRenderer::OnEvent(const WindowEvent* pEvent)
	{
		switch (pEvent->GetEventType())
		{
			case WindowEventType::WindowClosed:
				break;
			case WindowEventType::WindowMoved:
				break;
			case WindowEventType::WindowResized:
				OnWindowResized((WindowResizedEvent*)pEvent);
				break;
			case WindowEventType::KeyboardDown:
				OnKeyboardDown((KeyboardKeyDownEvent*)pEvent);
				break;
			case WindowEventType::KeyboardUp:
				OnKeyboardUp((KeyboardKeyUpEvent*)pEvent);
				break;
			case WindowEventType::MouseButtonDown:
				OnMouseButtonDown((MouseButtonDownEvent*)pEvent);
				break;
			case WindowEventType::MouseButtonUp:
				OnMouseButtonUp((MouseButtonUpEvent*)pEvent);
				break;
			case WindowEventType::MouseMoved:
				OnMouseMoved((MouseMovedEvent*)pEvent);
				break;
			case WindowEventType::MouseScrolled:
				OnMouseWheel((MouseWheelEvent*)pEvent);
				break;
			case WindowEventType::Char:
				OnKeyboardChar((KeyboardCharEvent*)pEvent);
				break;
			default:
				break;
		}
	}
	GraphicsBackend ImGuiRenderer::GetTargetBackend() const noexcept
	{
		return mDevice->GetBackend();
	}
	void ImGuiRenderer::OnWindowResized(const WindowResizedEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(pEvent->GetWidth(), pEvent->GetHeight());
	}
	void ImGuiRenderer::OnMouseMoved(const MouseMovedEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(pEvent->GetX(), pEvent->GetY());
	}
	void ImGuiRenderer::OnMouseButtonDown(const MouseButtonDownEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(pEvent->GetButton(), true);
	}
	void ImGuiRenderer::OnMouseButtonUp(const MouseButtonUpEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(pEvent->GetButton(), false);
	}
	void ImGuiRenderer::OnMouseWheel(const MouseWheelEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(0, pEvent->GetVertical() > 0 ? 1 : -1);
	}
	void ImGuiRenderer::OnKeyboardDown(const KeyboardKeyDownEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.AddKeyEvent(ImGuiKeys::GetKey(pEvent->GetKey()), true);

		if(pEvent->GetKey() == KeyboardKeys::LeftControl)
			io.AddKeyEvent(ImGuiKey_ModCtrl, true);
		if (pEvent->GetKey() == KeyboardKeys::LeftShift)
			io.AddKeyEvent(ImGuiKey_ModShift,true);
		if (pEvent->GetKey() == KeyboardKeys::LeftShift)
			io.AddKeyEvent(ImGuiKey_ModAlt, true);
		if (pEvent->GetKey() == KeyboardKeys::LeftShift)
			io.AddKeyEvent(ImGuiKey_ModSuper, true);
	}
	void ImGuiRenderer::OnKeyboardUp(const KeyboardKeyUpEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(ImGuiKeys::GetKey(pEvent->GetKey()),false);

		if (pEvent->GetKey() == KeyboardKeys::LeftControl)
			io.AddKeyEvent(ImGuiKey_ModCtrl, false);
		if (pEvent->GetKey() == KeyboardKeys::LeftShift)
			io.AddKeyEvent(ImGuiKey_ModShift, false);
		if (pEvent->GetKey() == KeyboardKeys::LeftShift)
			io.AddKeyEvent(ImGuiKey_ModAlt, false);
		if (pEvent->GetKey() == KeyboardKeys::LeftShift)
			io.AddKeyEvent(ImGuiKey_ModSuper, false);
	}
	void ImGuiRenderer::OnKeyboardChar(const KeyboardCharEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.AddInputCharacter(pEvent->GetChar());
	}
}