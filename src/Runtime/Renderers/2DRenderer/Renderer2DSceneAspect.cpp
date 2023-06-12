#include "Renderer2DSceneAspect.h"
#include <Runtime/Renderers/2DRenderer/SpriteCameraComponent.h>
#include <Runtime/Renderers/2DRenderer/SpriteRendererComponent.h>
#include <Runtime/World/Entity.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Renderers/2DRenderer/Renderer2DRenderPass.h>

namespace Portakal
{
	void Renderer2DSceneAspect::Initialize()
	{
		/*
		* Get device
		*/
		GraphicsDevice* pDevice = GraphicsDeviceAPI::GetDefaultDevice();

		/*
		* Create command list
		*/
		mCmdList = pDevice->CreateCommandList({});

		/*
		* Create populate and compile render graph
		*/
		RenderGraph* pRenderGraph = new RenderGraph();

		pRenderGraph->CreateGlobalOther("FrameDrawData");

		Renderer2DRenderPass* pRenderPass = pRenderGraph->CreatePass<Renderer2DRenderPass>();

		pRenderGraph->ConnectGlobalOutput("FrameDrawData", pRenderPass->GetInput("renderDataIn"));
		pRenderGraph->SetFinishPass(pRenderPass);

		pRenderGraph->Compile();

		mRenderGraph = pRenderGraph;
		mDevice = pDevice;
	}
	void Renderer2DSceneAspect::Execute()
	{
		/*
		* Update dirty state
		*/
		UpdateDirtyStates();

		/*
		* Set per frame FrameRenderData
		*/
		mRenderGraph->SetGlobalOther("FrameDrawData", &mDrawData);

		/*
		* Execute render graph
		*/
		mCmdList->Lock();
		mRenderGraph->ExecuteSync(mCmdList);
		mCmdList->Unlock();
	}
	void Renderer2DSceneAspect::Finalize()
	{
		/*
		* Delete cmd list
		*/
		mCmdList->Destroy();
		mCmdList == nullptr;

		/*
		* Delete rendering graph
		*/
		mRenderGraph->Destroy();
		mRenderGraph = nullptr;
	}
	void Renderer2DSceneAspect::RegisterCamera(SpriteCameraComponent* pCamera)
	{
		/*
		* Validate
		*/
		if (pCamera == nullptr)
			return;

		/*
		* First try find if this camera exists
		*/
		if (mCameras.Has(pCamera))
			return;

		/*
		* Create new camera data
		*/
		CreateCameraData(pCamera);

		/*
		* Register
		*/
		mCameras.Add(pCamera);
	}
	void Renderer2DSceneAspect::RemoveCamera(SpriteCameraComponent* pCamera)
	{
		/*
		* First try find if this camera exists
		*/
		const int index = mCameras.FindIndex(pCamera);
		if (index == -1)
			return;

		/*
		* Get camera data
		*/
		Renderer2DCameraData& data = mDrawData.Cameras[index].Value;

		/*
		* Delete camera data
		*/
		DeleteCameraData(data,index);

		/*
		* Remove from the list
		*/
		mCameras.RemoveIndex(index);
	}
	void Renderer2DSceneAspect::RegisterRenderer(SpriteRendererComponent* pRenderer)
	{
		/*
		* Validate
		*/
		if (pRenderer == nullptr)
			return;

		/*
		* First try find
		*/
		if (mRenderers.Has(pRenderer))
			return;

		/*
		* Search if the given renderer material already exists
		*/
		MaterialResource* pRendererMaterial = pRenderer->GetMaterial();
		Renderer2DObjectData* pFoundObjectData = mDrawData.Objects.GetEntryValue(pRendererMaterial);
		if (pFoundObjectData != nullptr) // found material just add instance
		{
			CreateInstance(*pFoundObjectData, pRenderer);
		}
		else
		{
			CreateObjectData(pRenderer);
		}
		

		/*
		* Add to the list
		*/
		mRenderers.Add(pRenderer);
	}
	void Renderer2DSceneAspect::RemoveRenderer(SpriteRendererComponent* pRenderer)
	{
		/*
		* Validate
		*/
		if (pRenderer == nullptr)
			return;

		/*
		* Check if we have this renderer
		*/
		const int index = mRenderers.FindIndex(pRenderer);
		if (index == -1)
			return;

		/*
		* Search for instance
		*/
		Renderer2DObjectData* pObjectData = mDrawData.Objects.GetEntryValue(pRenderer->GetMaterial());
		if (pObjectData == nullptr)
		{
			LOG("Renderer2DAspect", "Given renderer component couldnt not be removed due to it's not registered");
			return;
		}

		/*
		* Find instance
		*/
		Renderer2DInstanceData* pInstanceData = pObjectData->Instances.GetEntryValue(pRenderer);
		if (pInstanceData == nullptr)
		{
			LOG("Renderer2DAspect", "Given instance couldnt not be found.");
			return;
		}

		/*
		* Delete instance
		*/
		DeleteInstance(*pObjectData,*pInstanceData);
		
		/*
		* Remove the renderer from the list
		*/
		mRenderers.RemoveIndex(index);
	}
	
	void Renderer2DSceneAspect::SignalCameraPropertiesChanged(SpriteCameraComponent* pCamera)
	{
		/*
		* Validate
		*/
		if (pCamera == nullptr)
			return;

		/*
		* Check if this camera exists
		*/
		if (!mCameras.Has(pCamera))
			return;

		/*
		* Find camera
		*/
		Renderer2DCameraData* pData = mDrawData.Cameras.GetEntryValue(pCamera);
		if (pData == nullptr)
			return;

		/*
		* Update camera properties
		*/
		UpdateCameraProperties(*pData, pCamera);
	}

	void Renderer2DSceneAspect::SignalCameraRenderTargetChanged(SpriteCameraComponent* pCamera, RenderTargetResource* pNewRenderTarget)
	{
		/*
		* Validate
		*/
		if (pCamera == nullptr)
			return;

		/*
		* Check if camera exists
		*/
		if (!mCameras.Has(pCamera))
			return;

		/*
		* Find camera and change
		*/
		Renderer2DCameraData* pData = mDrawData.Cameras.GetEntryValue(pCamera);
		pData->pRenderTarget = pNewRenderTarget;

		if (pData == nullptr)
			return;

		/*
		* Update properties
		*/
		UpdateCameraProperties(*pData, pCamera);

		/*
		* Signal render graph
		*/
		mRenderGraph->RemoveRenderTarget(pData->pRenderTarget);
		mRenderGraph->RegisterRenderTarget(pNewRenderTarget);
	}
	void Renderer2DSceneAspect::SignalRendererMaterialChanged(SpriteRendererComponent* pRenderer, MaterialResource* pOldMaterial, MaterialResource* pNewMaterial)
	{
		/*
		* Validate
		*/
		if (pRenderer == nullptr)
			return;

		/*
		* Check if renderer exists
		*/
		const int index = mRenderers.FindIndex(pRenderer);
		if (index == -1)
			return;

		/*
		* Find the existing renderer object data
		*/
		Renderer2DObjectData* pOldObjectData = mDrawData.Objects.GetEntryValue(pOldMaterial);
		if (pOldObjectData == nullptr)
			return;

		/*
		* Find instance data
		*/
		Renderer2DInstanceData* pInstanceData = pOldObjectData->Instances.GetEntryValue(pRenderer);
		if (pInstanceData == nullptr)
			return;

		/*
		* Remove instance from the object data
		*/
		DeleteInstance(*pOldObjectData, *pInstanceData);

		/*
		* Try find new object data for the new material
		*/
		Renderer2DObjectData* pNewObjectData = mDrawData.Objects.GetEntryValue(pNewMaterial);
		if (pNewObjectData == nullptr) // create new object data
		{
			CreateObjectData(pRenderer);
		}
		else // create new instance data for the existing object data
		{
			CreateInstance(*pNewObjectData, pRenderer);
		}
	}
	void Renderer2DSceneAspect::SignalRendererTransformChanged(SpriteRendererComponent* pRenderer)
	{
		/*
		* Validate
		*/
		if (pRenderer == nullptr)
			return;

		/*
		* Check if we have this renderer
		*/
		if (!mRenderers.Has(pRenderer))
			return;

		/*
		* Find object data
		*/
		Renderer2DObjectData* pObjectData = mDrawData.Objects.GetEntryValue(pRenderer->GetMaterial());
		if (pObjectData == nullptr)
			return;

		/*
		* Find instance data
		*/
		Renderer2DInstanceData* pInstanceData = pObjectData->Instances.GetEntryValue(pRenderer);
		if (pInstanceData == nullptr)
			return;

		/*
		* Update transform
		*/
		UpdateInstanceTransform(*pInstanceData, pRenderer);

	}
	void Renderer2DSceneAspect::SignalCameraTransformChanged(SpriteCameraComponent* pCamera)
	{
		/*
		* Validate
		*/
		if (pCamera == nullptr)
			return;

		/*
		* Check if we have this camera
		*/
		if (!mCameras.Has(pCamera))
			return;

		/*
		* Find this camera
		*/
		Renderer2DCameraData* pData = mDrawData.Cameras.GetEntryValue(pCamera);
		if (pData == nullptr)
			return;

		/*
		* Update camera transform
		*/
		UpdateCameraTransform(*pData, pCamera);
	}
	void Renderer2DSceneAspect::CreateInstance(Renderer2DObjectData& objectData, SpriteRendererComponent* pRenderer)
	{
		struct BufferData
		{
			Matrix4x4F MvpMatrix;
		};

		/*
		* Create instance
		*/
		Renderer2DInstanceData instanceData = {};
		instanceData.pRenderer = pRenderer;
		instanceData.Transform = {};
		instanceData.bDirty = true;

		/*
		* Update transformation
		*/
		UpdateInstanceTransform(instanceData, pRenderer);

		/*
		* Register the instance to the object data
		*/
		objectData.Instances.Register(pRenderer,instanceData);

	}
	void Renderer2DSceneAspect::UpdateInstanceTransform(Renderer2DInstanceData& data, SpriteRendererComponent* pRenderer)
	{
		data.Transform.Position = pRenderer->GetPosition();
		data.Transform.RotationZ = pRenderer->GetRotation();
		data.Transform.Scale = pRenderer->GetScale();
		data.bDirty = true;
	}
	void Renderer2DSceneAspect::DeleteInstance(Renderer2DObjectData& objectData,Renderer2DInstanceData& instanceData)
	{
		/*
		* First remove
		*/
		objectData.Instances.Remove(instanceData.pRenderer);

		/*
		* Check if object data is empty
		*/
		if (objectData.Instances.GetCursor() == 0)
		{
			DeleteObjectData(objectData);
		}
	}
	void Renderer2DSceneAspect::CreateObjectData(SpriteRendererComponent* pRenderer)
	{
		/*
		* Create new object data entry
		*/
		Renderer2DObjectData objectData = {};
		objectData.pMaterial = pRenderer->GetMaterial();
		
		/*
		* Create new instance
		*/
		CreateInstance(objectData, pRenderer);

		/*
		* Register material if exists
		*/
		if (objectData.pMaterial != nullptr)
			RegisterRenderGraphMaterial(objectData.pMaterial);

		/*
		* Register object data
		*/
		mDrawData.Objects.Register(objectData.pMaterial, objectData);
	}
	void Renderer2DSceneAspect::DeleteObjectData(Renderer2DObjectData& objectData)
	{
		/*
		* Check if object data is empty
		*/
		if (objectData.Instances.GetCursor() == 0)
		{
			/*
			* Remove material from render graph if it's not nullptr
			*/
			if (objectData.pMaterial != nullptr)
				RemoveRenderGraphMaterial(objectData.pMaterial);

			/*
			* Remove object data
			*/
			mDrawData.Objects.Remove(objectData.pMaterial);
		}
	}
	void Renderer2DSceneAspect::UpdateCameraTransform(Renderer2DCameraData& data, SpriteCameraComponent* pCamera)
	{
		data.Transform.Position = pCamera->GetPosition();
		data.Transform.RotationZ = pCamera->GetRotation();
		data.bDirty = true;
	}

	void Renderer2DSceneAspect::UpdateCameraProperties(Renderer2DCameraData& data, SpriteCameraComponent* pCamera)
	{
		data.OrthoSize = pCamera->GetOrthoSize();
		data.ClearColor = pCamera->GetClearColor();
		data.bDirty = true;
	}
	void Renderer2DSceneAspect::CreateCameraData(SpriteCameraComponent* pCamera)
	{
		/*
		* Create new camera entry
		*/
		Renderer2DCameraData cameraData = {};
		cameraData.pCamera = pCamera;
		cameraData.pRenderTarget = pCamera->GetRenderTarget();

		/*
		* Update camera property
		*/
		UpdateCameraProperties(cameraData, pCamera);

		/*
		* Update camera transform
		*/
		UpdateCameraTransform(cameraData, pCamera);

		/*
		* Register render target to render graph
		*/
		if (pCamera->GetRenderTarget() != nullptr)
			RegisterRenderGraphRenderTarget(pCamera->GetRenderTarget());

		/*
		* Register newly created camera entry
		*/
		mDrawData.Cameras.Register(pCamera,cameraData);
	}
	void Renderer2DSceneAspect::DeleteCameraData(Renderer2DCameraData& cameraData,const unsigned int index)
	{
		/*
		* Remove render target from the render graph
		*/
		if (cameraData.pRenderTarget != nullptr)
			RemoveRenderGraphRenderTarget(cameraData.pRenderTarget);

		/*
		* Just remove the camera entry
		*/
		mDrawData.Cameras.Remove(cameraData.pCamera);
	}
	void Renderer2DSceneAspect::RegisterRenderGraphMaterial(MaterialResource* pMaterial)
	{
		mRenderGraph->RegisterMaterial(pMaterial);
	}
	void Renderer2DSceneAspect::RemoveRenderGraphMaterial(MaterialResource* pMaterial)
	{
		mRenderGraph->RemoveMaterial(pMaterial);
	}
	void Renderer2DSceneAspect::RegisterRenderGraphRenderTarget(RenderTargetResource* pRenderTarget)
	{
		mRenderGraph->RegisterRenderTarget(pRenderTarget);
	}
	void Renderer2DSceneAspect::RemoveRenderGraphRenderTarget(RenderTargetResource* pRenderTarget)
	{
		mRenderGraph->RemoveRenderTarget(pRenderTarget);
	}
	void Renderer2DSceneAspect::UpdateDirtyStates()
	{
		/*
		* Iterate and update dirty cameras
		*/
		bool bAnyCameraDirty = false;
		for (unsigned int cameraIndex = 0; cameraIndex < mDrawData.Cameras.GetCursor(); cameraIndex++)
		{
			/*
			* Get camera data and validate if this camera is dirty
			*/
			Renderer2DCameraData& data = mDrawData.Cameras[cameraIndex].Value;
			if (!data.bDirty || data.pRenderTarget == nullptr)
				continue;

			/*
			* Rebuild projection matrix
			*/
			const float aspectRatio = data.pRenderTarget->GetWidth() / (float)data.pRenderTarget->GetHeight();
			data.ProjectionMatrix = Matrix4x4F::Ortho(-data.OrthoSize,data.OrthoSize,-data.OrthoSize,data.OrthoSize, -5.0f, 5.0f, aspectRatio);

			/*
			* Rebuild view matrix
			*/
			data.ViewMatrix = Matrix4x4F::Translation(data.Transform.Position*-1.0f) * Matrix4x4F::RotationZ(data.Transform.RotationZ * DEG_TO_RAD);

			/*
			* Rebuild view projection matrix
			*/
			data.ViewProjectionMatrix = data.ViewMatrix * data.ProjectionMatrix;
			data.bDirty = false;
			data.bNeedGraphicsUpdate = true;

			bAnyCameraDirty = true;
		}

		/*
		* Iterate and update dirty instances
		*/
		for (unsigned int objectIndex = 0; objectIndex < mDrawData.Objects.GetCursor(); objectIndex++)
		{
			/*
			* Get object data
			*/
			RegistryEntry<MaterialResource*,Renderer2DObjectData>& objectEntry = mDrawData.Objects[objectIndex];

			/*
			* Iterate instances
			*/
			for (unsigned int instanceIndex = 0; instanceIndex < objectEntry.Value.Instances.GetCursor(); instanceIndex++)
			{
				/*
				* Get instance data
				*/
				RegistryEntry<SpriteRendererComponent*, Renderer2DInstanceData>& instancEntry = objectEntry.Value.Instances[instanceIndex];
				if (!instancEntry.Value.bDirty && !bAnyCameraDirty)
					continue;

				/*
				* Rebuild model matrix
				*/
				instancEntry.Value.ModelMatrix = Matrix4x4F::Scale(instancEntry.Value.Transform.Scale)* Matrix4x4F::RotationZ(instancEntry.Value.Transform.RotationZ) *Matrix4x4F::Translation(instancEntry.Value.Transform.Position);

				instancEntry.Value.bDirty = false;
				instancEntry.Value.bNeedGraphicsUpdate = true;
			}
		}
	}
}