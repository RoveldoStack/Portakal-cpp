#pragma once
#include <Runtime/Resource/Mesh/MeshIndexType.h>

namespace Portakal
{
	class PORTAKAL_API MeshUtils
	{
	public:
		static unsigned int GetMeshIndexTypeSize(const MeshIndexType type);
	public:
		MeshUtils() = delete;
		~MeshUtils() = delete;
	};
}