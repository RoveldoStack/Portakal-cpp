#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Type.h>
#include <Editor/GUI/Window/EditorWindowSettings.h>
#include <Editor/GUI/Window/EditorWindow.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	/// <summary>
	/// API for enabling application to use editor window operations
	/// </summary>
	class PORTAKAL_API EditorWindowAPI
	{
		friend class GUIWindowModule;
	public:
		FORCEINLINE static Array<EditorWindow*> GetWindows() { return sWindows; }

		template<typename TWindow,typename... TParams>
		static TWindow* Create(TParams... params)
		{
			/*
			* Validate if it's a sub class of EditorWindow class
			*/
			Type* pType = TypeAccessor<TWindow>::GetAccessorType();
			if (!pType->IsSubClassOf(typeof(EditorWindow)))
			{
				return nullptr;
			}

			/*
			* Create instance
			*/
			TWindow* pWindow = new TWindow(params...);
			pWindow->_SetParentWindow(nullptr);
			pWindow->_SetPosition({ 100,100 });
			pWindow->_SetSize({ 512,512 });

			pWindow->OnInitialize();
			pWindow->OnShow();

			sWindows.Add(pWindow);

			return pWindow;
		}

		static EditorWindow* Create(Type* pType);
	private:
		static EditorWindow* CreateFromSetting(const EditorWindowSetting& setting);
		static void Paint();
		static void ClearAllWindows();
		static void DeleteWindow(EditorWindow* pWindow);
	private:
		static Array<EditorWindow*> sWindows;
	private:
		EditorWindowAPI() = delete;
		~EditorWindowAPI() = delete;
	};
}