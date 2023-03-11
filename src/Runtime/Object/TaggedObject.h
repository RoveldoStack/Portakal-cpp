#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	/// <summary>
	/// Represents an identifiable unique object
	/// </summary>
	class PORTAKAL_API TaggedObject : public Class
	{
		GENERATE_CLASS(TaggedObject);
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
		FORCEINLINE void SetTagName(const String& name) { mName = name; }

		/// <summary>
		/// Overrides the unique id of this object, use it with caution
		/// </summary>
		/// <param name="id"></param>
		void OverrideID(const Guid& id) { mID = id; }

		/// <summary>
		/// Destroys the object
		/// </summary>
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

		~TaggedObject()
		{
			if (mDestroyed)
				return;

			Destroy();
		}

		virtual void DestroyCore() = 0;
	private:
		String mName;
		Guid mID;
		bool mDestroyed;

	};
	START_GENERATE_TYPE(TaggedObject);
	START_TYPE_PROPERTIES(TaggedObject);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
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