#pragma once
#include <Runtime/World/SceneAspect.h>
#include <Runtime/Resource/Material/MaterialResource.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Resource/Mesh/MeshResource.h>
#include <Runtime/Resource/RenderTarget/RenderTargetResource.h>
#include <Runtime/Rendering/RenderGraph.h>
#include <Runtime/Renderers/2DRenderer/SpriteCameraComponent.h>
#include <Runtime/Renderers/2DRenderer/SpriteRendererComponent.h>
#include <Runtime/Math/Vector2F.h>
#include <Runtime/Renderers/2DRenderer/Renderer2DData.h>

namespace Portakal
{
	PCLASS();
	class PORTAKAL_API Renderer2DSceneAspect : public SceneAspect
	{
		GENERATE_CLASS(Renderer2DSceneAspect);
	public:
		Renderer2DSceneAspect() : mCmdList(nullptr),mRenderGraph(nullptr),mDevice(nullptr) {}
		~Renderer2DSceneAspect() = default;

		void RegisterCamera(SpriteCameraComponent* pCamera);
		void RemoveCamera(SpriteCameraComponent* pCamera);

		void RegisterRenderer(SpriteRendererComponent* pRenderer);
		void RemoveRenderer(SpriteRendererComponent* pRenderer);

		void SignalCameraPropertiesChanged(SpriteCameraComponent* pCamera);
		void SignalCameraRenderTargetChanged(SpriteCameraComponent* pCamera,RenderTargetResource* pNewRenderTarget);
		void SignalRendererMaterialChanged(SpriteRendererComponent* pRenderer,MaterialResource* pOldMaterial, MaterialResource* pNewMaterial);
		void SignalRendererTransformChanged(SpriteRendererComponent* pRenderer);
		void SignalCameraTransformChanged(SpriteCameraComponent* pCamera);
	private:
		// Inherited via SceneAspect
		virtual void Initialize() override;
		virtual void Execute() override;
		virtual void Finalize() override;
	private:
		void CreateInstance(Renderer2DObjectData& objectData, SpriteRendererComponent* pRenderer);
		void UpdateInstanceTransform(Renderer2DInstanceData& data, SpriteRendererComponent* pRenderer);
		void DeleteInstance(Renderer2DObjectData& objectData,Renderer2DInstanceData& instanceData);

		void CreateObjectData(SpriteRendererComponent* pRenderer);
		void DeleteObjectData(Renderer2DObjectData& objectData);

		void UpdateCameraTransform(Renderer2DCameraData& data, SpriteCameraComponent* pCamera);
		void UpdateCameraProperties(Renderer2DCameraData& data, SpriteCameraComponent* pCamera);

		void CreateCameraData(SpriteCameraComponent* pCamera);
		void DeleteCameraData(Renderer2DCameraData& cameraData,const unsigned int index);

		void RegisterRenderGraphMaterial(MaterialResource* pMaterial);
		void RemoveRenderGraphMaterial(MaterialResource* pMaterial);
		void RegisterRenderGraphRenderTarget(RenderTargetResource* pRenderTarget);
		void RemoveRenderGraphRenderTarget(RenderTargetResource* pRenderTarget);
		void UpdateDirtyStates();
	private:
		Array<SpriteCameraComponent*> mCameras;
		Array<SpriteRendererComponent*> mRenderers;
		Renderer2DFrameDrawData mDrawData;
		RenderGraph* mRenderGraph;
		CommandList* mCmdList;
		GraphicsDevice* mDevice;
	};

#include "Renderer2DSceneAspect.reflect.h"
}