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
		FORCEINLINE void SetDeviceObjectName(const String& name) { _name = name; }

		FORCEINLINE GraphicsDevice* GetOwnerDevice() const noexcept { return _ownerDevice; }
		FORCEINLINE String GetDeviceObjectName() const noexcept { return _name; }
		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept = 0;

		void DeleteDeviceObject();
	protected:
		GraphicsDeviceObject() = default;
		virtual ~GraphicsDeviceObject();

		virtual void Initialize() = 0;
	private:
		void _SetOwnerDevice(GraphicsDevice* pDevice) { _ownerDevice = pDevice; }
	private:
		GraphicsDevice* _ownerDevice;
		String _name;
	};
}