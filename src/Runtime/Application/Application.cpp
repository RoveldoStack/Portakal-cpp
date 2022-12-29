#include "Application.h"
#include <Runtime/Log/Log.h>

namespace Portakal
{
	Application::~Application()
	{

	}

	void Application::PostQuitMessage(const String& message)
	{
		_quitRequest = true;
		_quitReason = message;
	}

	void Application::PostValidateRequest()
	{
		_validationRequest = true;
	}

	void Application::Run()
	{
		/*
		* Create module categories
		*/
		for (int i = 0; i < _modules.GetCursor(); i++)
		{
			ApplicationModule* pModule = _modules[i];

			if (pModule->IsEventsEnabled())
				_eventableModules.Add(pModule);
			if (pModule->IsTickEnabled())
				_tickableModules.Add(pModule);
			if (pModule->IsValidationLayersEnabled())
				_validationModules.Add(pModule);
		}

		/*
		* Initialize modules
		*/
		for (int i = 0; i < _modules.GetCursor(); i++)
		{
			ApplicationModule* pModule = _modules[i];

			pModule->_SetOwnerApplication(this);

			pModule->OnInitialize();
		}

		/*
		* Run core
		*/
		_running = true;
		RunCore();
		_running = false;

		/*
		* Post exit message
		*/
		LOG("Application", "Exit message: %s", *_quitReason);

		/*
		* Finalize
		*/
		for (int i = _modules.GetCursor() - 1; i >= 0; i--)
		{
			ApplicationModule* pModule = _modules[i];

			pModule->OnFinalize();
			pModule->_SetOwnerApplication(nullptr);

			delete pModule;
		}

		_modules.Clear();
		_eventableModules.Clear();
		_tickableModules.Clear();
		_validationModules.Clear();
	}

	Application::Application()
	{
		_quitReason = false;
		_validationRequest = false;
	}

}

