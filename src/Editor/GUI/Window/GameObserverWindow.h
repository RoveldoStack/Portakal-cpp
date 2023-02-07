#pragma once
#include <Editor/GUI/Window/EditorWindow.h>

namespace Portakal
{
	class PORTAKAL_API GameObserverWindow : public EditorWindow
	{
		GENERATE_CLASS(GameObserverWindow);
	public:
		GameObserverWindow() = default;
		~GameObserverWindow() = default;
	private:

		// Inherited via EditorWindow
		virtual void OnShow() override;
		virtual void OnHide() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPaint() override;
	};

	START_GENERATE_TYPE(GameObserverWindow);
	START_TYPE_PROPERTIES(GameObserverWindow);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(GameObserverWindow);
	END_GENERATE_TYPE(GameObserverWindow);
}