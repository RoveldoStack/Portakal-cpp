#pragma once
#include <Runtime/Containers/String.h>
#include <Editor/GUI/Window/EditorWindowDockState.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Reflection/Type.h>
#include <Editor/GUI/Window/EditorWindowSetting.h>

namespace Portakal
{
	/// <summary>
	/// Editor window settings file
	/// </summary>
	PSTRUCT();
	struct PORTAKAL_API EditorWindowSettings
	{
		/// <summary>
		/// Generates the default window layout
		/// </summary>
		/// <returns></returns>
		static EditorWindowSettings Default()
		{
			EditorWindowSettings settings = {};
			{
				EditorWindowSetting setting = {};
				setting.Name = "DomainObserverWindow";
				setting.ID = Guid::Create();
				setting.DockState = EditorWindowDockState::Down;
				setting.OwnerID = Guid::Zero();
				settings.Windows.Add(setting);
			}
			{
				EditorWindowSetting setting = {};
				setting.Name = "WorldObserverWindow";
				setting.ID = Guid::Create();
				setting.DockState = EditorWindowDockState::Left;
				setting.OwnerID = Guid::Zero();
				settings.Windows.Add(setting);
			}
			{
				EditorWindowSetting setting = {};
				setting.Name = "ObjectObserverWindow";
				setting.ID = Guid::Create();
				setting.DockState = EditorWindowDockState::Right;
				setting.OwnerID = Guid::Zero();
				settings.Windows.Add(setting);
			}
			{
				EditorWindowSetting setting = {};
				setting.Name = "GameObserverWindow";
				setting.ID = Guid::Create();
				setting.DockState = EditorWindowDockState::Center;
				setting.OwnerID = Guid::Zero();
				settings.Windows.Add(setting);
			}

			return settings;
		}

		PFIELD();
		Array<EditorWindowSetting> Windows;
	};

#include "EditorWindowSettings.reflect.h"
}