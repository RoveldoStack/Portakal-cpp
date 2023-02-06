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

		void OverrideID(const Guid& id) { mID = id; }
	protected:
		TaggedObject(const String& name,const Guid& id) : mName(name), mID(id) {}
		TaggedObject(const String& name) : mName(name), mID(Guid::Create()) {}
		TaggedObject(const Guid& id) : mID(id) {}
		TaggedObject() = default;

		~TaggedObject() = default;

	private:
		String mName;
		Guid mID;
	};
	START_GENERATE_TYPE(TaggedObject);
		START_TYPE_PROPERTIES(TaggedObject);
		END_TYPE_PROPERTIES;
		CONCRETE_TYPE(TaggedObject);
	END_GENERATE_TYPE(TaggedObject);


	FORCEINLINE bool operator ==(const TaggedObject& a, const TaggedObject& b)
	{
		return a.GetID() == b.GetID();
	}
	FORCEINLINE bool operator !=(const TaggedObject& a, const TaggedObject& b)
	{
		return a.GetID() != b.GetID();
	}
}