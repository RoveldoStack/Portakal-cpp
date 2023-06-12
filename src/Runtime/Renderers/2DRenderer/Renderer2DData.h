#pragma once
#include <Runtime/Math/Vector2F.h>
#include <Runtime/Renderers/2DRenderer/SpriteRendererComponent.h>
#include <Runtime/Renderers/2DRenderer/SpriteCameraComponent.h>
#include <Runtime/Resource/Material/MaterialResource.h>
#include <Runtime/Math/Matrix4x4.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Graphics/Resource/ResourceTable.h>

namespace Portakal
{
	struct Renderer2DTransformData
	{
		Renderer2DTransformData() : RotationZ(0)
		{

		}

		Vector2F Position;
		Vector2F Scale;
		float RotationZ;
	};

	struct Renderer2DInstanceData
	{
		Renderer2DInstanceData() : pRenderer(nullptr), bDirty(false), bNeedGraphicsUpdate(false)
		{

		}

		SpriteRendererComponent* pRenderer;

		Renderer2DTransformData Transform; 

		Matrix4x4F ModelMatrix;

		bool bDirty;
		bool bNeedGraphicsUpdate;
	};

	struct Renderer2DCameraData
	{
		Renderer2DCameraData() : pCamera(nullptr), pRenderTarget(nullptr), OrthoSize(3), bDirty(false), bNeedGraphicsUpdate(false)
		{

		}

		SpriteCameraComponent* pCamera;
		RenderTargetResource* pRenderTarget;

		Renderer2DTransformData Transform;

		Matrix4x4F ViewMatrix;
		Matrix4x4F ProjectionMatrix;
		Matrix4x4F ViewProjectionMatrix;

		Color4 ClearColor;
		float OrthoSize;

		bool bDirty;
		bool bNeedGraphicsUpdate;
	};

	struct Renderer2DObjectData
	{
		Renderer2DObjectData() : pMaterial(nullptr)
		{

		}
		MaterialResource* pMaterial;
		Registry<SpriteRendererComponent*,Renderer2DInstanceData> Instances;
	};

	struct Renderer2DFrameDrawData
	{
		Registry<SpriteCameraComponent*,Renderer2DCameraData> Cameras;
		Registry<MaterialResource*,Renderer2DObjectData> Objects;
	};
}