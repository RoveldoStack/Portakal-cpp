#pragma once
#include <Runtime/Graphics/FaceCullMode.h>
#include <Runtime/Graphics/MeshShadeMode.h>
#include <Runtime/Graphics/FrontFaceDirection.h>

namespace Portakal
{
	struct PORTAKAL_API RasterizerStateDesc
	{
		FaceCullMode CullMode;
		MeshShadeMode ShadeMode;
		FrontFaceDirection FrontFace;
		bool bDepthClipEnabled;
		bool bScissorTestEnabled;
	};
}