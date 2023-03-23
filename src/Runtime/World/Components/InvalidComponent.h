#pragma once
#include <Runtime/World/Component.h>

namespace Portakal
{
	class PORTAKAL_API InvalidComponent : public Component
	{
		GENERATE_CLASS(InvalidComponent);
	public:
		FORCEINLINE String GetIntendedType() const noexcept { return mIntendedType; }
		FORCEINLINE void SetIntendedType(const String& type) { mIntendedType = type; }


		int myInt;
		String myString;
	private:
		String mIntendedType;

		// Inherited via Component
		virtual void DestroyCore() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
	};


	START_GENERATE_TYPE(InvalidComponent);
	START_TYPE_PROPERTIES(InvalidComponent);
	REGISTER_BASE_TYPE(Component);
	REGISTER_FIELD(InvalidComponent, myInt, int, AccessSpecifier::Public);
	REGISTER_FIELD(InvalidComponent, myString, String, AccessSpecifier::Public);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(InvalidComponent);
	END_GENERATE_TYPE(InvalidComponent);
}