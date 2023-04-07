#pragma once
#include <Runtime/Containers/String.h>
#include <Editor/GUI/Window/EditorWindowDockState.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Reflection/Type.h>

namespace Portakal
{
	/// <summary>
	/// Editor window settings
	/// </summary>
	struct PORTAKAL_API EditorWindowSetting
	{
		/// <summary>
		/// Title of the window
		/// </summary>
		String Name;

		/// <summary>
		/// Unique id of the window
		/// </summary>
		Guid ID;

		/// <summary>
		/// Dock state of the window
		/// </summary>
		EditorWindowDockState DockState;

		/// <summary>
		/// Owner window id
		/// </summary>
		Guid OwnerID;
	};

	/// <summary>
	/// Editor window settings file
	/// </summary>
	struct PORTAKAL_API EditorWindowSettings : public Class
	{
		GENERATE_CLASS(EditorWindowSettings);

		/// <summary>
		/// Generates the default window layout
		/// </summary>
		/// <returns></returns>
		static EditorWindowSettings Default()
		{
			EditorWindowSettings settings = {};
			settings.Windows.Add({ "DomainObserverWindow",Guid::Create(),EditorWindowDockState::Down,Guid::Create() });
			settings.Windows.Add({ "WorldObserverWindow",Guid::Create(),EditorWindowDockState::Left,Guid::Create() });
			settings.Windows.Add({ "ObjectObserverWindow",Guid::Create(),EditorWindowDockState::Right,Guid::Create() });
			settings.Windows.Add({ "GameObserverWindow",Guid::Create(),EditorWindowDockState::Center,Guid::Create() });

			return settings;
		}
		Array<EditorWindowSetting> Windows;
	};

	//START_GENERATE_TYPE(EditorWindowSettings);
	//START_TYPE_PROPERTIES(EditorWindowSettings);
	//END_TYPE_PROPERTIES;
	//HAS_DEFAULT_CONSTRUCTOR(EditorWindowSettings);
	//END_GENERATE_TYPE(EditorWindowSettings);

#include "EditorWindowSettings.reflect.h"
}