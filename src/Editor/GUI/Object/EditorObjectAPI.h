#pragma once
#include <Editor/GUI/Object/EditorObjectVisualizer.h>

namespace Portakal
{
	class ObjectObserverWindow;
	class PORTAKAL_API EditorObjectAPI
	{
	public:
		static void RegisterWindow(ObjectObserverWindow* pWindow);
		static void RemoveWindow(ObjectObserverWindow* pWindow);
		static void SignalNewObject(Class* pObject);
	private:
		static Array<ObjectObserverWindow*> sWindows;
	private:
		EditorObjectAPI() = delete;
		~EditorObjectAPI() = delete;
	};
}