#include "MenuItemTemplates.h"
#include <Runtime/World/SceneAPI.h>
#include <Runtime/World/Scene.h>
#include <Runtime/Resource/RenderTarget/RenderTarget.h>
#include <Runtime/World/Aspects/DisplayAspect.h>

namespace Portakal
{
	void CreateEmptySceneButton::OnClick()
	{
		Scene* pScene = new Scene();
		pScene->MarkPrimal();
		pScene->SetTagName("Runtime test scene");
	}
	void CreateDisplayButton::OnClick()
	{
		RenderTarget* pRt = new RenderTarget(1024, 1024, { TextureFormat::R8_G8_B8_A8_UNorm }, TextureFormat::None, { "Test color layer" });

		Scene* pPrimalScene = SceneAPI::GetPrimalScene();
		if (pPrimalScene == nullptr)
			return;
		DisplayAspect* pAspect = pPrimalScene->GetAspect<DisplayAspect>();
		if (pAspect == nullptr)
			return;

		pAspect->RegisterDisplay(pRt);
	}
}