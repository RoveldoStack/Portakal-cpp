#pragma once
#include <Runtime/World/SceneAspect.h>

namespace Portakal
{
	PCLASS();
	class PORTAKAL_API InvalidAspect : public SceneAspect
	{
		GENERATE_CLASS(InvalidAspect);
	public:
		InvalidAspect() = default;
		~InvalidAspect() = default;

		FORCEINLINE String GetIntendedAspect() const noexcept { return mIntendedAspectTypeName; }
		FORCEINLINE void SetIntendedAspect(const String& intendedAspect) { mIntendedAspectTypeName = intendedAspect; }

		// Inherited via SceneAspect
		virtual void InitializeCore() override;
		virtual void ExecuteCore() override;
		virtual void FinalizeCore() override;
	private:
		// Inherited via SceneAspect
		virtual bool RegisterComponentCore(Component* pComponent) override;
		virtual void RemoveComponentCore(Component* pComponent) override;
	private:
		String mIntendedAspectTypeName;

	};
#include "InvalidAspect.reflect.h"
}