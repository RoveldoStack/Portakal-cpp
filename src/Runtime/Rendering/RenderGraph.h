#pragma once
#include <Runtime/Resource/Material/MaterialResource.h>
#include <Runtime/Resource/Mesh/MeshResource.h>
#include <Runtime/Resource/RenderTarget/RenderTargetResource.h>
#include <Runtime/Graphics/Pipeline/Pipeline.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Containers/Registry.h>
#include <Runtime/Rendering/RenderPass.h>
#include <Runtime/Containers/Registry.h>
#include <Runtime/Rendering/InputOutputs.h>
#include <Runtime/Math/Color4.h>
#include <Runtime/Resource/Material/MaterialResource.h>
#include <Runtime/Resource/Mesh/MeshResource.h>
#include <Runtime/Resource/RenderTarget/RenderTargetResource.h>
#include <Runtime/Rendering/RenderingPathCache.h>

namespace Portakal
{
	/// <summary>
	/// Represents an isolated rendering state and execution context
	/// RenderGraph provides both cached pipeline state and execution context
	/// </summary>
	class PORTAKAL_API RenderGraph final : public TaggedObject
	{
		friend class RenderPass;
	public:
		struct CompiledPassSet
		{
			Array<RenderPass*> Passes;
		};
	public:
		RenderGraph();
		virtual ~RenderGraph();

		/// <summary>
		/// Returns the rendering path cache assigned to the render graph
		/// </summary>
		/// <returns></returns>
		FORCEINLINE RenderingPathCache* GetRenderingPathCache() const noexcept { return mPathCache; }

		/// <summary>
		/// Returns the globa lIO pin with name
		/// </summary>
		/// <returns></returns>
		RenderPassInputOutput* GetGlobalIO(const String& name) const noexcept;

		/// <summary>
		/// Returns the finish IO pin of this render graph
		/// </summary>
		/// <returns></returns>
		FORCEINLINE RenderPass* GetFinishPass() const noexcept { return mFinishPass; }

		/// <summary>
		/// Creates anew render target global slot
		/// </summary>
		/// <param name="name"></param>
		void CreateGlobalRenderTarget(const String& name);

		/// <summary>
		/// Creates anew color global slot
		/// </summary>
		/// <param name="name"></param>
		void CreateGlobalColorRgbaF(const String& name);

		/// <summary>
		/// Creates anew mesh global slot
		/// </summary>
		/// <param name="name"></param>
		void CreateGlobalMesh(const String& name);

		/// <summary>
		/// Creates anew material global slot
		/// </summary>
		/// <param name="name"></param>
		void CreateGlobalMaterial(const String& name);

		/// <summary>
		/// Creates anew texture global slot
		/// </summary>
		/// <param name="name"></param>
		void CreateGlobalTexture(const String& name);

		/// <summary>
		/// Sets the existing render target stot with the given name
		/// </summary>
		/// <param name="name"></param>
		/// <param name="pRenderTarget"></param>
		void SetGlobalRenderTarget(const String& name,RenderTargetResource* pRenderTarget);

		/// <summary>
		/// Sets the existing color slot with the given name
		/// </summary>
		/// <param name="name"></param>
		/// <param name="value"></param>
		void SetGlobalColorRgbaF(const String& name, const ColorRgbaF& value);

		/// <summary>
		/// Sets the existing mesh slot with the given name
		/// </summary>
		/// <param name="name"></param>
		/// <param name="pMesh"></param>
		void SetGlobalMesh(const String& name, MeshResource* pMesh);

		/// <summary>
		/// Sets the existing material slot with the given name
		/// </summary>
		/// <param name="name"></param>
		/// <param name="pMaterial"></param>
		void SetGlobalMaterial(const String& name, MaterialResource* pMaterial);

		/// <summary>
		/// Sets the existing texture slot with the given name
		/// </summary>
		/// <param name="name"></param>
		/// <param name="pTexture"></param>
		void SetGlobalTexture(const String& name, TextureResource* pTexture);

		/// <summary>
		/// Connects a global render target to a pin of the existing rendering pass
		/// </summary>
		/// <param name="name"></param>
		/// <param name="pInput"></param>
		void ConnectGlobalOutput(const String& name,RenderPassInputOutput* pInput);

		/// <summary>
		/// Connects an output pin to the finish IO
		/// </summary>
		/// <param name="pOutput"></param>
		void SetFinishPass(RenderPass* pPass);

		/// <summary>
		/// Registers anew material for the render graph.
		/// </summary>
		/// <param name="pMaterial"></param>
		void RegisterMaterial(MaterialResource* pMaterial);

		/// <summary>
		/// Removes the existing material from the render graph
		/// </summary>
		/// <param name="pMaterial"></param>
		void RemoveMaterial(MaterialResource* pMaterial);

		/// <summary>
		/// Registers anew mesh to the render graph
		/// </summary>
		/// <param name="pMesh"></param>
		void RegisterMesh(MeshResource* pMesh);

		/// <summary>
		/// Removes the existing mesh from the render graph
		/// </summary>
		/// <param name="pmesh"></param>
		void RemoveMesh(MeshResource* pMesh);

		/// <summary>
		/// Registers anew render target to the render graph
		/// </summary>
		/// <param name="pRenderTarget"></param>
		void RegisterRenderTarget(RenderTargetResource* pRenderTarget);

		/// <summary>
		/// Removes the existing render target from the render graph
		/// </summary>
		/// <param name="pRenderTarget"></param>
		void RemoveRenderTarget(RenderTargetResource* pRenderTarget);

		/// <summary>
		/// Executes the render graph on the current thread only
		/// </summary>
		/// <param name="pCmdList"></param>
		void ExecuteSync(CommandList* pCmdList);

		/// <summary>
		/// Executes the render graph on other thread
		/// </summary>
		void ExecuteAsync();

		/// <summary>
		/// Compiles the current state of the execution context and flattens it to a monolithic queue
		/// </summary>
		void Compile();

		/// <summary>
		/// Deletes the given pass from the graph
		/// </summary>
		/// <param name="pPass"></param>
		/// <returns></returns>
		bool DeletePass(RenderPass* pPass);

		/// <summary>
		/// Creates anew pass for the graph
		/// </summary>
		/// <typeparam name="TPass"></typeparam>
		/// <returns></returns>
		template<typename TPass>
		TPass* CreatePass()
		{
			/*
			* Create new pass
			*/
			TPass* pPass = new TPass();
			pPass->_SetOwnerGraph(this);

			/*
			* Register the pass
			*/
			mPasses.Add(pPass);

			/*
			* Mark the graph dirty
			*/
			_MarkGraphDirty();

			return pPass;
		}
	private:
		void _MarkGraphDirty();

		// Inherited via TaggedObject
		virtual void DestroyCore() override;
	private:
		Array<RenderPass*> mPasses;
		Array<CompiledPassSet> mCompiledPassSets;
		Registry<String, RenderPassInputOutput*> mGlobals;
		RenderPass* mFinishPass;
		RenderingPathCache* mPathCache;
		bool mCompiled;
		bool mDirty;

};
}