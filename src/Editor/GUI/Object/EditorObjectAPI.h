#pragma once
#include <Editor/GUI/Object/EditorObjectVisualizer.h>
#include <Runtime/Object/API.h>

namespace Portakal
{
	class ObjectObserverWindow;
	class PORTAKAL_API EditorObjectAPI : public API<EditorObjectAPI>
	{
	public:
		static void RegisterWindow(ObjectObserverWindow* pWindow);
		static void RemoveWindow(ObjectObserverWindow* pWindow);
		static void SignalNewObject(Class* pObject);
	private:
		EditorObjectAPI();
		virtual ~EditorObjectAPI() override;
	private:
		Array<ObjectObserverWindow*> mWindows;
	};
}