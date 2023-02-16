#include <Editor/GUI/Window/EditorWindow.h>

namespace Portakal
{

	class DomainFile;
	class IAssetAuthorizationTool;
	class PORTAKAL_API AuthorizationToolWindow : public EditorWindow
	{
		GENERATE_CLASS(AuthorizationToolWindow);
	public:
		AuthorizationToolWindow() = default;
		~AuthorizationToolWindow() = default;

		void SetToolData(DomainFile* pTargetFile);

		// Inherited via EditorWindow
		virtual void OnShow() override;
		virtual void OnHide() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPaint() override;

	private:
		DomainFile* mTargetFile;
		IAssetAuthorizationTool* mAuthorizationTool;
	};

	START_GENERATE_TYPE(AuthorizationToolWindow);
	START_TYPE_PROPERTIES(AuthorizationToolWindow);
	REGISTER_BASE_TYPE(EditorWindow);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(AuthorizationToolWindow);
	END_GENERATE_TYPE(AuthorizationToolWindow);
}