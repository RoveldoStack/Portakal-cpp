#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/ResourceTableCreateDesc.h>

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
		FORCEINLINE Array<GraphicsDeviceObject*> GetResources() const noexcept { return _resources; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::ResourceTable; }

		/// <summary>
		/// Returns the native handle
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual void* GetHandle() const noexcept = 0;
	protected:
		ResourceTable(const ResourceTableCreateDesc& desc) : _resources(desc.Resources) {}
		virtual ~ResourceTable() {}

	private:
		const Array<GraphicsDeviceObject*> _resources;
	};
}