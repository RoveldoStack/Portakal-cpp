#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class DomainFile;
	class TextureResource;
	class PORTAKAL_API IAssetVisualizer : public Class
	{
		GENERATE_CLASS(IAssetVisualizer);
	public:
		IAssetVisualizer() = default;
		~IAssetVisualizer() = default;
		
		virtual TextureResource* OnPaint(const DomainFile* pFile) = 0;
	};

	START_GENERATE_TYPE(IAssetVisualizer);
	START_TYPE_PROPERTIES(IAssetVisualizer);
	END_TYPE_PROPERTIES;
	VIRTUAL_TYPE;
	END_GENERATE_TYPE(IAssetVisualizer);
}