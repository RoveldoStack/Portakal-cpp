#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Resource/Resource.h>
#include <Runtime/Object/API.h>

namespace Portakal
{
	/// <summary>
	/// API for accessing resource related operations across the application
	/// </summary>
	class PORTAKAL_API ResourceAPI : public API<ResourceAPI>
	{
	public:
		static Resource* RegisterResource(const String& path,const ResourceDescriptor& descriptor);
		static Resource* GetResourceViaID(const Guid& id);
		static void ClearResources();
	public:
		ResourceAPI();
		virtual ~ResourceAPI() override;
	private:
		Array<Resource*> mResources;
	private:

	};
}