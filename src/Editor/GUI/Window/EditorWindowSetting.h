#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Containers/Guid.h>
#include <Editor/GUI/Window/EditorWindowDockState.h>

namespace Portakal
{
	/// <summary>
	/// Editor window settings
	/// </summary>
	PSTRUCT();
	struct PORTAKAL_API EditorWindowSetting
	{
		EditorWindowSetting() = default;
		~EditorWindowSetting() = default;

		/// <summary>
		/// Title of the window
		/// </summary>
		PFIELD();
		String Name;

		/// <summary>
		/// Unique id of the window
		/// </summary>
		PFIELD();
		Guid ID;

		/// <summary>
		/// Dock state of the window
		/// </summary>
		PFIELD();
		EditorWindowDockState DockState;

		/// <summary>
		/// Owner window id
		/// </summary>
		PFIELD();
		Guid OwnerID;
	};

#include "EditorWindowSetting.reflect.h"
}