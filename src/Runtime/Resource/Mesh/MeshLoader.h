#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Resource/Mesh/MeshLoadFlags.h>
#include <Runtime/Resource/Mesh/MeshLoadResult.h>

namespace Portakal
{
	class PORTAKAL_API MeshLoader
	{
	public:
		static void Load(const String& path,const MeshLoadFlags flags,Array<MeshLoadResult>& results);
	public:
		MeshLoader() = delete;
		~MeshLoader() = delete;
	};
}