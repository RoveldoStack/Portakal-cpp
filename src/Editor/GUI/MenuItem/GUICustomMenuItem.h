#pragma once
#include <Runtime/Reflection/Attribute.h>

namespace Portakal
{
	/// <summary>
	/// An attribute for marking a class as a menu item
	/// </summary>
	class PORTAKAL_API GUICustomMenuItem : public Attribute
	{
		GENERATE_CLASS(GUICustomMenuItem);
	public:
		GUICustomMenuItem(const String& location) : mLocation(location) {}
		GUICustomMenuItem() = default;
		~GUICustomMenuItem() = default;

		/// <summary>
		/// Returns the target menu path location
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetLocation() const noexcept { return mLocation; }
	private:
		const String mLocation;
	};

	/*START_GENERATE_TYPE(GUICustomMenuItem);
	START_TYPE_PROPERTIES(GUICustomMenuItem);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(GUICustomMenuItem);
	END_GENERATE_TYPE(GUICustomMenuItem);*/

#include "GUICustomMenuItem.reflect.h"
}