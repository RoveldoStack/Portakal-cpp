#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Math/Vector2F.h>
#include <Runtime/Math/Vector3.h>

namespace Portakal
{
	struct PORTAKAL_API MeshLoadResult
	{
		Array<Vector3F> Positions;
		Array<Vector3F> Normals;
		Array<Vector3F> Tangents;
		Array<Vector3F> Bitangents;
		Array<Vector2F> TextureCoordinates;
		Array<unsigned int> Triangles;
	};
}