#pragma once
#include <Editor/Asset/IAssetAuthoringTool.h>
#include <Editor/Asset/CustomAssetAuthoringToolAttribute.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomAssetAuthoringToolAttribute, "texture");
	PCLASS();
	class PORTAKAL_API TextureAuthoringTool : public IAssetAuthoringTool
	{
		GENERATE_CLASS(TextureAuthoringTool);
	public:
		TextureAuthoringTool() = default;
		~TextureAuthoringTool() = default;

	private:

		// Inherited via IAssetAuthorizationTool
		virtual void OnInitialize() override;
		virtual void OnPaint(DomainFile* pFile) override;
		virtual void OnFinalize() override;
	};


#include "TextureAuthoringTool.reflect.h"

}