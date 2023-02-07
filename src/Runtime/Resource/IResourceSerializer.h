#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Memory/ByteBlock.h>
namespace Portakal
{
	class ResourceSubObject;
	class PORTAKAL_API IResourceSerializer
	{
	public:
		IResourceSerializer() = default;
		~IResourceSerializer() = default;

		virtual ResourceSubObject* DeserializeFromPackage(const ByteBlock& block) = 0;
	};
}