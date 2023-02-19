#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class Window;

	/// <summary>
	/// Represents the main application module for the entire Portakal program
	/// </summary>
	class PORTAKAL_API Application
	{
	public:
		virtual ~Application();

		/// <summary>
		/// Whether the application is running
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsRunning() const noexcept { return mRunning; }

		/// <summary>
		/// Whether the application has a quit request in the waiting
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool HasQuitRequest() const noexcept { return mQuitRequest; }

		/// <summary>
		/// Whether the application has a validation request in the waiting
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool HasValidationRequest() const noexcept { return mValidationRequest; }

		/// <summary>
		/// Returns all of the submitted modules
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<ApplicationModule*> GetModules() const noexcept { return mModules; }

		/// <summary>
		/// Returns all of the tick enabled modules
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<ApplicationModule*> GetTickableModules() const noexcept { return mTickableModules; }

		/// <summary>
		/// Returns all of the event enabled modules
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<ApplicationModule*> GetEventableModules() const noexcept { return mEventableModules; }

		/// <summary>
		/// Returns all of the validation enabled modules
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<ApplicationModule*> GetValidationModules() const noexcept { return mValidationModules; }

		/// <summary>
		/// Registers a window to the application's event feed
		/// </summary>
		/// <param name="pWindow"></param>
		void RegisterWindow(Window* pWindow) { mWindows.Add(pWindow); }

		/// <summary>
		/// Removes an existing window from the application's event feed
		/// </summary>
		/// <param name="pWindow"></param>
		void RemoveWindow(Window* pWindow) { mWindows.Remove(pWindow); }

		/// <summary>
		/// Posts a quit message for the application
		/// </summary>
		/// <param name="message"></param>
		void PostQuitMessage(const String& message);

		/// <summary>
		/// Posts a validation request for the application
		/// </summary>
		void PostValidateRequest();

		/// <summary>
		/// Runs one frame of the application
		/// </summary>
		void Run();

		/// <summary>
		/// Creates and submits a module
		/// </summary>
		/// <typeparam name="TModule"></typeparam>
		/// <typeparam name="...TParameters"></typeparam>
		/// <param name="...parameters"></param>
		template<typename TModule,typename... TParameters>
		void CreateModule(TParameters... parameters)
		{
			TModule* pModule = new TModule(parameters...);
			
			mModules.Add(pModule);
		}

		/// <summary>
		/// Returns a module based on its type
		/// </summary>
		/// <typeparam name="TModule"></typeparam>
		/// <returns></returns>
		template<typename TModule>
		TModule* GetModule() const noexcept
		{
			Type* pTargetType = TypeAccessor<TModule>::GetAccessorType();

			for (int i = 0; i < mModules.GetCursor(); i++)
			{
				ApplicationModule* pModule = mModules[i];

				if (pModule->GetType() == pTargetType)
					return (TModule*)pModule;
			}

			return nullptr;
		}

	protected:
		Application();

		/// <summary>
		/// Marks validated
		/// </summary>
		FORCEINLINE void MarkValidated() { mValidationRequest = false; }

		/// <summary>
		/// Runs on intialization of the application
		/// </summary>
		virtual void Initialize() = 0;

		/// <summary>
		/// Runs before the tick routine
		/// </summary>
		virtual void PreTick() = 0;

		/// <summary>
		/// Runs per frame
		/// </summary>
		virtual void Tick() = 0;

		/// <summary>
		/// Runs after the tick routine
		/// </summary>
		virtual void PostTick() = 0;
	private:
		Array<ApplicationModule*> mModules;
		Array<ApplicationModule*> mTickableModules;
		Array<ApplicationModule*> mEventableModules;
		Array<ApplicationModule*> mValidationModules;
		Array<Window*> mWindows;
		bool mRunning;
		bool mQuitRequest;
		bool mValidationRequest;
		String mQuitReason;
	};
}