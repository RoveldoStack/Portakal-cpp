#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	class DomainFolder;
	class DomainFile;
	/// <summary>
	/// API for enabling the use of domain operations across the application
	/// </summary>
	class PORTAKAL_API DomainAPI
	{
		friend class DomainModule;
	private:
		static DomainAPI* sAPI;
	public:

		/// <summary>
		/// Returns the root folder of the domain
		/// </summary>
		/// <returns></returns>
		FORCEINLINE static DomainFolder* GetRootFolder();
		FORCEINLINE static DomainFile* GetFileViaID(const Guid& id);
	private:
		DomainAPI(const String& domainFolderPath);
		~DomainAPI();
	private:
		DomainFolder* mRootFolder;
		const String mFolderPath;
	};
}