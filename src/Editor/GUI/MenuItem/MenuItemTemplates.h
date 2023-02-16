#pragma once
#include <Editor/GUI/MenuItem/GUIMenuItemBehaviour.h>
#include <Editor/GUI/MenuItem/GUICustomMenuItem.h>
#include <Runtime/Log/Log.h>
#include <Editor/GUI/Window/EditorWindowAPI.h>
#include <Editor/GUI/Window/Templates/TestWindow.h>

namespace Portakal
{
	class PORTAKAL_API TestMenuItem : public MenuItemBehaviour
	{
		GENERATE_CLASS(TestMenuItem);
	public:
		virtual void OnClick() override
		{
			LOG("TESt", "TEST");
		}
	};

	START_GENERATE_TYPE(TestMenuItem);
	START_TYPE_PROPERTIES(TestMenuItem);
	REGISTER_TYPE_ATTRIBUTE(GUICustomMenuItem, "Test/My test button")
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(TestMenuItem);
	END_GENERATE_TYPE(TestMenuItem);


	class PORTAKAL_API TestWindowCreateButton : public MenuItemBehaviour
	{
		GENERATE_CLASS(TestWindowCreateButton);
	public:
		virtual void OnClick() override
		{
			EditorWindowAPI::CreateWindowViaType<TestWindow>();
		}
	};

	START_GENERATE_TYPE(TestWindowCreateButton);
	START_TYPE_PROPERTIES(TestWindowCreateButton);
	REGISTER_TYPE_ATTRIBUTE(GUICustomMenuItem, "Test/Test window")
		END_TYPE_PROPERTIES;
	CONCRETE_TYPE(TestWindowCreateButton);
	END_GENERATE_TYPE(TestWindowCreateButton);
}