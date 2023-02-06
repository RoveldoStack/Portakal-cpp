#pragma once
#include <Runtime/Object/TaggedObject.h>

namespace Portakal
{
	class Entity;

	class PORTAKAL_API Component : public TaggedObject
	{
		friend class Entity;
	public:
		FORCEINLINE Entity* GetOwnerEntity() const noexcept { return mOwnerEntity; }

		void DestroyComponent();
		virtual void OnInitialize() = 0;
		virtual void OnFinalize() = 0;

	protected:
		Component() = default;
	private:
		~Component() = default;

		void _SetOwnerEntity(Entity* pEntity) { mOwnerEntity = pEntity; }
	private:
		Entity* mOwnerEntity;
	};
}