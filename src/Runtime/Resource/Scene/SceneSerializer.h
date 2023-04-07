#pragma once
#include <Runtime/World/Scene.h>
#include <Runtime/Resource/IResourceSerializer.h>
#include <Runtime/Resource/CustomResourceSerializerAttribute.h>

namespace Portakal
{
	CLASS_ATTRIBUTE(CustomResourceSerializerAttribute, "scene");
	class PORTAKAL_API SceneSerializer : public IResourceSerializer
	{
		GENERATE_CLASS(SceneSerializer);
	public:
		SceneSerializer() = default;
		~SceneSerializer() = default;

		// Inherited via IResourceSerializer
		virtual ResourceSubObject* Deserialize(const ByteBlock& block) override;
		virtual ResourceSubObject* DeserializeCompressed(const ByteBlock& block) override;

	};

	//START_GENERATE_TYPE(SceneSerializer);
	//START_TYPE_PROPERTIES(SceneSerializer);
	//REGISTER_BASE_TYPE(IResourceSerializer);
	//REGISTER_TYPE_ATTRIBUTE(CustomResourceSerializerAttribute, "scene");
	//END_TYPE_PROPERTIES;
	//HAS_DEFAULT_CONSTRUCTOR(SceneSerializer);
	//END_GENERATE_TYPE(SceneSerializer);

#include "SceneSerializer.reflect.h"
}