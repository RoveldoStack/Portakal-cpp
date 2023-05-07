#pragma once
#include <Editor/GUI/Window/EditorWindow.h>

namespace Portakal
{

	class DomainFile;
	class IAssetAuthoringTool;
	PCLASS();
	class PORTAKAL_API AuthoringToolWindow : public EditorWindow
	{
		GENERATE_CLASS(AuthoringToolWindow);
	public:
		AuthoringToolWindow() = default;
		~AuthoringToolWindow() = default;

		void SetToolData(DomainFile* pTargetFile);

		// Inherited via EditorWindow
		virtual void OnShow() override;
		virtual void OnHide() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPaint() override;

	private:
		DomainFile* mTargetFile;
		IAssetAuthoringTool* mAuthoringTool;
	};
#include "AuthoringToolWindow.reflect.h"
}