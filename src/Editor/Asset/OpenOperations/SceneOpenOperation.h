#pragma once
#include <Editor/Asset/IAssetOpenOperation.h>
#include <Editor/Asset/CustomAssetOpenOperationAttribute.h>
#include <Runtime/World/Scene.h>

namespace Portakal
{
	class PORTAKAL_API SceneOpenOperation : public IAssetOpenOperation
	{
		GENERATE_CLASS(SceneOpenOperation);
	public:
		virtual void OnOpen(DomainFile* pFile) override;
	};

	START_GENERATE_TYPE(SceneOpenOperation);
	START_TYPE_PROPERTIES(SceneOpenOperation);
	REGISTER_BASE_TYPE(IAssetOpenOperation);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetOpenOperationAttribute,"scene");
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(SceneOpenOperation);
	END_GENERATE_TYPE(SceneOpenOperation);
}