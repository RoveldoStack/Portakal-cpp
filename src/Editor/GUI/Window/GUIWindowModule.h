#pragma once
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class EditorWindowAPI;

	/// <summary>
	/// An application module which authors the editor window components
	/// </summary>
	PCLASS();
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

		/// <summary>
		/// Creates default settings
		/// </summary>
		void CreateDefaultSettings();

		/// <summary>
		/// Saves the current settings to the settings file
		/// </summary>
		void SaveSettingsToFile();

		/// <summary>
		/// Loads the windows from the settings file
		/// </summary>
		void LoadWindowsFromFile();
	private:
		EditorWindowAPI* mAPI;
		bool mLayoutInitialized;
		bool mDockState;
	};

#include "GUIWindowModule.reflect.h"
}