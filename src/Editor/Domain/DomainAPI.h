#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Object/API.h>

namespace Portakal
{
	class DomainFolder;
	class DomainFile;
	/// <summary>
	/// API for enabling the use of domain operations across the application
	/// </summary>
	class PORTAKAL_API DomainAPI : public API<DomainAPI>
	{
		friend class DomainModule;
	public:
		/// <summary>
		/// Returns the root folder of the domain
		/// </summary>
		/// <returns></returns>
		FORCEINLINE static DomainFolder* GetRootFolder();
		FORCEINLINE static DomainFile* GetFileViaID(const Guid& id);
	private:
		DomainAPI(const String& domainFolderPath);
		virtual ~DomainAPI() override;
	private:
		DomainFolder* mRootFolder;
		const String mFolderPath;
	};
}