#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Type.h>
#include <Editor/GUI/Window/EditorWindowSettings.h>
#include <Editor/GUI/Window/EditorWindow.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	class PORTAKAL_API EditorWindowAPI
	{
	private:
		static EditorWindowAPI* mAPI;
	public:
		static EditorWindow* CreateWindow(Type* pType);
		static EditorWindow* CreateFromSettings(const EditorWindowSettings& settings);

		template<typename TWindow>
		static TWindow* CreateWindow()
		{
			if (mAPI == nullptr)
			{
				LOG("EditorWindowAPI", "Invalid  api");
				return nullptr;
			}

			return mAPI->CreateWindowInternal<TWindow>();
		}
	public:
		EditorWindowAPI();
		~EditorWindowAPI();

		Array<EditorWindow*> GetWindows() const noexcept { return _windows; }
		EditorWindow* CreateWindowInternal(Type* pTargetType);
		void DeleteWindow(EditorWindow* pWindow);

		void PreValidate();
		void PostValidate();
		void Paint();

		template<typename TWindow>
		TWindow* CreateWindowInternal()
		{
			return (TWindow*)CreateWindowInternal(TypeAccessor<TWindow>::GetAccessorType());
		}
	private:
		Array<EditorWindow*> _windows;
	};
}