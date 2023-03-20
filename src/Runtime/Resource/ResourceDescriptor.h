#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Guid.h>
namespace Portakal
{
	struct PORTAKAL_API ResourceDescriptor
	{

		/// <summary>
		/// Resource type
		/// </summary>
		String ResourceType;

		/// <summary>
		/// Unique id
		/// </summary>
		Guid ID;
	};
}