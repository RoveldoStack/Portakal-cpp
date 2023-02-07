#pragma once
#include <Runtime/Containers/String.h>
#include <Editor/Resource/EditorResourceType.h>

namespace Portakal
{
	struct PORTAKAL_API EditorResourceRequest
	{
		String Name;
		EditorResourceType Type;
	};
}