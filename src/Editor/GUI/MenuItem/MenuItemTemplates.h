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
	HAS_DEFAULT_CONSTRUCTOR(TestMenuItem);
	END_GENERATE_TYPE(TestMenuItem);


	class PORTAKAL_API TestWindowCreateButton : public MenuItemBehaviour
	{
		GENERATE_CLASS(TestWindowCreateButton);
	public:
		virtual void OnClick() override
		{
			EditorWindowAPI::Create<TestWindow>();
		}
	};

	START_GENERATE_TYPE(TestWindowCreateButton);
	START_TYPE_PROPERTIES(TestWindowCreateButton);
	REGISTER_TYPE_ATTRIBUTE(GUICustomMenuItem, "Test/Test window")
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(TestWindowCreateButton);
	END_GENERATE_TYPE(TestWindowCreateButton);

	class PORTAKAL_API CreateEmptySceneButton : public MenuItemBehaviour
	{
		GENERATE_CLASS(CreateEmptySceneButton);
	public:
		virtual void OnClick() override;
	};

	START_GENERATE_TYPE(CreateEmptySceneButton);
	START_TYPE_PROPERTIES(CreateEmptySceneButton);
	REGISTER_TYPE_ATTRIBUTE(GUICustomMenuItem, "Scene/Create new")
		END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(CreateEmptySceneButton);
	END_GENERATE_TYPE(CreateEmptySceneButton);

	class PORTAKAL_API CreateDisplayButton : public MenuItemBehaviour
	{
		GENERATE_CLASS(CreateDisplayButton);
	public:
		virtual void OnClick() override;
	};

	START_GENERATE_TYPE(CreateDisplayButton);

	START_TYPE_PROPERTIES(CreateDisplayButton);
	REGISTER_TYPE_ATTRIBUTE(GUICustomMenuItem, "Display/Create new")
	END_TYPE_PROPERTIES;

	HAS_DEFAULT_CONSTRUCTOR(CreateDisplayButton);
	END_GENERATE_TYPE(CreateDisplayButton);
}