#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Object/API.h>

namespace Portakal
{
	class EditorResource;

	/// <summary>
	/// API for enabling application to use editor resources
	/// </summary>
	class PORTAKAL_API EditorResourceAPI : public API<EditorResourceAPI>
	{
		friend class EditorResourceModule;
	public:
		static EditorResource* GetResource(const String& name);
	private:
		static void ClearResources();
	private:
		EditorResourceAPI(const Array<EditorResource*>& loadedResources);
		virtual ~EditorResourceAPI() override;
	private:
		Array<EditorResource*> mResources;
	};
}