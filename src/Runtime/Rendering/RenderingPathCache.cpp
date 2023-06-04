#include "RenderingPathCache.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	RenderingPathCache::RenderingPathCache()
	{
		mOwnerDevice = GraphicsDeviceAPI::GetDefaultDevice();
		mMaterials.Reserve(100);
		mMeshes.Reserve(100);
		mRenderTargets.Reserve(100);
	}
	RenderingPathCache::~RenderingPathCache()
	{

	}
	Pipeline* RenderingPathCache::GetSinglePipeline(MeshResource* pMesh, MaterialResource* pMaterial, RenderTargetResource* pRenderTarget)
	{
		const int meshIndex = mMeshes.FindIndex(pMesh);
		if (meshIndex == -1)
			return nullptr;
		const int materialIndex = mMaterials.FindIndex(pMaterial);
		if (materialIndex == -1)
			return nullptr;
		const int renderTargetIndex = mRenderTargets.FindIndex(pRenderTarget);
		if (renderTargetIndex == -1)
			return nullptr;

		return mPathViews[meshIndex].MaterialViews[materialIndex].RenderTargetViews[renderTargetIndex].pPipeline;
	}
	void RenderingPathCache::RegisterMaterial(MaterialResource* pMaterial)
	{
		/*
		* Validate if it's a valid material
		*/
		if (pMaterial == nullptr || pMaterial->IsDestroyed())
			return;

		/*
		* Validate if we have this material already
		*/
		if (mMaterials.Has(pMaterial))
			return;

		/*
		* Register material state changed signal
		*/
		pMaterial->RegisterStateChangedDelegate(GENERATE_MEMBER_DELEGATE1(this, RenderingPathCache::OnMaterialStateChanged, void, MaterialResource*));

		/*
		* Create path view
		*/
		CreateNewMaterialPathView(pMaterial);

		/*
		* Add it to the list
		*/
		mMaterials.Add(pMaterial);
	}
	void RenderingPathCache::RegisterMesh(MeshResource* pMesh)
	{
		/*
		* Validate if it's a valid mesh
		*/
		if (pMesh == nullptr || pMesh->IsDestroyed())
			return;

		/*
		* Validate if we have this mesh already
		*/
		if (mMeshes.Has(pMesh))
			return;

		/*
		* Register mash state changed signal
		*/
		pMesh->RegisterStateChangedDelegate(GENERATE_MEMBER_DELEGATE1(this, RenderingPathCache::OnMeshStateChanged, void, MeshResource*));

		/*
		* Create path view
		*/
		CreateNewMeshPathView(pMesh);

		/*
		* Add it to the list
		*/
		mMeshes.Add(pMesh);
	}
	void RenderingPathCache::RegisterRenderTarget(RenderTargetResource* pRenderTarget)
	{
		/*
		* Validate if it's a valid render target
		*/
		if (pRenderTarget == nullptr || pRenderTarget->IsDestroyed())
			return;

		/*
		* Validate if we have this render target already
		*/
		if (mRenderTargets.Has(pRenderTarget))
			return;

		/*
		* Register render target state changed signal
		*/
		pRenderTarget->RegisterStateChangedDelegate(GENERATE_MEMBER_DELEGATE1(this, RenderingPathCache::OnRenderTargetStateChanged, void, RenderTargetResource*));

		/*
		* Create path view
		*/
		CreateNewRenderTargetPathView(pRenderTarget);

		/*
		* Add it to the list
		*/
		mRenderTargets.Add(pRenderTarget);
	}
	void RenderingPathCache::RemoveMaterial(MaterialResource* pMaterial)
	{
		/*
		* Validate if material exists within this cache
		*/
		if (!mMaterials.Has(pMaterial))
			return;

		/*
		* Delete material
		*/
		DeleteMaterial(pMaterial);

		/*
		* Remove material
		*/
		mMaterials.Remove(pMaterial);
	}
	void RenderingPathCache::RemoveMesh(MeshResource* pMesh)
	{
		/*
		* Validate if mesh exists within this cache
		*/
		if (!mMeshes.Has(pMesh))
			return;

		/*
		* Delete mesh
		*/
		DeleteMesh(pMesh);

		/*
		* Remove mesh
		*/
		mMeshes.Remove(pMesh);
	}
	void RenderingPathCache::RemoveRenderTarget(RenderTargetResource* pRenderTarget)
	{
		/*
		* Validate if render target within this cache
		*/
		if (!mRenderTargets.Has(pRenderTarget))
			return;

		/*
		* Delete render target
		*/
		DeleteRenderTarget(pRenderTarget);

		/*
		* Remove render target
		*/
		mRenderTargets.Remove(pRenderTarget);
	}
	void RenderingPathCache::OnMaterialStateChanged(MaterialResource* pMaterial)
	{
		/*
		* Check for something sus
		*/
		ASSERT(pMaterial != nullptr, "RenderingPathCache", "OnMaterialStateChanged reported a nullptr material!");

		/*
		* Check if the given material is valid
		*/
		if (pMaterial->IsDestroyed())
		{
			/*
			* Validate for invalid material
			*/
			const int index = mMaterials.FindIndex(pMaterial);
			ASSERT(index != -1, "RenderingPathCache", "The material given in method OnMaterialStateChanged is not found!");

			DeleteMaterial(pMaterial);
		}
		else
		{
			UpdateMaterial(pMaterial);
		}
	}
	void RenderingPathCache::OnMeshStateChanged(MeshResource* pMesh)
	{
		/*
		* Check for something sus
		*/
		ASSERT(pMesh != nullptr, "RenderingPathCache", "OnMeshStateChanged reported a nullptr mesh!");

		/*
		* Check if the given mesh is valid
		*/
		if (pMesh->IsDestroyed())
		{
			/*
			* Validate for invalid mesh
			*/
			const int index = mMeshes.FindIndex(pMesh);
			ASSERT(index != -1, "RenderingPathCache", "The mesh given in method OnMeshStateChanged is not found!");

			DeleteMesh(pMesh);
		}
		else
		{
			UpdateMesh(pMesh);
		}
	}
	void RenderingPathCache::OnRenderTargetStateChanged(RenderTargetResource* pRenderTarget)
	{
		/*
		* Check for something sus
		*/
		ASSERT(pRenderTarget != nullptr, "RenderingPathCache", "OnRenderTargetStateteChanged reported a nullptr render target!");

		/*
		* Check if the given render target is valid
		*/
		if (pRenderTarget->IsDestroyed())
		{
			/*
			* Validate for invalid material
			*/
			const int index = mRenderTargets.FindIndex(pRenderTarget);
			ASSERT(index != -1, "RenderingPathCache", "The render target given in method OnRenderTargetStateChanged is not found!");

			DeleteRenderTarget(pRenderTarget);
		}
		else
		{
			UpdateRenderTarget(pRenderTarget);
		}
	}
	void RenderingPathCache::CreateNewMeshPathView(MeshResource* pMesh)
	{
		MeshPathView newMeshPathView = {};
		newMeshPathView.pMesh = pMesh;
		newMeshPathView.InputLayout = pMesh->GetInputLayout();

		/*
		* Create material paths using already registered materials
		*/
		for (unsigned int i = 0; i < mMaterials.GetCursor(); i++)
			CreateMaterialPathView(newMeshPathView, mMaterials[i]);

		mPathViews.Add(newMeshPathView);
	}
	void RenderingPathCache::CreateNewMaterialPathView(MaterialResource* pMaterial)
	{
		/*
		* Iterate mesh path views
		*/
		for (unsigned int meshIndex = 0; meshIndex < mPathViews.GetCursor(); meshIndex++)
		{
			MeshPathView& meshPathView = mPathViews[meshIndex];

			/*
			* Create material path view
			*/
			CreateMaterialPathView(meshPathView, pMaterial);
		}
	}
	void RenderingPathCache::CreateNewRenderTargetPathView(RenderTargetResource* pRenderTarget)
	{
		/*
		* Iterate mesh path views
		*/
		for (unsigned int meshIndex = 0; meshIndex < mPathViews.GetCursor(); meshIndex++)
		{
			MeshPathView& meshPathView = mPathViews[meshIndex];

			/*
			* Iterate material path views
			*/
			for (unsigned int materialIndex = 0; materialIndex < meshPathView.MaterialViews.GetCursor(); materialIndex++)
			{
				MaterialPathView& materialPathView = meshPathView.MaterialViews[materialIndex];

				/*
				* Create render target path view
				*/
				CreateRenderTargetPathView(meshPathView, materialPathView, pRenderTarget);
			}
		}
	}
	void RenderingPathCache::CreateRenderTargetPathView(const MeshPathView& meshPathView, MaterialPathView& materialPathView, RenderTargetResource* pRenderTarget)
	{
		/*
		* Create new render target path view and add it to the material path
		*/
		RenderTargetPathView newPathView = {};
		newPathView.pRenderTarget = pRenderTarget;
		newPathView.OutputDescription = pRenderTarget->GetOutputDesc();

		/*
		* Create new pipeline
		*/
		CreatePipeline(meshPathView, materialPathView, newPathView);

		materialPathView.RenderTargetViews.Add(newPathView);
	}
	void RenderingPathCache::CreateMaterialPathView(MeshPathView& meshPathView, MaterialResource* pMaterial)
	{
		/*
		* Create material path view
		*/
		MaterialPathView newMaterialPathView = {};
		newMaterialPathView.pMaterial = pMaterial;
		newMaterialPathView.RasterizerDesc = pMaterial->GetRasterizerState();
		newMaterialPathView.DepthStencilDesc = pMaterial->GetDepthStencilState();
		newMaterialPathView.BlendingDesc = pMaterial->GetBlendingState();
		newMaterialPathView.ResourceDesc = pMaterial->GetResourceState();
		Array<ShaderResource*> shaderResources = pMaterial->GetShaders();
		Array<Shader*> shaders;
		for (unsigned int i = 0; i < shaderResources.GetCursor(); i++)
			shaders.Add(shaderResources[i]->GetShader());
		newMaterialPathView.Shaders = shaders;

		/*
		* Create render target path views
		*/
		for (unsigned int i = 0; i < mRenderTargets.GetCursor(); i++)
		{
			CreateRenderTargetPathView(meshPathView, newMaterialPathView, mRenderTargets[i]);
		}

		/*
		* Add the material path view
		*/
		meshPathView.MaterialViews.Add(newMaterialPathView);
	}
	void RenderingPathCache::CreatePipeline(const MeshPathView& meshPathView,const MaterialPathView& materialPathView, RenderTargetPathView& renderTargetPathView)
	{
		/*
		* Create new pipeline
		*/
		GraphicsPipelineCreateDesc pipelineDesc = {};
		pipelineDesc.RasterizerState = materialPathView.RasterizerDesc;
		pipelineDesc.DepthStencilState = materialPathView.DepthStencilDesc;
		pipelineDesc.BlendingState = materialPathView.BlendingDesc;
		pipelineDesc.ResourceState = materialPathView.ResourceDesc;
		pipelineDesc.Shaders = materialPathView.Shaders;
		pipelineDesc.MeshTopology = MeshTopology::TriangleList;
		pipelineDesc.InputLayout = meshPathView.InputLayout;
		pipelineDesc.OutputDesc = renderTargetPathView.OutputDescription;
		Pipeline* pPipeline = mOwnerDevice->CreateGraphicsPipeline(pipelineDesc);

		renderTargetPathView.pPipeline = pPipeline;
	}
	void RenderingPathCache::UpdateMeshPathView(MeshPathView& pathView,const bool bUpdateSelf)
	{
		/*
		* Update the input layout
		*/
		if(bUpdateSelf)
			pathView.InputLayout = pathView.InputLayout = pathView.pMesh->GetInputLayout();

		/*
		* Iterate and update the sub material path views
		*/
		for (unsigned int i = 0; i < pathView.MaterialViews.GetCursor(); i++)
			UpdateMaterialPathView(pathView, pathView.MaterialViews[i],false);
	}
	void RenderingPathCache::UpdateMaterialPathView(const MeshPathView& meshPathView, MaterialPathView& materialPathView,const bool bUpdateSelf)
	{
		/*
		* Update the material path view
		*/
		if (bUpdateSelf)
		{
			materialPathView.RasterizerDesc = materialPathView.pMaterial->GetRasterizerState();
			materialPathView.DepthStencilDesc = materialPathView.pMaterial->GetDepthStencilState();
			materialPathView.BlendingDesc = materialPathView.pMaterial->GetBlendingState();
			materialPathView.ResourceDesc = materialPathView.pMaterial->GetResourceState();
			materialPathView.Shaders.Clear();
			Array<ShaderResource*> shaderResources = materialPathView.pMaterial->GetShaders();
			Array<Shader*> shaders;
			for (unsigned int i = 0; i < shaderResources.GetCursor(); i++)
				shaders.Add(shaderResources[i]->GetShader());
			materialPathView.Shaders = shaders;
		}

		/*
		* Create sub render target path views
		*/
		for (unsigned int i = 0; i < materialPathView.RenderTargetViews.GetCursor(); i++)
			UpdateRenderTargetPathView(meshPathView, materialPathView, materialPathView.RenderTargetViews[i],false);
	}
	void RenderingPathCache::UpdateRenderTargetPathView(const MeshPathView& meshPathView, const MaterialPathView& materialPathView, RenderTargetPathView& renderTargetPathView,const bool bUpdateSelf)
	{
		/*
		* Update render target view
		*/
		if (bUpdateSelf)
		{
			renderTargetPathView.OutputDescription = renderTargetPathView.pRenderTarget->GetOutputDesc();
		}

		/*
		* Validate and delete former pipeline
		*/
		if (renderTargetPathView.pPipeline == nullptr)
		{
			renderTargetPathView.pPipeline->Destroy();
			renderTargetPathView.pPipeline = nullptr;
		}

		/*
		* Create pipeline
		*/
		CreatePipeline(meshPathView, materialPathView, renderTargetPathView);
	}
	void RenderingPathCache::DeleteMesh(MeshResource* pMesh)
	{
		/*
		* Validate for invalid mesh
		*/
		const int index = mMeshes.FindIndex(pMesh);
		ASSERT(index != -1, "RenderingPathCache", "The mesh given in method OnMeshStateChanged is not found!");

		/*
		* Delete path view
		*/
		DeleteMeshPathView(mPathViews[index]);

		/*
		* Remove path  from the list
		*/
		mPathViews.RemoveIndex(index);

	}
	void RenderingPathCache::DeleteMaterial(MaterialResource* pMaterial)
	{
		/*
		* Validate for invalid mesh
		*/
		const int index = mMaterials.FindIndex(pMaterial);
		ASSERT(index != -1, "RenderingPathCache", "The mesh given in method OnMaterialStateChanged is not found!");

		/*
		* Iterate each mesh path view and delete the found index of the material path
		*/
		for (unsigned int i = 0; i < mPathViews.GetCursor(); i++)
		{
			/*
			* Delete material path
			*/
			MeshPathView& pathView = mPathViews[i];
			DeleteMaterialPathView(pathView.MaterialViews[index]);

			/*
			* Remove it from the list
			*/
			pathView.MaterialViews.RemoveIndex(index);
		}
	}
	void RenderingPathCache::DeleteRenderTarget(RenderTargetResource* pRenderTarget)
	{
		/*
		* Validate for invalid mesh
		*/
		const int index = mRenderTargets.FindIndex(pRenderTarget);
		ASSERT(index != -1, "RenderingPathCache", "The mesh given in method OnRenderTargetStateChanged is not found!");

		/*
		* Iterate each mesh path view
		*/
		for (unsigned int meshIndex = 0; meshIndex < mPathViews.GetCursor(); meshIndex++)
		{
			/*
			* Iterate each material path view and delete the found index of the render target
			*/
			MeshPathView& meshPathView = mPathViews[meshIndex];
			for (unsigned int materialIndex = 0; materialIndex < meshPathView.MaterialViews.GetCursor(); materialIndex++)
			{
				/*
				* Delete the render target path view
				*/
				MaterialPathView& materialPathView = meshPathView.MaterialViews[materialIndex];
				DeleteRenderTargetPathView(materialPathView.RenderTargetViews[index]);

				/*
				* Remove it from the list
				*/
				materialPathView.RenderTargetViews.RemoveIndex(index);
			}
		}
	}
	void RenderingPathCache::UpdateMesh(MeshResource* pMesh)
	{
		/*
		* Validate for invalid mesh
		*/
		const int index = mMeshes.FindIndex(pMesh);
		ASSERT(index != -1, "RenderingPathCache", "The mesh given in method OnMeshStateChanged is not found!");

		/*
		* Update the mesh path view
		*/
		UpdateMeshPathView(mPathViews[index], true);
	}
	void RenderingPathCache::UpdateMaterial(MaterialResource* pMaterial)
	{
		/*
		* Validate for invalid mesh
		*/
		const int index = mMaterials.FindIndex(pMaterial);
		ASSERT(index != -1, "RenderingPathCache", "The mesh given in method OnMaterialStateChanged is not found!");

		/*
		* Iterate and update the material path view
		*/
		for (unsigned int i = 0; i < mPathViews.GetCursor(); i++)
			UpdateMaterialPathView(mPathViews[i], mPathViews[i].MaterialViews[index], true);
	}
	void RenderingPathCache::UpdateRenderTarget(RenderTargetResource* pRenderTarget)
	{
		/*
		* Validate for invalid mesh
		*/
		const int index = mRenderTargets.FindIndex(pRenderTarget);
		ASSERT(index != -1, "RenderingPathCache", "The mesh given in method OnRenderTargetStateChanged is not found!");

		/*
		* Iterate mesh path views
		*/
		for (unsigned int meshIndex = 0; meshIndex < mPathViews.GetCursor(); meshIndex++)
		{
			/*
			* Iterate material path views
			*/
			MeshPathView& meshPathView = mPathViews[meshIndex];
			for (unsigned int materialIndex = 0; materialIndex < meshPathView.MaterialViews.GetCursor(); materialIndex++)
			{
				/*
				* Update render target path view
				*/
				MaterialPathView& materialPathView = meshPathView.MaterialViews[materialIndex];
				UpdateRenderTargetPathView(meshPathView, materialPathView, materialPathView.RenderTargetViews[index], true);
			}
		}
	}
	void RenderingPathCache::DeleteMeshPathView(MeshPathView& pathView)
	{
		/*
		* Reset mesh path view state
		*/
		pathView.InputLayout = {};
		pathView.pMesh = nullptr;

		/*
		* Delete sub material path views
		*/
		for (unsigned int i = 0; i < pathView.MaterialViews.GetCursor(); i++)
			DeleteMaterialPathView(pathView.MaterialViews[i]);
	}
	void RenderingPathCache::DeleteMaterialPathView(MaterialPathView& materialPathView)
	{
		/*
		* Reset material path view state
		*/
		materialPathView.RasterizerDesc = {};
		materialPathView.DepthStencilDesc = {};
		materialPathView.BlendingDesc = {};
		materialPathView.ResourceDesc = {};
		materialPathView.Shaders.Clear();
		materialPathView.pMaterial = nullptr;

		/*
		* Delete sub render target path views
		*/
		for (unsigned int i = 0; i < materialPathView.RenderTargetViews.GetCursor(); i++)
			DeleteRenderTargetPathView(materialPathView.RenderTargetViews[i]);
	}
	void RenderingPathCache::DeleteRenderTargetPathView(RenderTargetPathView& renderTargetPathView)
	{
		/*
		* Reset render target path view state
		*/
		renderTargetPathView.OutputDescription = {};
		renderTargetPathView.pRenderTarget = nullptr;

		/*
		* Delete pipeline
		*/
		if (renderTargetPathView.pPipeline != nullptr)
		{
			renderTargetPathView.pPipeline->Destroy();
			renderTargetPathView.pPipeline = nullptr;
		}

	}
	void RenderingPathCache::DestroyCore()
	{
		/*
		* Destroy all
		*/
		for (unsigned int i = 0; i < mMeshes.GetCursor(); i++)
			DeleteMesh(mMeshes[i]);

		mMaterials.Clear();
		mMeshes.Clear();
		mRenderTargets.Clear();
		mPathViews.Clear();
		mOwnerDevice = nullptr;
	}
}
