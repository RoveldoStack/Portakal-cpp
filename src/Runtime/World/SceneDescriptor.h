#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Containers/Array.h>

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

	

	struct PORTAKAL_API SceneDescriptor
	{

	};
}