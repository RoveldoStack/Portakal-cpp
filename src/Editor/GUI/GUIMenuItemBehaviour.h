#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API MenuItemBehaviour
	{
	public:
		MenuItemBehaviour() = default;
		~MenuItemBehaviour() = default;

		virtual void OnClicked() = 0;

		virtual String GetItemName() const noexcept { return "No name";}
	};
}