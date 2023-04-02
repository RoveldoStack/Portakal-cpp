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
	public:
		static Resource* RegisterResource(const String& path,const ResourceDescriptor& descriptor);
		static Resource* GetResourceViaID(const Guid& id);
		static void ClearResources();
	private:
		static Array<Resource*> sResources;
	private:
		ResourceAPI() = delete;
		~ResourceAPI() = delete;
	};
}