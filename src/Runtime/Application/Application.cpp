#include "Application.h"
#include <Runtime/Log/Log.h>
#include <Runtime/Message/MessageAPI.h>
#include <Runtime/Time/Stopwatch.h>
#include <Runtime/Time/Time.h>
#include <Runtime/Window/Window.h>
#include <Runtime/Window/WindowEvent.h>

namespace Portakal
{
	Application::~Application()
	{

	}

	void Application::PostQuitMessage(const String& message)
	{
		mQuitRequest = true;
		mQuitReason = message;
	}

	void Application::PostValidateRequest()
	{
		mValidationRequest = true;
	}


	void Application::Run()
	{
		/*
		* Create module categories
		*/
		for (int i = 0; i < mModules.GetCursor(); i++)
		{
			ApplicationModule* pModule = mModules[i];

			if (pModule->IsEventsEnabled())
				mEventableModules.Add(pModule);
			if (pModule->IsTickEnabled())
				mTickableModules.Add(pModule);
			if (pModule->IsValidationLayersEnabled())
				mValidationModules.Add(pModule);
		}

		/*
		* Initialize modules
		*/
		for (int i = 0; i < mModules.GetCursor(); i++)
		{
			ApplicationModule* pModule = mModules[i];

			pModule->_SetOwnerApplication(this);

			pModule->OnInitialize();

			BROADCAST_MESSAGE("Module initialized");
		}

		/*
		* Initialize
		*/
		Initialize();

		/*
		* Run core
		*/
		mRunning = true;
		Stopwatch deltaTimer = {};
		while (!HasQuitRequest())
		{
			/*
			* Mark the starting of the frame
			*/
			deltaTimer.Mark();

			/*
			* Poll window events
			*/
			for(unsigned int i = 0;i<mWindows.GetCursor();i++)
				mWindows[i]->PollEvents();

			/*
			* Validate window state
			*/
			for(unsigned int i = 0;i<mWindows.GetCursor();i++)
				if (!mWindows[i]->IsActive())
					PostQuitMessage("Window is not active");

			/*
			* Broadcast events
			*/
			for (unsigned int i = 0; i < mWindows.GetCursor(); i++)
			{
				const Array<WindowEvent*> events = mWindows[i]->GetPolledEvents();
				for (unsigned int eventIndex = 0; eventIndex < events.GetCursor(); eventIndex++)
				{
					WindowEvent* pEvent = events[eventIndex];

					for (int i = mEventableModules.GetCursor() - 1; i >= 0; i--)
					{
						ApplicationModule* pModule = mEventableModules[i];

						pModule->OnEvent(pEvent);

						if (pEvent->IsHandled())
							break;
					}
				}
			}

			/*
			* Check at the begining of a frame session if one of the modules submitted a validation request
			*/
			if (mValidationRequest)
			{
				/*
				* Pre validate
				*/
				for (int i = mValidationModules.GetCursor() - 1; i >= 0; i--)
				{
					mValidationModules[i]->PreValidate();
				}

				/*
				* Post validate
				*/
				for (unsigned int i = 0; i < mValidationModules.GetCursor(); i++)
					mValidationModules[i]->PostValidate();

				mValidationRequest = false;
			}
			
			/*
			* Pre-tick applicaiton
			*/
			PreTick();

			/*
			* Tick the modules
			*/
			for (unsigned int i = 0; i < mTickableModules.GetCursor(); i++)
				mTickableModules[i]->OnPreTick();

			for (unsigned int i = 0; i < mTickableModules.GetCursor(); i++)
				mTickableModules[i]->OnTick();

			for (unsigned int i = 0; i < mTickableModules.GetCursor(); i++)
				mTickableModules[i]->OnPostTick();

			/*
			* Post-tick application
			*/
			PostTick();

			/*
			* Mark the ending of the frame
			*/
			deltaTimer.Mark();

			/*
			* Set last frame's delta time
			*/
			const float deltaTime = deltaTimer.GetAsMilliseconds();
			Time::_SetDeltaTime(deltaTime);
		}
		mRunning = false;

		/*
		* Post exit message
		*/
		LOG("Application", "Exit message: %s", *mQuitReason);

		/*
		* Finalize
		*/
		for (int i = mModules.GetCursor() - 1; i >= 0; i--)
		{
			ApplicationModule* pModule = mModules[i];


			BROADCAST_MESSAGE("Module finalizing...");

			pModule->OnFinalize();
			pModule->_SetOwnerApplication(nullptr);

			delete pModule;
		}

		mModules.Clear();
		mEventableModules.Clear();
		mTickableModules.Clear();
		mValidationModules.Clear();
	}

	Application::Application()
	{
		mQuitRequest = false;
		mValidationRequest = false;
		mRunning = false;
	}

}

