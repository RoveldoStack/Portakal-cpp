#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Type.h>
#include <Runtime/Reflection/Reflection.h>
namespace Portakal
{
	/// <summary>
	/// Describes a menu item button behaviour
	/// </summary>
	PCLASS(Virtual);
	class PORTAKAL_API GUIMenuItemBehaviour : public Class
	{
		GENERATE_CLASS(GUIMenuItemBehaviour);
	public:
		GUIMenuItemBehaviour() = default;
		~GUIMenuItemBehaviour() = default;

		/// <summary>
		/// Called upon clicking
		/// </summary>
		virtual void OnClick() = 0;

		/// <summary>
		/// Returns the name of the button
		/// </summary>
		/// <returns></returns>
		virtual String GetItemName() const noexcept { return "No name";}
	};
#include "GUIMenuItemBehaviour.reflect.h"
}