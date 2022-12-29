#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Application/ApplicationModule.h>
namespace Portakal
{
	class PORTAKAL_API Application
	{
	public:
		virtual ~Application();

		void PostQuitMessage(const String& message);
		void PostValidateRequest();
		void Run();

		template<typename TModule,typename... TParameters>
		void CreateModule(TParameters... parameters)
		{
			TModule* pModule = new TModule(parameters...);
			
			_modules.Add(pModule);
		}

		template<typename TModule>
		TModule* GetModule() const noexcept
		{
			return nullptr;
		}
	protected:
		Application();

		virtual void RunCore() = 0;
	private:
		Array<ApplicationModule*> _modules;
		Array<ApplicationModule*> _tickableModules;
		Array<ApplicationModule*> _eventableModules;
		Array<ApplicationModule*> _validationModules;
		bool _running;
		bool _quitRequest;
		bool _validationRequest;
		String _quitReason;
	};
}