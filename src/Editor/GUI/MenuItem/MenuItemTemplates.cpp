#include "MenuItemTemplates.h"
#include <Runtime/World/SceneAPI.h>
#include <Runtime/World/Scene.h>

namespace Portakal
{
	void CreateEmptySceneButton::OnClick()
	{
		Scene* pScene = SceneAPI::CreateScene(true);
		pScene->SetTagName("Runtime test scene");
	}
}