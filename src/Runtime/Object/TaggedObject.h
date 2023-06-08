#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	/// <summary>
	/// Represents an identifiable unique object
	/// </summary>
	PCLASS();
	class PORTAKAL_API TaggedObject : public Class
	{
		friend class GarbageCollector;
		GENERATE_CLASS(TaggedObject,Virtual);
	public:
		/// <summary>
		/// Returns the object name
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetTagName() const noexcept { return mName; }

		/// <summary>
		/// Returns the unique object id
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Guid GetID() const noexcept { return mID; }

		/// <summary>
		/// Returns whether this object is destroyed or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsDestroyed() const noexcept { return mDestroyed; }

		/// <summary>
		/// Sets the object name
		/// </summary>
		/// <param name="name"></param>
		FORCEINLINE void SetTagName(const String& name) { SetTagNameCore(name);  mName = name; }

		/// <summary>
		/// Overrides the unique id of this object, use it with caution
		/// </summary>
		/// <param name="id"></param>
		void OverrideID(const Guid& id) { mID = id; }

		/// <summary>
		/// Destroys the object
		/// </summary>
		void Destroy();

		FORCEINLINE bool operator ==(const TaggedObject& other)
		{
			return mID == other.mID;
		}
		FORCEINLINE bool operator !=(const TaggedObject& other)
		{
			return mID != other.mID;
		}
	protected:
		TaggedObject(const String& name,const Guid& id) : mName(name), mID(id),mDestroyed(false) {}
		TaggedObject(const String& name) : mName(name), mID(Guid::Create()),mDestroyed(false) {}
		TaggedObject(const Guid& id) : mID(id),mDestroyed(false) {}
		TaggedObject() : mDestroyed(false),mID(Guid::Create()),mName("Default") {}

		~TaggedObject()
		{

		}

		virtual void DestroyCore() = 0;
		virtual void SetTagNameCore(const String& name) {}
	private:
		String mName;
		Guid mID;
		bool mDestroyed;

	};

#include "TaggedObject.reflect.h"
}