#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Type.h>

namespace Portakal
{
	class PORTAKAL_API MenuItemBehaviour : Class
	{
		GENERATE_CLASS(MenuItemBehaviour);
	public:
		MenuItemBehaviour() = default;
		~MenuItemBehaviour() = default;

		virtual void OnClick() = 0;

		virtual String GetItemName() const noexcept { return "No name";}
	};

	START_GENERATE_TYPE(MenuItemBehaviour);
	START_TYPE_PROPERTIES(MenuItemBehaviour);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(MenuItemBehaviour);
}