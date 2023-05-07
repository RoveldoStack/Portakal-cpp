#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Containers/Guid.h>
#include <Editor/GUI/Window/EditorWindowDockState.h>

namespace Portakal
{
	/// <summary>
	/// Editor window settings
	/// </summary>
	struct PORTAKAL_API EditorWindowSetting : public Class
	{
		GENERATE_CLASS(EditorWindowSetting);

		EditorWindowSetting() = default;
		~EditorWindowSetting() = default;

		/// <summary>
		/// Title of the window
		/// </summary>
		FIELD();
		String Name;

		/// <summary>
		/// Unique id of the window
		/// </summary>
		FIELD();
		Guid ID;

		/// <summary>
		/// Dock state of the window
		/// </summary>
		FIELD();
		EditorWindowDockState DockState;

		/// <summary>
		/// Owner window id
		/// </summary>
		FIELD();
		Guid OwnerID;
	};

#include "EditorWindowSetting.reflect.h"
}