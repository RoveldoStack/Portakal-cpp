#pragma once
#include <Editor/GUI/Window/EditorWindow.h>

namespace Portakal
{
	class PORTAKAL_API ObjectObserverWindow : public EditorWindow
	{
		GENERATE_CLASS(ObjectObserverWindow);
	public:
		ObjectObserverWindow() = default;
		~ObjectObserverWindow() = default;

	private:

		// Inherited via EditorWindow
		virtual void OnShow() override;
		virtual void OnHide() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPaint() override;
	};

	START_GENERATE_TYPE(ObjectObserverWindow);
	START_TYPE_PROPERTIES(ObjectObserverWindow);
	REGISTER_BASE_TYPE(EditorWindow);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(ObjectObserverWindow);
	END_GENERATE_TYPE(ObjectObserverWindow);
}