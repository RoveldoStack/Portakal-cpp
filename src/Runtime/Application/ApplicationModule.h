#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class Application;
	class WindowEvent;

	class PORTAKAL_API ApplicationModule
	{
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
	private:
		ApplicationModule() = default;
		~ApplicationModule() = default;

		void _SetOwnerApplication(Application* pApplication) { _ownerApplication = pApplication; }
	private:
		Application* _ownerApplication;
	};
}