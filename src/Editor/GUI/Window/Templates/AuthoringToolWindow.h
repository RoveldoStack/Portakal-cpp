#pragma once
#include <Editor/GUI/Window/EditorWindow.h>

namespace Portakal
{

	class DomainFile;
	class IAssetAuthoringTool;
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

	//START_GENERATE_TYPE(AuthoringToolWindow);
	//START_TYPE_PROPERTIES(AuthoringToolWindow);
	//REGISTER_BASE_TYPE(EditorWindow);
	//END_TYPE_PROPERTIES;
	//HAS_DEFAULT_CONSTRUCTOR(AuthoringToolWindow);
	//END_GENERATE_TYPE(AuthoringToolWindow);

#include "AuthoringToolWindow.reflect.h"
}