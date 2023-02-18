#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Memory/ByteBlock.h>

namespace Portakal
{
	class DomainFile;
	class ResourceSubObject;
	class PORTAKAL_API IAssetSerializer : public Class
	{
		GENERATE_CLASS(IAssetSerializer);
	public:
		IAssetSerializer() = default;
		~IAssetSerializer() = default;

		virtual void SerializeToEditor(const ResourceSubObject* pObject) = 0;
		virtual void SerializeToPackage(const ResourceSubObject* pObject) = 0;
		virtual ResourceSubObject* Deserialize(const DomainFile* pFile) = 0;
	};

	START_GENERATE_TYPE(IAssetSerializer);
	START_TYPE_PROPERTIES(IAssetSerializer);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(IAssetSerializer)
}