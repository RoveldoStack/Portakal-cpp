#pragma once
#include <Runtime/Application/ApplicationModule.h>
#include <Runtime/Containers/Array.h>
#include <Editor/Resource/EditorResourceRequest.h>

namespace Portakal
{
	/// <summary>
	/// Module params
	/// </summary>
	struct EditorResourceModuleCreateParams
	{
		Array<EditorResourceRequest> Requests;
	};

	class EditorResourceAPI;

	/// <summary>
	/// An application which authors the editor resources
	/// </summary>
	class PORTAKAL_API EditorResourceModule : public ApplicationModule
	{
		GENERATE_CLASS(EditorResourceModule);
	public:
		EditorResourceModule(const Array<EditorResourceRequest>& requests);
		EditorResourceModule() : mAPI (nullptr) {}
		~EditorResourceModule() = default;

		GENERATE_APPLICATION_MODULE(false, false, false);
	private:
		const EditorResourceModuleCreateParams mParams;
		EditorResourceAPI* mAPI;

		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPreTick() override;
		virtual void OnTick() override;
		virtual void OnPostTick() override;
		virtual void PreValidate() override;
		virtual void PostValidate() override;
		virtual void OnEvent(WindowEvent* pEvent) override;
	};

	START_GENERATE_TYPE(EditorResourceModule);
	START_TYPE_PROPERTIES(EditorResourceModule);
	REGISTER_BASE_TYPE(ApplicationModule);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(EditorResourceModule);
	END_GENERATE_TYPE(EditorResourceModule);
}