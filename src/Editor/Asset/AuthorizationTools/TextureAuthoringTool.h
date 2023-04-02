#pragma once
#include <Editor/Asset/IAssetAuthoringTool.h>
#include <Editor/Asset/CustomAssetAuthoringToolAttribute.h>

namespace Portakal
{
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

	START_GENERATE_TYPE(TextureAuthoringTool);
	START_TYPE_PROPERTIES(TextureAuthoringTool);
	REGISTER_BASE_TYPE(IAssetAuthoringTool);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetAuthoringToolAttribute,"texture");
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(TextureAuthoringTool);
	END_GENERATE_TYPE(TextureAuthoringTool);
}