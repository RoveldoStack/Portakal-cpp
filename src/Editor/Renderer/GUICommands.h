#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Math/Vector2F.h>
#include <Runtime/Math/Vector3.h>
#include <Runtime/Math/Color4.h>
#include <Editor/Renderer/GUIColorType.h>
#include <Editor/Renderer/GUIInputTextFlags.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Math/Color4F.h>
namespace Portakal
{
	class PORTAKAL_API GUICommands
	{
	public:
		static void Text(const String& content);

		static int IntField(const String& name, const int value);
		static int IntField(const String& name, const int value,bool& bChanged);

		static float FloatField(const String& name, const float value);
		static float FloatField(const String& name, const float value,bool& bChanged);

		static long long EnumField(const String& name, const Type* pType, const long long value);
		static long long EnumField(const String& name, const Type* pType, const long long value,bool& bChanged);

		static Vector2F Vector2FField(const String& name, const Vector2F value);
		static Vector2F Vector2FField(const String& name, const Vector2F value,bool& bChanged);

		static Vector3F Vector3FField(const String& name, const Vector3F value);
		static Vector3F Vector3FField(const String& name, const Vector3F value, bool& bChanged);

		static String TextField(const String& name, const String& value);
		static String TextField(const String& name, const String& value, bool& bChanged);
		static String MultilineTextField(const String& name, const String& value, const Vector2F& size,const GUIInputTextFlags flags = GUIInputTextFlags::None);

		static Color4 RgbaField(const String& name, const Color4& value);
		static Color4 RgbaField(const String& name, const Color4& value, bool& bChanged);
		static Color4F RgbaFField(const String& name, const Color4F& value);
		static Color4F RgbaFField(const String& name, const Color4F& value, bool& bChanged);
		
		static void PushColor(const GUIColorType type,const Color4& color);
		static void PopColor();
	public:
		GUICommands() = delete;
		~GUICommands() = delete;
	};
}