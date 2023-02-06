#pragma once
#include <Runtime/Reflection/Attribute.h>

namespace Portakal
{
	class PORTAKAL_API GUICustomMenuItem : public Attribute
	{
		GENERATE_CLASS(GUICustomMenuItem);
	public:
		GUICustomMenuItem(const String& location) : mLocation(location) {}
		GUICustomMenuItem() = default;
		~GUICustomMenuItem() = default;

		FORCEINLINE String GetLocation() const noexcept { return mLocation; }
	private:
		const String mLocation;
	};

	START_GENERATE_TYPE(GUICustomMenuItem);
	START_TYPE_PROPERTIES(GUICustomMenuItem);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(GUICustomMenuItem);
	END_GENERATE_TYPE(GUICustomMenuItem);
}