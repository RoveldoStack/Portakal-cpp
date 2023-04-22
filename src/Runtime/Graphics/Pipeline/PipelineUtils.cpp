#include "PipelineUtils.h"
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	unsigned int PipelineUtils::GetInputElementDataSize(const InputElementDataFormat format)
	{
		switch (format)
		{
			case Portakal::InputElementDataFormat::Float1:
				return 4;
			case Portakal::InputElementDataFormat::Float2:
				return 8;
			case Portakal::InputElementDataFormat::Float3:
				return 12;
			case Portakal::InputElementDataFormat::Float4:
				return 16;
			case Portakal::InputElementDataFormat::Byte2_Norm:
				return 2;
			case Portakal::InputElementDataFormat::Byte2:
				return 2;
			case Portakal::InputElementDataFormat::Byte4_Norm:
				return 4;
			case Portakal::InputElementDataFormat::Byte4:
				return 4;
			case Portakal::InputElementDataFormat::SByte2_Norm:
				return 2;
			case Portakal::InputElementDataFormat::SByte2:
				return 2;
			case Portakal::InputElementDataFormat::SByte4_Norm:
				return 4;
			case Portakal::InputElementDataFormat::SByte4:
				return 4;
			case Portakal::InputElementDataFormat::UShort2_Norm:
				return 4;
			case Portakal::InputElementDataFormat::UShort2:
				return 4;
			case Portakal::InputElementDataFormat::UShort4_Norm:
				return 8;
			case Portakal::InputElementDataFormat::UShort4:
				return 8;
			case Portakal::InputElementDataFormat::Short2_Norm:
				return 4;
			case Portakal::InputElementDataFormat::Short2:
				return 4;
			case Portakal::InputElementDataFormat::Short4_Norm:
				return 8;
			case Portakal::InputElementDataFormat::Short4:
				return 8;
			case Portakal::InputElementDataFormat::UInt1:
				return 4;
			case Portakal::InputElementDataFormat::UInt2:
				return 8;
			case Portakal::InputElementDataFormat::UInt3:
				return 12;
			case Portakal::InputElementDataFormat::UInt4:
				return 16;
			case Portakal::InputElementDataFormat::Int1:
				return 4;
			case Portakal::InputElementDataFormat::Int2:
				return 8;
			case Portakal::InputElementDataFormat::Int3:
				return 12;
			case Portakal::InputElementDataFormat::Int4:
				return 16;
			case Portakal::InputElementDataFormat::Half1:
				return 4;
			case Portakal::InputElementDataFormat::Half2:
				return 8;
			case Portakal::InputElementDataFormat::Half4:
				return 16;
			default:
				ASSERT(false, "PipelineUtils", "Invalid InputElementDataType");
				break;
		}
	}
}