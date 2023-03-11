#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Resource/Resource.h>

namespace Portakal
{
	/// <summary>
	/// API for accessing resource related operations across the application
	/// </summary>
	class PORTAKAL_API ResourceAPI
	{
		friend class ResourceModule;
	private:
		static ResourceAPI* sAPI;
	public:
		static Resource* GetResourceViaID(const Guid& id);
		static Resource* RegisterResource(const String& path,const String& type);
	private:
		ResourceAPI(const String& packagesPath);
		ResourceAPI();
		~ResourceAPI();

		Resource* _GetResourceViaID(const Guid& id);
		Resource* _RegisterResource(const String& path,const String& type);
	private:
		Array<Resource*> mResources;
	};
}