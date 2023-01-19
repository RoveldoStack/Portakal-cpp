#pragma once
#include <Runtime/Reflection/Attribute.h>

namespace Portakal
{
	class PORTAKAL_API GUICustomMenuItem : public Attribute
	{
		GENERATE_CLASS(GUICustomMenuItem);
	public:
		GUICustomMenuItem(const String& location) : _location(location) {}
		GUICustomMenuItem() = default;
		~GUICustomMenuItem() = default;

		FORCEINLINE String GetLocation() const noexcept { return _location; }
	private:
		const String _location;
	};

	START_GENERATE_TYPE(GUICustomMenuItem);
	START_TYPE_PROPERTIES(GUICustomMenuItem);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(GUICustomMenuItem);
	END_GENERATE_TYPE(GUICustomMenuItem);
}