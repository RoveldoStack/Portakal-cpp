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

		FORCEINLINE bool IsRunning() const noexcept { return _running; }
		FORCEINLINE bool HasQuitRequest() const noexcept { return _quitRequest; }
		FORCEINLINE bool HasValidationRequest() const noexcept { return _validationRequest; }
		FORCEINLINE Array<ApplicationModule*> GetModules() const noexcept { return _modules; }
		FORCEINLINE Array<ApplicationModule*> GetTickableModules() const noexcept { return _tickableModules; }
		FORCEINLINE Array<ApplicationModule*> GetEventableModules() const noexcept { return _eventableModules; }
		FORCEINLINE Array<ApplicationModule*> GetValidationModules() const noexcept { return _validationModules; }

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
			Type* pTargetType = TypeAccessor<TModule>::GetAccessorType();

			for (int i = 0; i < _modules.GetCursor(); i++)
			{
				ApplicationModule* pModule = _modules[i];

				if (pModule->GetType() == pTargetType)
					return (TModule*)pModule;
			}

			return nullptr;
		}

	protected:
		Application();

		FORCEINLINE void MarkValidated() { _validationRequest = false; }
		virtual void Initialize() = 0;
		virtual bool Tick() = 0;
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