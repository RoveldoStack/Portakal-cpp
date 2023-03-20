#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class EditorResource;

	/// <summary>
	/// API for enabling application to use editor resources
	/// </summary>
	class PORTAKAL_API EditorResourceAPI
	{
		friend class EditorResourceModule;
	public:
		static EditorResource* GetResource(const String& name);
	private:
		static void ClearResources();
	private:
		static Array<EditorResource*> sResources;
	private:
		EditorResourceAPI() = delete;
		~EditorResourceAPI() = delete;
	};
}