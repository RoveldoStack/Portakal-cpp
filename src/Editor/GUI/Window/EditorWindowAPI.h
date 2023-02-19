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
	private:
		static EditorWindowAPI* mAPI;
	public:
		/// <summary>
		/// Creates new window via type
		/// </summary>
		/// <param name="pType"></param>
		/// <returns></returns>
		static EditorWindow* CreateWindowViaType(Type* pType);

		/// <summary>
		/// Creates new window via setting
		/// </summary>
		/// <param name="setting"></param>
		/// <returns></returns>
		static EditorWindow* CreateFromSetting(const EditorWindowSetting& setting);

		/// <summary>
		/// Creates a window via template type
		/// </summary>
		/// <typeparam name="TWindow"></typeparam>
		/// <returns></returns>
		template<typename TWindow>
		static TWindow* CreateWindowViaType()
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

		/// <summary>
		/// Returns the windows
		/// </summary>
		/// <returns></returns>
		Array<EditorWindow*> GetWindows() const noexcept { return _windows; }

		EditorWindow* CreateWindowInternal(Type* pTargetType);
		EditorWindow* CreateWindowFromSettingsInternal(Type* pType, const EditorWindowSetting& setting);
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