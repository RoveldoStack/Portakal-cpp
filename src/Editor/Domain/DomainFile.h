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
	class IAssetImporter;
	class IAssetProcessor;
	class IAssetAuthorizationTool;

	/// <summary>
	/// Represents a registered file to the domain system
	/// </summary>
	class PORTAKAL_API DomainFile
	{
		friend class DomainFolder;
	public:
		/// <summary>
		/// Returns the owner folder of this file
		/// </summary>
		/// <returns></returns>
		FORCEINLINE DomainFolder* GetOwnerFolder() const noexcept { return mOwnerFolder; }

		/// <summary>
		/// Returns the assinged authorization tool
		/// </summary>
		/// <returns></returns>
		FORCEINLINE IAssetAuthorizationTool* GetAuthorizationTool() const noexcept { return mAuthorizationTool; }

		/// <summary>
		/// Returns the assigned serializer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE IAssetSerializer* GetSerializer() const noexcept { return mSerializer; }

		/// <summary>
		/// Returns the assigned viusalizer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE IAssetVisualizer* GetVisualizer() const noexcept { return mVisualizer; }

		/// <summary>
		/// Returns the assigned importers
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<IAssetImporter*> GetImporters() const noexcept { return mImporters; }

		/// <summary>
		/// Returns the assigned processors
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<IAssetProcessor*> GetProcessors() const noexcept { return mProcessors; }

		/// <summary>
		/// Returns the loaded sub resource object
		/// </summary>
		/// <returns></returns>
		FORCEINLINE ResourceSubObject* GetLoadedSubObject() const noexcept { return mSubObject; }

		/// <summary>
		/// Returns the file descriptor path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetFileDescriptorPath() const noexcept { return mFileDescriptorPath; }

		/// <summary>
		/// Returns the file source path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetSourceFilePath() const noexcept { return mSourceFilePath; }

		/// <summary>
		/// Returns the file name
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetName() const noexcept { return mName; }

		/// <summary>
		/// Returns the file resource tpye
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }

		/// <summary>
		/// Returns the file id
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Guid GetID() const noexcept { return mID; }

		/// <summary>
		/// Returns whether it's loaded or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsLoaded() const noexcept { return mSubObject != nullptr; }

		/// <summary>
		/// Loads sync
		/// </summary>
		void LoadSync();

		/// <summary>
		/// Unloads sync
		/// </summary>
		void UnloadSync();

		/// <summary>
		/// Deletes this file
		/// </summary>
		void Delete();
	private:
		DomainFile(const String& fileDescriptorPath,DomainFolder* pOwnerFolder);
		~DomainFile();

	private:
		DomainFolder* mOwnerFolder;
		IAssetAuthorizationTool* mAuthorizationTool;
		IAssetSerializer* mSerializer;
		IAssetVisualizer* mVisualizer;
		Array<IAssetImporter*> mImporters;
		Array<IAssetProcessor*> mProcessors;
		ResourceSubObject* mSubObject;
		String mFileDescriptorPath;
		String mSourceFilePath;
		String mName;
		String mResourceType;
		Guid mID;
	};
}