#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	class ResourceSubObject;
	class IResourceSerializer;

	/// <summary>
	/// Represents a single resource registered to the application
	/// </summary>
	class PORTAKAL_API Resource
	{
		friend class ResourceAPI;
	public:
		FORCEINLINE ResourceSubObject* GetSubObject() const noexcept { return mSubObject; }
		FORCEINLINE Guid GetID() const noexcept { return mID; }
		FORCEINLINE String GetName() const noexcept { return mName; }
		FORCEINLINE String GetAbsolutePath() const noexcept { return mAbsolutePath; }
		FORCEINLINE String GetResourceType() const noexcept { return mType; }
		FORCEINLINE unsigned long long GetFileByteOffset() const noexcept { return mByteOffset; }
		FORCEINLINE unsigned long long GetSize() const noexcept { return mSize; }
		FORCEINLINE bool IsLoaded() const noexcept { return mLoaded; }

		/// <summary>
		/// Loads sync
		/// </summary>
		void LoadSync();

		/// <summary>
		/// Unloads sync
		/// </summary>
		void UnloadSync();
	private:
		Resource(const String& path,const String& resourceType,const bool bCompressed = false); // Constructor for files
		~Resource();
	private:
		IResourceSerializer* mSerializer;
		ResourceSubObject* mSubObject;
		Guid mID;
		String mName;
		String mAbsolutePath;
		String mType;
		unsigned long long mByteOffset;
		unsigned long long mSize;
		bool mLoaded;
		const bool mCompressed;

	};
}