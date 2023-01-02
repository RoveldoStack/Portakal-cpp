#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	class PORTAKAL_API TaggedObject : public Class
	{
		GENERATE_CLASS(TaggedObject);
	public:
		FORCEINLINE String GetTagName() const noexcept { return _name; }
		FORCEINLINE void SetTagName(const String& name) { _name = name; }
		FORCEINLINE Guid GetID() const noexcept { return _id; }

		void OverrideID(const Guid& id) { _id = id; }
	protected:
		TaggedObject(const String& name,const Guid& id) : _name(name),_id(id) {}
		TaggedObject(const String& name) : _name(name),_id(Guid::Create()) {}
		TaggedObject(const Guid& id) : _id(id) {}
		TaggedObject() = default;

		~TaggedObject() = default;

	private:
		String _name;
		Guid _id;
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