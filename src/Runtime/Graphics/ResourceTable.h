#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/ResourceTableCreateDesc.h>

namespace Portakal
{
	class PORTAKAL_API ResourceTable : public GraphicsDeviceObject
	{
	public:
		FORCEINLINE Array<GraphicsDeviceObject*> GetResources() const noexcept { return _resources; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::ResourceTable; }

		FORCEINLINE virtual void* GetHandle() const noexcept = 0;
	protected:
		ResourceTable(const ResourceTableCreateDesc& desc) : _resources(desc.Resources) {}
		virtual ~ResourceTable() {}

	private:
		const Array<GraphicsDeviceObject*> _resources;
	};
}