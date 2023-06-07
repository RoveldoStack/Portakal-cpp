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
		virtual void Initialize() override;
		virtual void Execute() override;
		virtual void Finalize() override;
	private:
		String mIntendedAspectTypeName;

	};
#include "InvalidAspect.reflect.h"
}