#pragma once
#include <Runtime/Object/TaggedObject.h>

namespace Portakal
{
	class Entity;

	class PORTAKAL_API Component : public TaggedObject
	{
		friend class Entity;
	public:
		FORCEINLINE Entity* GetOwnerEntity() const noexcept { return _ownerEntity; }

		void DestroyComponent();
		virtual void OnInitialize() = 0;
		virtual void OnFinalize() = 0;

	protected:
		Component() = default;
	private:
		~Component() = default;

		void _SetOwnerEntity(Entity* pEntity) { _ownerEntity = pEntity; }
	private:
		Entity* _ownerEntity;
	};
}