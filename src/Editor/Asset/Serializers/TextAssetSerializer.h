#pragma once
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>

namespace Portakal
{
	class PORTAKAL_API TextAssetSerializer : public IAssetSerializer
	{
		GENERATE_CLASS(TextAssetSerializer);
	public:
		TextAssetSerializer() = default;
		~TextAssetSerializer() = default;

		// Inherited via IAssetSerializer
		virtual void SerializeToEditor(const ResourceSubObject* pObject) override;
		virtual void SerializeToPackage(const ResourceSubObject* pObject) override;
	};

	START_GENERATE_TYPE(TextAssetSerializer);
	START_TYPE_PROPERTIES(TextAssetSerializer);
	REGISTER_BASE_TYPE(IAssetSerializer);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetSerializerAttribute, "simple-text");
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(TextAssetSerializer);

	END_GENERATE_TYPE(TextAssetSerializer);
}