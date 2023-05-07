#pragma once
#include <Runtime/World/Scene.h>
#include <Runtime/Resource/IResourceSerializer.h>
#include <Runtime/Resource/CustomResourceSerializerAttribute.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomResourceSerializerAttribute, "scene");
	PCLASS();
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

#include "SceneSerializer.reflect.h"
}