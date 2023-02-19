#pragma once
#include <Runtime/Containers/String.h>
#include <Editor/Resource/EditorResourceType.h>

namespace Portakal
{
	/// <summary>
	/// Represents a initialization time editor resource request for loading them on editor initialization
	/// </summary>
	struct PORTAKAL_API EditorResourceRequest
	{
		/// <summary>
		/// name of the resource
		/// </summary>
		String Name;

		/// <summary>
		/// The of the resource
		/// </summary>
		EditorResourceType Type;
	};
}