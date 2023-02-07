#pragma once
#include <Runtime/Application/ApplicationModule.h>
#include <Runtime/Containers/Array.h>
#include <Editor/Resource/EditorResourceRequest.h>

namespace Portakal
{
	struct EditorResourceModuleCreateParams
	{
		Array<EditorResourceRequest> Requests;
	};

	class EditorResourceAPI;
	class PORTAKAL_API EditorResourceModule : public ApplicationModule
	{
	public:
		EditorResourceModule(const Array<EditorResourceRequest>& requests);
		EditorResourceModule() : mAPI (nullptr) {}
		~EditorResourceModule() = default;

		GENERATE_APPLICATION_MODULE(false, false, false);
	private:
		const EditorResourceModuleCreateParams mParams;
		EditorResourceAPI* mAPI;


		// Inherited via ApplicationModule
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPreTick() override;
		virtual void OnTick() override;
		virtual void OnPostTick() override;
		virtual void PreValidate() override;
		virtual void PostValidate() override;
		virtual void OnEvent(WindowEvent* pEvent) override;
	};
}