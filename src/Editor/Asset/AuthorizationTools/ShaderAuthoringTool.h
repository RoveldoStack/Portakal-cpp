#pragma once
#include <Editor/Asset/IAssetAuthoringTool.h>
#include <Editor/Asset/CustomAssetAuthoringToolAttribute.h>

namespace Portakal
{
	class PORTAKAL_API ShaderAuthoringTool : public IAssetAuthoringTool
	{
		GENERATE_CLASS(ShaderAuthoringTool);
	public:
		ShaderAuthoringTool() = default;
		~ShaderAuthoringTool() = default;

	private:

		// Inherited via IAssetAuthorizationTool
		virtual void OnInitialize() override;
		virtual void OnPaint(DomainFile* pFile) override;
		virtual void OnFinalize() override;
	};

	START_GENERATE_TYPE(ShaderAuthoringTool);
	START_TYPE_PROPERTIES(ShaderAuthoringTool);
	REGISTER_BASE_TYPE(IAssetAuthoringTool);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetAuthoringToolAttribute, "shader")
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(ShaderAuthoringTool);
	END_GENERATE_TYPE(ShaderAuthoringTool);

	//START_GENERATE_TYPE(ShaderAuthoringTool);
	//START_TYPE_PROPERTIES(ShaderAuthoringTool);
	//REGISTER_BASE_TYPE(ShaderAuthoringTool);
	//REGISTER_TYPE_ATTRIBUTE(CustomAssetAuthoringToolAttribute, "shader");
	//END_TYPE_PROPERTIES;
	//HAS_DEFAULT_CONSTRUCTOR(ShaderAuthoringTool);
	//END_GENERATE_TYPE(ShaderAuthoringTool);

}