#pragma once
#include <Editor/GUI/Window/EditorWindow.h>

namespace Portakal
{
	class PORTAKAL_API WorldObserverWindow : public EditorWindow
	{
		GENERATE_CLASS(WorldObserverWindow);
	public:
		WorldObserverWindow() = default;
		~WorldObserverWindow() = default;

	private:

		virtual void OnShow() override;
		// Inherited via EditorWindow
		virtual void OnHide() override;

		virtual void OnInitialize() override;

		virtual void OnFinalize() override;

		virtual void OnPaint() override;

	};

	START_GENERATE_TYPE(WorldObserverWindow);
	START_TYPE_PROPERTIES(WorldObserverWindow);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(WorldObserverWindow);
	END_GENERATE_TYPE(WorldObserverWindow);
}