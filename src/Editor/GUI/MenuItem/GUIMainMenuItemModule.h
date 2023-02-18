#pragma once
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class MenuItemTree;

	class PORTAKAL_API GUIMainMenuItemModule : public ApplicationModule
	{
		GENERATE_CLASS(GUIMainMenuItemModule);
		GENERATE_APPLICATION_MODULE(true, false, true);
	public:
		GUIMainMenuItemModule() = default;
		virtual ~GUIMainMenuItemModule() override = default;

		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPreTick() override;
		virtual void OnTick() override;
		virtual void OnPostTick() override;
		virtual void PreValidate() override;
		virtual void PostValidate() override;
		virtual void OnEvent(WindowEvent* pEvent) override;
	private:
		void LoadMainMenuItems();
	private:
		MenuItemTree* mTree;
	};

	START_GENERATE_TYPE(GUIMainMenuItemModule);
	START_TYPE_PROPERTIES(GUIMainMenuItemModule);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(GUIMainMenuItemModule);
	END_GENERATE_TYPE(GUIMainMenuItemModule);
}