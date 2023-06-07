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
		* Create new camera entry
		*/
		Renderer2DCameraData cameraData = {};
		cameraData.pCamera = pCamera;
		cameraData.bDirty = true;
		UpdateCameraProperties(cameraData, pCamera);
		UpdateCameraTransform(cameraData, pCamera);

		/*
		* Register render target to render graph
		*/
		if(pCamera->GetRenderTarget() != nullptr)
			RegisterRenderGraphRenderTarget(pCamera->GetRenderTarget());

		/*
		* Register newly created camera entry
		*/
		mDrawData.Cameras.Add(cameraData);

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
		Renderer2DCameraData& data = mDrawData.Cameras[index];

		/*
		* Remove render target from the render graph
		*/
		if(data.pRenderTarget != nullptr)
			RemoveRenderGraphRenderTarget(data.pRenderTarget);

		/*
		* Just remove the camera entry
		*/
		mDrawData.Cameras.RemoveIndex(index);

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
		bool bCreatedAsInstance = false;
		for (unsigned int i = 0; i < mDrawData.Objects.GetCursor(); i++)
		{
			Renderer2DObjectData& objectData = mDrawData.Objects[i];

			/*
			* Found an exact material, create anew instance for the material
			*/
			if (objectData.pMaterial == pRendererMaterial)
			{
				/*
				* Create instance
				*/
				CreateInstance(objectData, pRenderer);

				/*
				* Mark as this process was a instance creation process
				*/
				bCreatedAsInstance = true;
				break;
			}
		}

		/*
		* Check if this was a instance creation process or a new object creation process
		*/
		if (!bCreatedAsInstance) // this means we have a object creation process.
		{
			/*
			* Create object data
			*/
			Renderer2DObjectData objectData = {};
			objectData.pMaterial = pRendererMaterial;

			/*
			* Create first instance
			*/
			CreateInstance(objectData, pRenderer);

			/*
			* Register new object data
			*/
			mDrawData.Objects.Add(objectData);

			/*
			* Register new material to the render graph
			*/
			if (pRendererMaterial != nullptr)
				mRenderGraph->RegisterMaterial(objectData.pMaterial);
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
		for (unsigned int objectIndex = 0; objectIndex < mDrawData.Objects.GetCursor(); objectIndex++)
		{
			Renderer2DObjectData& objectData = mDrawData.Objects[objectIndex];

			for (unsigned int instanceIndex = 0; instanceIndex < objectData.Instances.GetCursor(); instanceIndex++)
			{
				Renderer2DInstanceData& instanceData = objectData.Instances[instanceIndex];

				/*
				* Check and remove if the renderers match
				*/
				if (instanceData.pRenderer == pRenderer) // remove this instance
				{
					/*
					* Remove it from the instance list
					*/
					objectData.Instances.RemoveIndex(instanceIndex);

					/*
					* Check if the objectdata has no instances now, if it does not than delete it
					*/
					if (objectData.Instances.GetCursor() == 0)
					{
						/*
						* Remove the material from the render graph
						*/
						RemoveRenderGraphMaterial(objectData.pMaterial);

						/*
						* Remove it from the frame data
						*/
						mDrawData.Objects.RemoveIndex(objectIndex);
						break;
					}
				}
			}
		}

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
		for (unsigned int i = 0; i < mDrawData.Cameras.GetCursor(); i++)
		{
			Renderer2DCameraData& data = mDrawData.Cameras[i];
			UpdateCameraProperties(data, pCamera);
			return;
		}
	}

	void Renderer2DSceneAspect::SignalCameraRenderTargetChanged(SpriteCameraComponent* pCamera, RenderTargetResource* pOldRenderTarget, RenderTargetResource* pNewRenderTarget)
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
		for (unsigned int i = 0; i < mDrawData.Cameras.GetCursor(); i++)
		{
			Renderer2DCameraData& data = mDrawData.Cameras[i];
			UpdateCameraProperties(data, pCamera);
		}

		/*
		* Signal render graph
		*/
		mRenderGraph->RemoveRenderTarget(pOldRenderTarget);
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
		* Find old renderer material data and remove it
		*/
		for (unsigned int objectIndex = 0; objectIndex < mDrawData.Objects.GetCursor(); objectIndex++)
		{
			Renderer2DObjectData& objectData = mDrawData.Objects[objectIndex];

			/*
			* Check if the old material matches
			*/
			if (objectData.pMaterial == pOldMaterial)
			{
				for (unsigned int instanceIndex = 0; instanceIndex < objectData.Instances.GetCursor(); instanceIndex++)
				{
					Renderer2DInstanceData& instanceData = objectData.Instances[instanceIndex];

					if (instanceData.pRenderer == pRenderer)
					{
						/*
						* Remove the instance data from this object data
						*/
						objectData.Instances.RemoveIndex(instanceIndex);

						/*
						* Check if object data has no instances now!
						*/
						if (objectData.Instances.GetCursor() == 0)
						{
							/*
							* Remove material from the render graph
							*/
							mRenderGraph->RemoveMaterial(objectData.pMaterial);

							/*
							* Remove this object data from the draw list
							*/
							mDrawData.Objects.RemoveIndex(objectIndex);
						}
						break;
					}
				}
			}
		}

		/*
		* Remove the renderer
		*/
		mRenderers.RemoveIndex(index);

		/*
		* Register the renderer
		*/
		RegisterRenderer(pRenderer);
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
		* Find this renderer
		*/
		for (unsigned int objectIndex = 0; objectIndex < mDrawData.Objects.GetCursor(); objectIndex++)
		{
			Renderer2DObjectData& objectData = mDrawData.Objects[objectIndex];

			for (unsigned int instanceIndex = 0; instanceIndex < objectData.Instances.GetCursor(); instanceIndex++)
			{
				Renderer2DInstanceData& instanceData = objectData.Instances[instanceIndex];

				if (instanceData.pRenderer == pRenderer)
				{
					UpdateInstanceTransform(instanceData, pRenderer);
					return;
				}
			}
		}
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
		for (unsigned int cameraIndex = 0; cameraIndex < mDrawData.Cameras.GetCursor(); cameraIndex++)
		{
			Renderer2DCameraData& cameraData = mDrawData.Cameras[cameraIndex];
			if (cameraData.pCamera == pCamera)
			{
				UpdateCameraTransform(cameraData, pCamera);
				return;
			}
		}
	}
	void Renderer2DSceneAspect::CreateInstance(Renderer2DObjectData& objectData, SpriteRendererComponent* pRenderer)
	{
		/*
		* Create instance
		*/
		Renderer2DInstanceData instanceData = {};
		instanceData.pRenderer = pRenderer;
		instanceData.Transform = {};
		instanceData.bDirty = true;

		UpdateInstanceTransform(instanceData, pRenderer);

		/*
		* Register the instance to the object data
		*/
		objectData.Instances.Add(instanceData);

	}
	void Renderer2DSceneAspect::UpdateInstanceTransform(Renderer2DInstanceData& data, SpriteRendererComponent* pRenderer)
	{
		data.Transform.Position = pRenderer->GetPosition();
		data.Transform.RotationZ = pRenderer->GetRotation();
		data.Transform.Scale = pRenderer->GetScale();
		data.bDirty = true;
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
		data.pRenderTarget = pCamera->GetRenderTarget();
		data.bDirty = true;
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
		for (unsigned int cameraIndex = 0; cameraIndex < mDrawData.Cameras.GetCursor(); cameraIndex++)
		{
			/*
			* Get camera data and validate if this camera is dirty
			*/
			Renderer2DCameraData& data = mDrawData.Cameras[cameraIndex];
			if (!data.bDirty)
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
		}

		/*
		* Iterate and update dirty instances
		*/
		for (unsigned int objectIndex = 0; objectIndex < mDrawData.Objects.GetCursor(); objectIndex++)
		{
			/*
			* Get object data
			*/
			Renderer2DObjectData& objectData = mDrawData.Objects[objectIndex];

			/*
			* Iterate instances
			*/
			for (unsigned int instanceIndex = 0; instanceIndex < objectData.Instances.GetCursor(); instanceIndex++)
			{
				/*
				* Get instance data
				*/
				Renderer2DInstanceData& instanceData = objectData.Instances[instanceIndex];
				if (!instanceData.bDirty)
					continue;

				/*
				* Rebuild model matrix
				*/
				instanceData.ModelMatrix = Matrix4x4F::Scale(instanceData.Transform.Scale)* Matrix4x4F::RotationZ(instanceData.Transform.RotationZ) *Matrix4x4F::Translation(instanceData.Transform.Position);
			}
		}
	}
}