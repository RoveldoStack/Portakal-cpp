#pragma once
#include <Runtime/Reflection/Attribute.h>

namespace Portakal
{
	class PORTAKAL_API GUICustomMenuItem : public Attribute
	{
	public:
		GUICustomMenuItem(const String& location) : _location(location) {}
		GUICustomMenuItem() = default;
		~GUICustomMenuItem() = default;

		FORCEINLINE String GetLocation() const noexcept { return _location; }
	private:
		const String _location;
	};
}