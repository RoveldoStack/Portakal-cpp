#pragma once
#include <Runtime/Containers/String.h>
#include <Editor/GUI/Window/EditorWindowDockState.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Reflection/Type.h>

namespace Portakal
{
	struct PORTAKAL_API EditorWindowSetting
	{
		String Name;
		Guid ID;
		EditorWindowDockState DockState;
		Guid OwnerID;
	};

	struct PORTAKAL_API EditorWindowSettings : public Class
	{
		GENERATE_CLASS(EditorWindowSettings);
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

	START_GENERATE_TYPE(EditorWindowSettings);
	START_TYPE_PROPERTIES(EditorWindowSettings);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(EditorWindowSettings);
	END_GENERATE_TYPE(EditorWindowSettings);
}