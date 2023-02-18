#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Reflection/Reflection.h>
namespace Portakal
{
	enum class PORTAKAL_API SceneComponentFieldType
	{
		Raw,
		Entity,
		Component,
		Resource
	};

	struct PORTAKAL_API SceneResourceEntry
	{
		Guid ID;
	};

	struct PORTAKAL_API SceneAspectEntry
	{
		String TypeName;
	};

	struct PORTAKAL_API SceneEntityEntry
	{
		String TagName;
		Guid ID;
	};

	struct PORTAKAL_API SceneComponentFieldEntry
	{
		String FieldName;
		SceneComponentFieldType Type;
		String Content;
	};

	struct PORTAKAL_API SceneComponentEntry
	{
		String TypeName;
		String TagName;
		Guid ID;
		Guid OwnerEntityID;
		Array<SceneComponentFieldEntry> Fields;
	};

	

	struct PORTAKAL_API SceneDescriptor : public Class
	{
		GENERATE_CLASS(SceneDescriptor);

		SceneDescriptor() = default;
		~SceneDescriptor() = default;

		Array<SceneAspectEntry> Aspects;
		Array<SceneEntityEntry> Entities;
		Array<SceneComponentEntry> Components;
	};

	START_GENERATE_TYPE(SceneDescriptor);
	START_TYPE_PROPERTIES(SceneDescriptor);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(SceneDescriptor);
	END_GENERATE_TYPE(SceneDescriptor);
}