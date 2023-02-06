#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class Window;
	class PORTAKAL_API Application
	{
	public:
		virtual ~Application();

		FORCEINLINE bool IsRunning() const noexcept { return mRunning; }
		FORCEINLINE bool HasQuitRequest() const noexcept { return mQuitRequest; }
		FORCEINLINE bool HasValidationRequest() const noexcept { return mValidationRequest; }
		FORCEINLINE Array<ApplicationModule*> GetModules() const noexcept { return mModules; }
		FORCEINLINE Array<ApplicationModule*> GetTickableModules() const noexcept { return mTickableModules; }
		FORCEINLINE Array<ApplicationModule*> GetEventableModules() const noexcept { return mEventableModules; }
		FORCEINLINE Array<ApplicationModule*> GetValidationModules() const noexcept { return mValidationModules; }

		void RegisterWindow(Window* pWindow) { mWindows.Add(pWindow); }
		void RemoveWindow(Window* pWindow) { mWindows.Remove(pWindow); }
		void PostQuitMessage(const String& message);
		void PostValidateRequest();
		void Run();

		template<typename TModule,typename... TParameters>
		void CreateModule(TParameters... parameters)
		{
			TModule* pModule = new TModule(parameters...);
			
			mModules.Add(pModule);
		}

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

		FORCEINLINE void MarkValidated() { mValidationRequest = false; }
		virtual void Initialize() = 0;
		virtual void PreTick() = 0;
		virtual void Tick() = 0;
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