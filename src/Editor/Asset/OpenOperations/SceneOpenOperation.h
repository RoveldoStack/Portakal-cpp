#pragma once
#include <Editor/Asset/IAssetOpenOperation.h>
#include <Editor/Asset/CustomAssetOpenOperationAttribute.h>
#include <Runtime/World/Scene.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomAssetOpenOperationAttribute, "scene");
	PCLASS();
	class PORTAKAL_API SceneOpenOperation : public IAssetOpenOperation
	{
		GENERATE_CLASS(SceneOpenOperation);
	public:
		virtual void OnOpen(DomainFile* pFile) override;
	};


#include "SceneOpenOperation.reflect.h"
}