#pragma once
#include <Runtime/Graphics/GraphicsDeviceObjectType.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class GraphicsDevice;

	/// <summary>
	/// Represents a graphics device object inherited by the owner graphics device
	/// </summary>
	class PORTAKAL_API GraphicsDeviceObject
	{
		friend class GraphicsDevice;
	public:
		/// <summary>
		/// Sets the device debug name
		/// </summary>
		/// <param name="name"></param>
		FORCEINLINE void SetDeviceObjectName(const String& name) { mName = name; }

		/// <summary>
		/// Returns the owner device
		/// </summary>
		/// <returns></returns>
		FORCEINLINE GraphicsDevice* GetOwnerDevice() const noexcept { return mOwnerDevice; }

		/// <summary>
		/// Returns whether this device object is destroyed or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsDestroyed() const noexcept { return mDestroyed; }

		/// <summary>
		/// Returns the device debug name
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetDeviceObjectName() const noexcept { return mName; }
		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept = 0;

		/// <summary>
		/// Deletes the device object
		/// </summary>
		void Destroy();
	protected:
		GraphicsDeviceObject()
		{
			mOwnerDevice = nullptr;
			mDestroyed = false;
		}
		~GraphicsDeviceObject()
		{
			mOwnerDevice = nullptr;
		}

		virtual void OnDestroy() = 0;
	private:

		/// <summary>
		/// Internal setter for the owner device
		/// </summary>
		/// <param name="pDevice"></param>
		void _SetOwnerDevice(GraphicsDevice* pDevice) { mOwnerDevice = pDevice; }
	private:
		GraphicsDevice* mOwnerDevice;
		String mName;
		bool mDestroyed;
	};
}