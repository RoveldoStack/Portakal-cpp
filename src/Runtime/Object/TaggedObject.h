#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	class PORTAKAL_API TaggedObject : public Class
	{
		GENERATE_CLASS(TaggedObject);
	public:
		FORCEINLINE String GetTagName() const noexcept { return mName; }
		FORCEINLINE void SetTagName(const String& name) { mName = name; }
		FORCEINLINE Guid GetID() const noexcept { return mID; }
		FORCEINLINE bool IsDestroyed() const noexcept { return mDestroyed; }
		void OverrideID(const Guid& id) { mID = id; }
		void Destroy()
		{
			DestroyCore();
			mDestroyed = true;
		}
	protected:
		TaggedObject(const String& name,const Guid& id) : mName(name), mID(id),mDestroyed(false) {}
		TaggedObject(const String& name) : mName(name), mID(Guid::Create()),mDestroyed(false) {}
		TaggedObject(const Guid& id) : mID(id),mDestroyed(false) {}
		TaggedObject() : mDestroyed(false) {}

		~TaggedObject() = default;

		virtual void DestroyCore() = 0;
	private:
		String mName;
		Guid mID;
		bool mDestroyed;

	};
	START_GENERATE_TYPE(TaggedObject);
		START_TYPE_PROPERTIES(TaggedObject);
		END_TYPE_PROPERTIES;
		VIRTUAL_TYPE;
	END_GENERATE_TYPE(TaggedObject);

	/*FORCEINLINE bool operator ==(const TaggedObject& a, const TaggedObject& b)
	{
		return a.GetID() == b.GetID();
	}
	FORCEINLINE bool operator !=(const TaggedObject& a, const TaggedObject& b)
	{
		return a.GetID() != b.GetID();
	}*/
}