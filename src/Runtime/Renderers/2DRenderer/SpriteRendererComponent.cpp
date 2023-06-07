#include "SpriteRendererComponent.h"
#include <Runtime/World/Entity.h>
#include <Runtime/World/Scene.h>
#include <Runtime/Renderers/2DRenderer/Renderer2DSceneAspect.h>

namespace Portakal
{
	void SpriteRendererComponent::SetMaterial(MaterialResource* pMaterial)
	{
		/*
		* Check if the materials are the same
		*/
		if (mMaterial == pMaterial)
			return;

		/*
		* Get renderer aspect and validate
		*/
		Renderer2DSceneAspect* pAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();
		if (pAspect == nullptr)
			return;

		/*
		* Signal that this renderer has a new material now
		*/
		pAspect->SignalRendererMaterialChanged(this, mMaterial, pMaterial);

		/*
		* Set material
		*/
		mMaterial = pMaterial;
	}
	void SpriteRendererComponent::SetTexture(TextureResource* pTexture)
	{
		/*
		* Check if it has material
		*/
		if (mMaterial == nullptr)
			return;

		/*
		* Set material fixed texture field
		*/
		mMaterial->SetTextureParameter("textureIn", ShaderStage::Fragment, pTexture);
	}

	void SpriteRendererComponent::SetPosition(const Vector2F value)
	{
		/*
		* Set position
		*/
		mPosition = value;

		/*
		* Get renderer aspect and validate
		*/
		Renderer2DSceneAspect* pAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();
		if (pAspect == nullptr)
			return;

		/*
		* Signal
		*/
		pAspect->SignalRendererTransformChanged(this);
	}

	void SpriteRendererComponent::SetScale(const Vector2F value)
	{
		mScale = value;

		/*
		* Get renderer aspect and validate
		*/
		Renderer2DSceneAspect* pAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();
		if (pAspect == nullptr)
			return;

		/*
		* Signal
		*/
		pAspect->SignalRendererTransformChanged(this);
	}

	void SpriteRendererComponent::SetRotation(const float value)
	{
		mRotation = value;

		/*
		* Get renderer aspect and validate
		*/
		Renderer2DSceneAspect* pAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();
		if (pAspect == nullptr)
			return;

		/*
		* Signal
		*/
		pAspect->SignalRendererTransformChanged(this);
	}
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
              float2 uv  : TEXCOORD0;\
            };\
            \
            struct PS_INPUT\
            {\
              float4 pos : SV_POSITION;\
              float2 uv  : TEXCOORD0;\
            };\
            \
            PS_INPUT main(VS_INPUT input)\
            {\
              PS_INPUT output;\
			  output.pos = mul( ProjectionMatrix, float4(input.pos.xy, 0.f, 1.f));\
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
            float2 uv  : TEXCOORD0;\
            };\
            sampler sampler0;\
            Texture2D texture0;\
            \
			struct PS_OUTPUT\
			{\
				float4 Color : SV_Target0;\
				float4 UvColor : SV_Target1;\
			};\
            PS_OUTPUT main(PS_INPUT input)\
            {\
			float4 color = texture0.Sample(sampler0,input.uv);\
			float4 uvColor = float4(input.uv,0,1);\
			PS_OUTPUT output;\
			output.Color = color;\
			output.UvColor = uvColor;\
			return output;\
            }";
	void SpriteRendererComponent::OnInitialize()
	{
		/*
		* Get renderer aspect and validate
		*/
		Renderer2DSceneAspect* pAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();
		if (pAspect == nullptr)
			return;

		/*
		* Create dummy material for testing
		*/
		ShaderResource* pVertexShader = new ShaderResource();
		ShaderResource* pFragmentShader = new ShaderResource();
		pVertexShader->Compile("main", vertexShaderSource, ShaderStage::Vertex);
		pFragmentShader->Compile("main", pixelShaderSource, ShaderStage::Fragment);

		RasterizerStateDesc rasterizerState = {};
		rasterizerState.bDepthClipEnabled = false;
		rasterizerState.bScissorTestEnabled = false;
		rasterizerState.CullMode = FaceCullMode::Back;
		rasterizerState.DepthBias = 0;
		rasterizerState.DepthBiasClamp = 0;
		rasterizerState.DepthBiasSlope = 0;
		rasterizerState.FrontFace = FrontFaceDirection::CounterClockwise;
		rasterizerState.ShadeMode = MeshShadeMode::Solid;

		DepthStencilStateDesc depthStencilState = {};
		depthStencilState.bDepthTestEnabled = false;
		depthStencilState.bDepthWriteEnabled = false;
		depthStencilState.bStencilTestEnabled = false;
		
		BlendingStateDesc blendingState = {};
		blendingState.bAlphaToCoverageEnabled = false;
		BlendingAttachmentDesc blendingAttachment = {};
		blendingAttachment.bEnabled = false;
		blendingAttachment.WriteMask = BlendingColorWriteFlags::All;
		blendingState.Attachments.Add(blendingAttachment);
		blendingState.Attachments.Add(blendingAttachment);

		MaterialResource* pMaterial = new MaterialResource();
		pMaterial->Create({ pVertexShader,pFragmentShader },rasterizerState,depthStencilState,blendingState);

		SetMaterial(pMaterial);

		pAspect->RegisterRenderer(this);
	}
	void SpriteRendererComponent::OnFinalize()
	{
		/*
		* Get renderer aspect and validate
		*/
		Renderer2DSceneAspect* pAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();
		if (pAspect == nullptr)
			return;

		pAspect->RemoveRenderer(this);
	}
}