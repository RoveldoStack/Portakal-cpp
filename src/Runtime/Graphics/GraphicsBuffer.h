#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/GraphicsBufferCreateDesc.h>

namespace Portakal
{
	class PORTAKAL_API GraphicsBuffer : public GraphicsDeviceObject
	{
	public:
		FORCEINLINE GraphicsBufferType GetBufferType() const noexcept { return _type; }
		FORCEINLINE unsigned long long GetSubItemSize() const noexcept { return _subItemSize; }
		FORCEINLINE unsigned long long GetSubItemCount() const noexcept { return _subItemCount; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override { return GraphicsDeviceObjectType::Buffer; }
	protected:
		GraphicsBuffer(const GraphicsBufferCreateDesc& desc) : _type(desc.Type),_subItemSize(desc.SubItemSize),_subItemCount(desc.SubItemCount) {}
		virtual ~GraphicsBuffer() {}
	private:
		const GraphicsBufferType _type;
		unsigned long long _subItemSize;
		unsigned long long _subItemCount;
	};
}