#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Memory/ByteBlock.h>
#include "ResourceDescriptor.h"
#include <Runtime/Platform/PlatformCriticalSection.h>
#include <Runtime/Job/Job.h>

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
		FORCEINLINE ResourceSubObject* GetSubObject() const noexcept;
		FORCEINLINE Guid GetID() const noexcept { return mID; }
		FORCEINLINE String GetName() const noexcept { return mName; }
		FORCEINLINE String GetAbsolutePath() const noexcept { return mAbsolutePath; }
		FORCEINLINE String GetResourceType() const noexcept { return mType; }
		FORCEINLINE unsigned long long GetFileByteOffset() const noexcept { return mByteOffset; }
		FORCEINLINE unsigned long long GetSize() const noexcept { return mSize; }
		FORCEINLINE bool IsLoaded() const noexcept;
		FORCEINLINE bool IsCached() const noexcept;

		/// <summary>
		/// Loads the resource on other thread
		/// </summary>
		void LoadAsync();

		/// <summary>
		/// Unloads the resource on other thread
		/// </summary>
		void UnloadAsync();

		/// <summary>
		/// Loads sync
		/// </summary>
		void LoadSync();

		/// <summary>
		/// Unloads sync
		/// </summary>
		void UnloadSync();

		/// <summary>
		/// Caches the target data
		/// </summary>
		void CacheSync();

		/// <summary>
		/// Clears the cached data
		/// </summary>
		void ClearCacheSync();
	private:
		Resource(const String& path,const ResourceDescriptor& descriptor,const bool bCompressed = false); // Constructor for files
		~Resource();

		void OnResourceLoadedAsync(ResourceSubObject* pObject);
	private:
		IResourceSerializer* mSerializer;
		ResourceSubObject* mSubObject;
		PlatformCriticalSection* mCriticalSection;
		Job* mJob;
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