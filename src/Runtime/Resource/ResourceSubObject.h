#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class Resource;

	class PORTAKAL_API ResourceSubObject
	{
		friend class Resource;
	public:
		ResourceSubObject() : _ownerResource(nullptr),_destroyed(false) {}

		FORCEINLINE bool IsVirtualSubObject() const noexcept { return _ownerResource == nullptr; }
		FORCEINLINE bool IsDestroyed() const noexcept { return _destroyed; }

		void DestroySubObject()
		{
			DestroySubObjectCore();

			_destroyed = true;
		}

	protected:
		virtual void DestroySubObjectCore() = 0;
	private:
		void _SetOwnerResource(Resource* pResource) { _ownerResource = pResource; }
	private:
		Resource* _ownerResource;
		bool _destroyed;
	};
}