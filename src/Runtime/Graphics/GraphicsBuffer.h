#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/GraphicsBufferCreateDesc.h>

namespace Portakal
{
	/// <summary>
	/// Represents a gpu allocated buffer
	/// </summary>
	class PORTAKAL_API GraphicsBuffer : public GraphicsDeviceObject
	{
	public:
		/// <summary>
		/// Returns the buffer type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE GraphicsBufferType GetBufferType() const noexcept { return mType; }

		/// <summary>
		/// Returns the sub item size in bytes
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long long GetSubItemSize() const noexcept { return mSubItemSize; }

		/// <summary>
		/// Returns the sub item count
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long long GetSubItemCount() const noexcept { return mSubItemCount; }

		/// <summary>
		/// Returns the total buffer size in bytes
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long long GetTotalBufferSize() const noexcept { return mSubItemCount * mSubItemSize; }
		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override { return GraphicsDeviceObjectType::Buffer; }
	protected:
		GraphicsBuffer(const GraphicsBufferCreateDesc& desc) : mType(desc.Type), mSubItemSize(desc.SubItemSize), mSubItemCount(desc.SubItemCount) {}
		virtual ~GraphicsBuffer() {}
	private:
		const GraphicsBufferType mType;
		unsigned long long mSubItemSize;
		unsigned long long mSubItemCount;
	};
}