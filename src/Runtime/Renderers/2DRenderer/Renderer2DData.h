#pragma once
#include <Runtime/Math/Vector2F.h>
#include <Runtime/Renderers/2DRenderer/SpriteRendererComponent.h>
#include <Runtime/Renderers/2DRenderer/SpriteCameraComponent.h>
#include <Runtime/Resource/Material/MaterialResource.h>
#include <Runtime/Math/Matrix4x4.h>

namespace Portakal
{
	struct Renderer2DTransformData
	{
		Vector2F Position;
		Vector2F Scale;
		float RotationZ;
	};

	struct Renderer2DInstanceData
	{
		SpriteRendererComponent* pRenderer;
		Renderer2DTransformData Transform; 
		Matrix4x4F ModelMatrix;
		bool bDirty;
	};

	struct Renderer2DCameraData
	{
		SpriteCameraComponent* pCamera;
		RenderTargetResource* pRenderTarget;
		Renderer2DTransformData Transform;
		Matrix4x4F ViewMatrix;
		Matrix4x4F ProjectionMatrix;
		Color4 ClearColor;
		float OrthoSize;
		bool bDirty;
	};

	struct Renderer2DObjectData
	{
		MaterialResource* pMaterial;
		Array<Renderer2DInstanceData> Instances;
	};

	struct Renderer2DFrameDrawData
	{
		Array<Renderer2DCameraData> Cameras;
		Array<Renderer2DObjectData> Objects;
	};
}