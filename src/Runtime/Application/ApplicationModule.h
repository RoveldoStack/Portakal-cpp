#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class Application;
	class WindowEvent;

	class PORTAKAL_API ApplicationModule : public Class
	{
		GENERATE_CLASS(ApplicationModule);
		friend class Application;
	public:
		FORCEINLINE virtual bool IsTickEnabled() const noexcept = 0;
		FORCEINLINE virtual bool IsEventsEnabled() const noexcept = 0 ;
		FORCEINLINE virtual bool IsValidationLayersEnabled() const noexcept = 0;

		virtual void OnInitialize() = 0;
		virtual void OnFinalize() = 0;
		virtual void OnPreTick() = 0;
		virtual void OnTick() = 0;
		virtual void OnPostTick() = 0;
		virtual void PreValidate() = 0;
		virtual void PostValidate() = 0;
		virtual void OnEvent(WindowEvent* pEvent) = 0;

	protected:
		ApplicationModule() = default;
		virtual ~ApplicationModule() = default;

		FORCEINLINE Application* GetOwnerApplication() const noexcept { return mOwnerApplication; }
	private:	

		void _SetOwnerApplication(Application* pApplication) { mOwnerApplication = pApplication; }
	private:
		Application* mOwnerApplication;
	};
	START_GENERATE_TYPE(ApplicationModule);

	START_TYPE_PROPERTIES(ApplicationModule)
	END_TYPE_PROPERTIES;

	VIRTUAL_TYPE;
	END_GENERATE_TYPE(ApplicationModule);


#define GENERATE_APPLICATION_MODULE(tickEnabled,eventsEnabled,validationEnabled) public: \
																	FORCEINLINE virtual bool IsTickEnabled() const noexcept override { return tickEnabled;} \
																	FORCEINLINE virtual bool IsEventsEnabled() const noexcept override { return eventsEnabled;}\
																	FORCEINLINE virtual bool IsValidationLayersEnabled() const noexcept override { return validationEnabled; }
}