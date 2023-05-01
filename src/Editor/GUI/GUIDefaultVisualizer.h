#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API GUIDefaultVisualizer
	{
	public:
		GUIDefaultVisualizer() = delete;
		~GUIDefaultVisualizer() = delete;

		static void DrawDefaultObject(Class* pObject);

	};
}