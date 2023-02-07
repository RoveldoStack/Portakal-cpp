#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class EditorResource;
	class PORTAKAL_API EditorResourceAPI
	{
		friend class EditorResourceModule;
	private:
		static EditorResourceAPI* sAPI;
	public:
		static EditorResource* GetResource(const String& name);
	private:
		EditorResourceAPI(const Array<EditorResource*>& resources);
		~EditorResourceAPI();
	private:
		Array<EditorResource*> mResources;

	};
}