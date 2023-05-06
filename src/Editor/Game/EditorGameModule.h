#pragma once
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class EditorGameAPI;
	class PORTAKAL_API EditorGameModule : public ApplicationModule
	{
		GENERATE_CLASS(EditorGameModule);
		GENERATE_APPLICATION_MODULE(false, false, false);
	public:
		EditorGameModule() = default;
		~EditorGameModule() = default;

	private:
		// Inherited via ApplicationModule
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPreTick() override;
		virtual void OnTick() override;
		virtual void OnPostTick() override;
		virtual void PreValidate() override;
		virtual void PostValidate() override;
		virtual void OnEvent(WindowEvent* pEvent) override;
	private:
		EditorGameAPI* mAPI;
	};


#include "EditorGameModule.reflect.h"
}