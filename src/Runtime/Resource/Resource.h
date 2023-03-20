#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Memory/ByteBlock.h>
#include "ResourceDescriptor.h"

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
		FORCEINLINE bool IsCached() const noexcept { return mCached; }

		/// <summary>
		/// Loads sync
		/// </summary>
		void LoadSync();

		/// <summary>
		/// Unloads sync
		/// </summary>
		void UnloadSync();

		void CacheSync();
		void ClearCacheSync();
	private:
		Resource(const String& path,const ResourceDescriptor& descriptor,const bool bCompressed = false); // Constructor for files
		~Resource();
	private:
		IResourceSerializer* mSerializer;
		ResourceSubObject* mSubObject;
		ByteBlock mCachedData;
		Guid mID;
		String mName;
		String mAbsolutePath;
		String mType;
		unsigned long long mByteOffset;
		unsigned long long mSize;
		bool mLoaded;
		bool mCached;
		const bool mCompressed;

	};
}