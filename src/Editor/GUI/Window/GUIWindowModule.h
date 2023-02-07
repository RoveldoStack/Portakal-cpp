#pragma once
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class EditorWindowAPI;

	class PORTAKAL_API GUIWindowModule : public ApplicationModule
	{
		GENERATE_CLASS(GUIWindowModule);
		GENERATE_APPLICATION_MODULE(true, false, true);
	public:
		GUIWindowModule() : mLayoutInitialized(false),mDockState(true) {}
		~GUIWindowModule() = default;

		// Inherited via ApplicationModule
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPreTick() override;
		virtual void OnTick() override;
		virtual void OnPostTick() override;
		virtual void PreValidate() override;
		virtual void PostValidate() override;
		virtual void OnEvent(WindowEvent* pEvent) override;

	private:
		void CreateDefaultSettings();
		void SaveSettingsToFile();
		void LoadWindowsFromFile();
	private:
		EditorWindowAPI* mAPI;
		bool mLayoutInitialized;
		bool mDockState;
	};

	START_GENERATE_TYPE(GUIWindowModule);
	START_TYPE_PROPERTIES(GUIWindowModule);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(GUIWindowModule);
	END_GENERATE_TYPE(GUIWindowModule);
}