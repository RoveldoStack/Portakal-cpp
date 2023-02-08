#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Memory/ByteBlock.h>

namespace Portakal
{
	class ResourceSubObject;
	class PORTAKAL_API IAssetSerializer : public Class
	{
		GENERATE_CLASS(IAssetSerializer);
	public:
		IAssetSerializer() = default;
		~IAssetSerializer() = default;

		virtual void SerializeToEditor(const ResourceSubObject* pObject) = 0;
		virtual void SerializeToPackage(const ResourceSubObject* pObject) = 0;
		virtual ResourceSubObject* DeserializeFromEditor(const String& text) = 0;
		virtual ResourceSubObject* DeserializeFromRaw(const ByteBlock& block) = 0;
	};

	START_GENERATE_TYPE(IAssetSerializer);
	START_TYPE_PROPERTIES(IAssetSerializer);
	END_TYPE_PROPERTIES;
	VIRTUAL_TYPE;
	END_GENERATE_TYPE(IAssetSerializer)
}