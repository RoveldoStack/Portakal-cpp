#pragma once
#include <Editor/GUI/Window/EditorWindow.h>

namespace Portakal
{
	class PORTAKAL_API TestWindow : public EditorWindow
	{
		GENERATE_CLASS(TestWindow);
	public:
		TestWindow() = default;
		virtual ~TestWindow() override = default;

		virtual void OnShow() override;
		virtual void OnHide() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPaint() override;
	};

	//START_GENERATE_TYPE(TestWindow);
	//START_TYPE_PROPERTIES(TestWindow);
	//REGISTER_BASE_TYPE(EditorWindow);
	//END_TYPE_PROPERTIES;
	//HAS_DEFAULT_CONSTRUCTOR(TestWindow);
	//END_GENERATE_TYPE(TestWindow);

#include "TestWindow.reflect.h"
}