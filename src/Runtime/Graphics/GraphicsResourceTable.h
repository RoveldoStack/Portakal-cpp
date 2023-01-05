#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/GraphicsResourceTableCreateDesc.h>

namespace Portakal
{
	class PORTAKAL_API GraphicsResourceTable : public GraphicsDeviceObject
	{
	public:
		FORCEINLINE Array<GraphicsDeviceObject*> GetResources() const noexcept { return _resources; }
		FORCEINLINE GraphicsResourceTableTarget GetTarget() const noexcept { return _target; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::ResourceTable; }
	protected:
		GraphicsResourceTable(const GraphicsResourceTableCreateDesc& desc) : _resources(desc.Resources),_target(desc.Target) {}
		virtual ~GraphicsResourceTable() {}

	private:
		const Array<GraphicsDeviceObject*> _resources;
		const GraphicsResourceTableTarget _target;
	};
}