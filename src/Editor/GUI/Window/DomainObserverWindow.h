#pragma once
#include <Editor/GUI/Window/EditorWindow.h>

namespace Portakal
{
	class DomainFolder;
	class PORTAKAL_API DomainObserverWindow : public EditorWindow
	{
		GENERATE_CLASS(DomainObserverWindow);
	public:
		DomainObserverWindow() = default;
		~DomainObserverWindow() = default;
	private:

		// Inherited via EditorWindow
		virtual void OnShow() override;
		virtual void OnHide() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPaint() override;
	private:
		DomainFolder* mCurrentFolder;

	};

	START_GENERATE_TYPE(DomainObserverWindow);
	START_TYPE_PROPERTIES(DomainObserverWindow);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(DomainObserverWindow);
	END_GENERATE_TYPE(DomainObserverWindow);
}