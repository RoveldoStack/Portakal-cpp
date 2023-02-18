#pragma once
#include <Editor/Asset/IAssetAuthorizationTool.h>
#include <Editor/Asset/CustomAssetAuthorizationToolAttribute.h>

namespace Portakal
{
	class PORTAKAL_API TextureAuthorizationTool : public IAssetAuthorizationTool
	{
		GENERATE_CLASS(TextureAuthorizationTool);
	public:
		TextureAuthorizationTool() = default;
		~TextureAuthorizationTool() = default;

	private:

		// Inherited via IAssetAuthorizationTool
		virtual void OnInitialize() override;
		virtual void OnPaint(DomainFile* pFile) override;
		virtual void OnFinalize() override;
	};

	START_GENERATE_TYPE(TextureAuthorizationTool);
	START_TYPE_PROPERTIES(TextureAuthorizationTool);
	REGISTER_BASE_TYPE(IAssetAuthorizationTool);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetAuthorizationToolAttribute,"texture");
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(TextureAuthorizationTool);
	END_GENERATE_TYPE(TextureAuthorizationTool);
}