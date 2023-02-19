#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class DomainFolder;

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
	private:
		DomainAPI(const String& domainFolderPath);
		~DomainAPI();
	private:
		DomainFolder* mRootFolder;
		const String mFolderPath;
	};
}