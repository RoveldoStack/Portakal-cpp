#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/Resource/ResourceTableCreateDesc.h>

namespace Portakal
{
	/// <summary>
	/// Represents a commitable resource table to the pipeline
	/// </summary>
	class PORTAKAL_API ResourceTable : public GraphicsDeviceObject
	{
	public:
		/// <summary>
		/// Returns the resources populated in this table
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Array<GraphicsDeviceObject*>& GetBuffers() const noexcept { return mBuffers; }
		FORCEINLINE const Array<GraphicsDeviceObject*>& GetTextures() const noexcept { return mTextures; }
		FORCEINLINE const Array<GraphicsDeviceObject*>& GetSamplers() const noexcept { return mSamplers; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::ResourceTable; }

		FORCEINLINE bool HasBuffers() const noexcept { return mHasBuffers; }
		FORCEINLINE bool HasTextures() const noexcept { return mHasTextures; }
		FORCEINLINE bool HasSamplers() const noexcept { return mHasSamplers; }
	protected:
		ResourceTable(const ResourceTableCreateDesc& desc);
		virtual ~ResourceTable() {}

	private:
		const Array<GraphicsDeviceObject*> mBuffers;
		const Array<GraphicsDeviceObject*> mTextures;
		const Array<GraphicsDeviceObject*> mSamplers;
		bool mHasBuffers;
		bool mHasTextures;
		bool mHasSamplers;
	};
}