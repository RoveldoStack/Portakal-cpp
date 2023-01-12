#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	class PORTAKAL_API Resource
	{
	public:
		Resource(const ResourceLoadDesc& desc, const Guid& id)
		{

		}

		FORCEINLINE bool IsLoaded() const noexcept;
		FORCEINLINE ResourceSubObject* GetSubObject() const noexcept;

		void LoadSync()
		{

		}
		void UnloadSync()
		{

		}
		void DestroyResourceSnyc()
		{

		}
	private:
		void LoadInternalSync()
		{

		}
	private:
		String _type;
		String _name;
		Guid _id;
		ResourceLoadDesc _loadDesc;
		ResourceSubObject* _subObject;
	};
}