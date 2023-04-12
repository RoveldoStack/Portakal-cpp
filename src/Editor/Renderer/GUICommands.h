#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Reflection.h>
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
	class PORTAKAL_API GUICommands
	{
	public:
		static int IntField(const String& name, const int value);
		static float FloatField(const String& name, const float value);
		static long long EnumField(const String& name, const Type* pType, const long long value);
		static String TextField(const String& name, const String& value);
		
	public:
		GUICommands() = delete;
		~GUICommands() = delete;
	};
}