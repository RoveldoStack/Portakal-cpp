#include "MeshUtils.h"

namespace Portakal
{
	unsigned int MeshUtils::GetMeshIndexTypeSize(const MeshIndexType type)
	{
		switch (type)
		{
			case Portakal::MeshIndexType::Unknown:
				return 0;
			case Portakal::MeshIndexType::Bit16:
				return 2;
			case Portakal::MeshIndexType::Bit32:
				return 4;
			default:
				return 0;
		}
	}
}