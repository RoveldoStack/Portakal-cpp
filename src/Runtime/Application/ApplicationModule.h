#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class Application;
	class WindowEvent;

	/// <summary>
	/// Represents a single responsibility of a the application
	/// Application modules are used to populate the behaviours on application
	/// </summary>
	PCLASS();
	class PORTAKAL_API ApplicationModule : public Class
	{
		GENERATE_CLASS(ApplicationModule,Virtual);
		friend class Application;
	public:
		/// <summary>
		/// Returns whether this module ticks
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual bool IsTickEnabled() const noexcept = 0;

		/// <summary>
		/// Returns whether this module accepts window events
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual bool IsEventsEnabled() const noexcept = 0;

		/// <summary>
		/// Returns whether this module is validated
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual bool IsValidationLayersEnabled() const noexcept = 0;

		/// <summary>
		/// Called on first initialization
		/// </summary>
		virtual void OnInitialize() = 0;

		/// <summary>
		/// Called on termination
		/// </summary>
		virtual void OnFinalize() = 0;

		/// <summary>
		/// Called before tick procedure
		/// </summary>
		virtual void OnPreTick() = 0;

		/// <summary>
		/// Called every frame
		/// </summary>
		virtual void OnTick() = 0;

		/// <summary>
		/// Called after tick procedure
		/// </summary>
		virtual void OnPostTick() = 0;

		/// <summary>
		/// Called before application validates itself
		/// </summary>
		virtual void PreValidate() = 0;

		/// <summary>
		/// Called after application validates itself
		/// </summary>
		virtual void PostValidate() = 0;

		/// <summary>
		/// Called when application sends anew window event
		/// </summary>
		/// <param name="pEvent"></param>
		virtual void OnEvent(WindowEvent* pEvent) = 0;

	protected:
		ApplicationModule() = default;
		virtual ~ApplicationModule() = default;

		/// <summary>
		/// Returns the owner application
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Application* GetOwnerApplication() const noexcept { return mOwnerApplication; }

		/// <summary>
		/// Post a validation request for the application
		/// </summary>
		void PostValidationRequest();

		/// <summary>
		/// Posts a quit request for the application
		/// </summary>
		/// <param name="message"></param>
		void PostQuitMessage(const String& message);
	private:	

		/// <summary>
		/// Internal setter for the owner application
		/// </summary>
		/// <param name="pApplication"></param>
		void _SetOwnerApplication(Application* pApplication) { mOwnerApplication = pApplication; }
	private:
		Application* mOwnerApplication;
	};

#include "ApplicationModule.reflect.h"

#define GENERATE_APPLICATION_MODULE(tickEnabled,eventsEnabled,validationEnabled) public: \
																	FORCEINLINE virtual bool IsTickEnabled() const noexcept override { return tickEnabled;} \
																	FORCEINLINE virtual bool IsEventsEnabled() const noexcept override { return eventsEnabled;}\
																	FORCEINLINE virtual bool IsValidationLayersEnabled() const noexcept override { return validationEnabled; }
}