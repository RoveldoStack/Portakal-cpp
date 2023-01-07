#include "D3DCompilerUtils.h"

namespace Portakal
{
	String D3DCompilerUtils::GetCompilerTarget(const ShaderStage stage, const unsigned int major, const unsigned int minor)
	{
		String text;
		switch (stage)
		{
			case Portakal::ShaderStage::None:
				break;
			case Portakal::ShaderStage::Vertex:
				text = "vs_";
				break;
			case Portakal::ShaderStage::Fragment:
				text = "ps_";
				break;
			case Portakal::ShaderStage::TesellationEval:
				break;
			case Portakal::ShaderStage::TesellationControl:
				break;
			case Portakal::ShaderStage::Compute:
				break;
			default:
				break;
		}

		text += String::GetFromInteger(major);
		text += "_";
		text += String::GetFromInteger(minor);

		return text;
	}
}