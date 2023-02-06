#pragma once
#include <Runtime/Graphics/GraphicsDeviceObjectType.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class GraphicsDevice;

	class PORTAKAL_API GraphicsDeviceObject
	{
		friend class GraphicsDevice;
	public:
		FORCEINLINE void SetDeviceObjectName(const String& name) { mName = name; }

		FORCEINLINE GraphicsDevice* GetOwnerDevice() const noexcept { return mOwnerDevice; }
		FORCEINLINE String GetDeviceObjectName() const noexcept { return mName; }
		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept = 0;

		void DeleteDeviceObject();
	protected:
		GraphicsDeviceObject()
		{
			mOwnerDevice = nullptr;
		}
		~GraphicsDeviceObject()
		{
			mOwnerDevice = nullptr;
		}

		virtual void OnDestroy() = 0;
	private:
		void _SetOwnerDevice(GraphicsDevice* pDevice) { mOwnerDevice = pDevice; }
	private:
		GraphicsDevice* mOwnerDevice;
		String mName;
	};
}