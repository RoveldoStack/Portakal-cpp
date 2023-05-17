#pragma once
#include <Runtime/Object/API.h>
#include <Runtime/Containers/Array.h>

namespace Portakal
{
	class MeshResource;
	class MaterialResource;
	class RenderTargetResource;

	class PORTAKAL_API RenderingCacheAPI : public API<RenderingCacheAPI>
	{
	public:
		static void RegisterMesh(const MeshResource* pMesh);
		static void RegisterMaterial(const MaterialResource* pMaterial);
		static void RegisterRenderTarget(const RenderTargetResource* pRenderTarget);
		static void RemoveMesh(const MeshResource* pMesh);
		static void RemoveMaterial(const MaterialResource* pMaterial);
		static void RemoveRenderTarget(const RenderTargetResource* pRenderTarget);
	private:
		Array<MeshResource*> mMeshes;
		Array<MaterialResource*> mMaterials;
		Array<RenderTargetResource*> mRenderTargets;
	};
}