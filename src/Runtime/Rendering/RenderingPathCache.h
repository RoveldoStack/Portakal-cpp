#pragma once
#include <Runtime/Resource/Material/MaterialResource.h>
#include <Runtime/Resource/Mesh/MeshResource.h>
#include <Runtime/Resource/RenderTarget/RenderTargetResource.h>
#include <Runtime/Graphics/Pipeline/Pipeline.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Object/TaggedObject.h>

namespace Portakal
{
	/// <summary>
	/// Represents a blob of rendering path pipeline cache
	/// </summary>
	class PORTAKAL_API RenderingPathCache final : public TaggedObject
	{
	public:
		RenderingPathCache();
		~RenderingPathCache();

		/// <summary>
		/// Returns the registered meshes
		/// </summary>
		/// <returns></returns>
		const Array<MeshResource*>& GetMeshes() const noexcept { return mMeshes; }

		/// <summary>
		/// Returns the registered materials
		/// </summary>
		/// <returns></returns>
		const Array<MaterialResource*>& GetMaterials() const noexcept { return mMaterials; }

		/// <summary>
		/// Returns the registered render targets
		/// </summary>
		/// <returns></returns>
		const Array<RenderTargetResource*>& GetRenderTargets() const noexcept { return mRenderTargets; }

		/// <summary>
		/// Finds a single pipeline
		/// </summary>
		/// <param name="pMesh"></param>
		/// <param name="pMaterial"></param>
		/// <param name="pRenderTarget"></param>
		/// <returns></returns>
		Pipeline* GetSinglePipeline(MeshResource* pMesh, MaterialResource* pMaterial, RenderTargetResource* pRenderTarget);

		/// <summary>
		/// Registers anew material to the cache
		/// </summary>
		/// <param name="pMaterial"></param>
		void RegisterMaterial(MaterialResource* pMaterial);

		/// <summary>
		/// Registers anew mesh to the cache
		/// </summary>
		/// <param name="pMesh"></param>
		void RegisterMesh(MeshResource* pMesh);

		/// <summary>
		/// Registers anew render target to the cache
		/// </summary>
		/// <param name="pRenderTarget"></param>
		void RegisterRenderTarget(RenderTargetResource* pRenderTarget);

		/// <summary>
		/// Removes the existing material from the cache
		/// </summary>
		/// <param name="pMaterial"></param>
		void RemoveMaterial(MaterialResource* pMaterial);

		/// <summary>
		/// Removes the existing mesh from the cache
		/// </summary>
		/// <param name="pMesh"></param>
		void RemoveMesh(MeshResource* pMesh);

		/// <summary>
		/// Removes the existing render target from the cache
		/// </summary>
		/// <param name="pRenderTarget"></param>
		void RemoveRenderTarget(RenderTargetResource* pRenderTarget);
	private:
		struct RenderTargetPathView
		{
			RenderTargetResource* pRenderTarget;
			OutputDesc OutputDescription;
			Pipeline* pPipeline;
		};
		struct MaterialPathView
		{
			MaterialResource* pMaterial;
			RasterizerStateDesc RasterizerDesc;
			DepthStencilStateDesc DepthStencilDesc;
			BlendingStateDesc BlendingDesc;
			ResourceStateDesc ResourceDesc;
			Array<Shader*> Shaders;
			Array<RenderTargetPathView> RenderTargetViews;
		};
		struct MeshPathView
		{
			MeshResource* pMesh;
			InputLayoutDesc InputLayout;
			Array<MaterialPathView> MaterialViews;
		};
	private:
		/// <summary>
		/// Called upon when material resource is signaled that it's state has changed
		/// </summary>
		/// <param name="pMaterial"></param>
		void OnMaterialStateChanged(MaterialResource* pMaterial);

		/// <summary>
		/// Called upon when mesh resource is signaled that it's state has changed
		/// </summary>
		/// <param name="pMesh"></param>
		void OnMeshStateChanged(MeshResource* pMesh);

		/// <summary>
		/// Called upon when render target resource is signaled that it's state has changed
		/// </summary>
		/// <param name="pRenderTarget"></param>
		void OnRenderTargetStateChanged(RenderTargetResource* pRenderTarget);

		/// <summary>
		/// Creates anew mesh path view out of the given mesh
		/// </summary>
		/// <param name="pMesh"></param>
		void CreateNewMeshPathView(MeshResource* pMesh);

		/// <summary>
		/// Creates anew material path view out of the given material
		/// </summary>
		/// <param name="pMaterial"></param>
		void CreateNewMaterialPathView(MaterialResource* pMaterial);

		/// <summary>
		/// Creates anew render target path view out of the given render target
		/// </summary>
		/// <param name="pRenderTarget"></param>
		void CreateNewRenderTargetPathView(RenderTargetResource* pRenderTarget);

		/// <summary>
		/// Creates render target path view for the given mesh and material view
		/// </summary>
		/// <param name="meshPathView"></param>
		/// <param name="materialPathView"></param>
		/// <param name="pRenderTarget"></param>
		void CreateRenderTargetPathView(const MeshPathView& meshPathView, MaterialPathView& materialPathView, RenderTargetResource* pRenderTarget);

		/// <summary>
		/// Creates material path view for the given mesh view
		/// </summary>
		/// <param name="meshPathView"></param>
		/// <param name="pMaterial"></param>
		void CreateMaterialPathView(MeshPathView& meshPathView, MaterialResource* pMaterial);

		/// <summary>
		/// Creates anew pipeline for the given mesh,material and render target path views
		/// </summary>
		/// <param name="meshPathView"></param>
		/// <param name="materialPathView"></param>
		/// <param name="renderTargetPathView"></param>
		void CreatePipeline(const MeshPathView& meshPathView,const MaterialPathView& materialPathView, RenderTargetPathView& renderTargetPathView);

		/// <summary>
		/// Updates the path views of the given mesh
		/// </summary>
		/// <param name="pMesh"></param>
		void UpdateMesh(MeshResource* pMesh);

		/// <summary>
		/// Updates the path views of the given material
		/// </summary>
		/// <param name="pMaterial"></param>
		void UpdateMaterial(MaterialResource* pMaterial);

		/// <summary>
		/// Updates the path views of the given render target
		/// </summary>
		/// <param name="pRenderTarget"></param>
		void UpdateRenderTarget(RenderTargetResource* pRenderTarget);

		/// <summary>
		/// Updates the given mesh path view
		/// </summary>
		/// <param name="pathView"></param>
		/// <param name="bUpdateSelf"></param>
		void UpdateMeshPathView(MeshPathView& pathView,const bool bUpdateSelf);

		/// <summary>
		/// Updates the given material path view
		/// </summary>
		/// <param name="meshPathView"></param>
		/// <param name="materialPathView"></param>
		/// <param name="bUpdateSelf"></param>
		void UpdateMaterialPathView(const MeshPathView& meshPathView, MaterialPathView& materialPathView,const bool bUpdateSelf);

		/// <summary>
		/// Updates the given render target path view
		/// </summary>
		/// <param name="meshPathView"></param>
		/// <param name="materialPathView"></param>
		/// <param name="renderTargetPathView"></param>
		/// <param name="bUpdateSelf"></param>
		void UpdateRenderTargetPathView(const MeshPathView& meshPathView, const MaterialPathView& materialPathView, RenderTargetPathView& renderTargetPathView,const bool bUpdateSelf);

		/// <summary>
		/// Deletes the given mesh path views
		/// </summary>
		/// <param name="pMesh"></param>
		void DeleteMesh(MeshResource* pMesh);

		/// <summary>
		/// Deletes the given material path views
		/// </summary>
		/// <param name="pMaterial"></param>
		void DeleteMaterial(MaterialResource* pMaterial);

		/// <summary>
		/// Deletes the given render target path views
		/// </summary>
		/// <param name="pRenderTarget"></param>
		void DeleteRenderTarget(RenderTargetResource* pRenderTarget);

		/// <summary>
		/// Deletes the given mesh path view
		/// </summary>
		/// <param name="pathView"></param>
		void DeleteMeshPathView(MeshPathView& pathView);

		/// <summary>
		/// Deletes the given material path view
		/// </summary>
		/// <param name="materialPathView"></param>
		void DeleteMaterialPathView(MaterialPathView& materialPathView);

		/// <summary>
		/// Deletes the given render target path view
		/// </summary>
		/// <param name="renderTargetPathView"></param>
		void DeleteRenderTargetPathView(RenderTargetPathView& renderTargetPathView);

		// Inherited via TaggedObject
		virtual void DestroyCore() override;
	private:
		Array<MaterialResource*> mMaterials;
		Array<MeshResource*> mMeshes;
		Array<RenderTargetResource*> mRenderTargets;
		Array<MeshPathView> mPathViews;
		GraphicsDevice* mOwnerDevice;

};
}