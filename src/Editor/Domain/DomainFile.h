#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	class IAssetSerializer;
	class ResourceSubObject;
	class DomainFolder;
	class IAssetVisualizer;
	class PORTAKAL_API DomainFile
	{
		friend class DomainFolder;
	public:


		FORCEINLINE DomainFolder* GetOwnerFolder() const noexcept { return mOwnerFolder; }
		FORCEINLINE IAssetSerializer* GetSerializer() const noexcept { return mSerializer; }
		FORCEINLINE IAssetVisualizer* GetVisualizer() const noexcept { return mVisualizer; }
		FORCEINLINE ResourceSubObject* GetLoadedSubObject() const noexcept { return mSubObject; }
		FORCEINLINE String GetFileDescriptorPath() const noexcept { return mFileDescriptorPath; }
		FORCEINLINE String GetSOurceFilePath() const noexcept { return mSourceFilePath; }
		FORCEINLINE String GetName() const noexcept { return mName; }
		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
		FORCEINLINE Guid GetID() const noexcept { return mID; }
	private:
		DomainFile(const String& fileDescriptorPath,DomainFolder* pOwnerFolder);
		~DomainFile();


	private:
		DomainFolder* mOwnerFolder;
		IAssetSerializer* mSerializer;
		IAssetVisualizer* mVisualizer;
		ResourceSubObject* mSubObject;
		String mFileDescriptorPath;
		String mSourceFilePath;
		String mName;
		String mResourceType;
		Guid mID;

	};
}