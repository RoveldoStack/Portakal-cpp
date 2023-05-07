#pragma once
#include <Editor/GUI/Window/EditorWindow.h>

namespace Portakal
{
	PCLASS();
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

#include "TestWindow.reflect.h"
}