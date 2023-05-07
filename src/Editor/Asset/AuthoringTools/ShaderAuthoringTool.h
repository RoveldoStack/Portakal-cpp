#pragma once
#include <Editor/Asset/IAssetAuthoringTool.h>
#include <Editor/Asset/CustomAssetAuthoringToolAttribute.h>
#include <Runtime/Graphics/Shader/ShaderStage.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomAssetAuthoringToolAttribute, "shader");
	PCLASS();
	class PORTAKAL_API ShaderAuthoringTool : public IAssetAuthoringTool
	{
		GENERATE_CLASS(ShaderAuthoringTool);
	public:
		ShaderAuthoringTool() : mInitialized(false),mStage(ShaderStage::None) {}
		~ShaderAuthoringTool() = default;

	private:

		// Inherited via IAssetAuthorizationTool
		virtual void OnInitialize() override;
		virtual void OnPaint(DomainFile* pFile) override;
		virtual void OnFinalize() override;
	private:
		String mSourceBuffer;
		String mEntryPointBuffer;
		ShaderStage mStage;
		bool mInitialized;
	};


#include "ShaderAuthoringTool.reflect.h"

}