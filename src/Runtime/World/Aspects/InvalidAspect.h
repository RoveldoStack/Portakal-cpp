#pragma once
#include <Runtime/World/SceneAspect.h>

namespace Portakal
{
	class PORTAKAL_API InvalidAspect : public SceneAspect
	{
		GENERATE_CLASS(InvalidAspect);
	public:
		InvalidAspect() = default;
		~InvalidAspect() = default;

		FORCEINLINE String GetIntendedAspect() const noexcept { return mIntendedAspectTypeName; }
		FORCEINLINE void SetIntendedAspect(const String& intendedAspect) { mIntendedAspectTypeName = intendedAspect; }

		// Inherited via SceneAspect
		virtual void OnInitialize() override;
		virtual void OnExecute() override;
		virtual void OnFinalize() override;
	private:
		String mIntendedAspectTypeName;
	};

	START_GENERATE_TYPE(InvalidAspect);
	START_TYPE_PROPERTIES(InvalidAspect);
	REGISTER_BASE_TYPE(SceneAspect);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(InvalidAspect);
	END_GENERATE_TYPE(InvalidAspect);
}