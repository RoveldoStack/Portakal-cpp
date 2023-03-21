#include "EditorObjectAPI.h"
#include <Editor/GUI/Window/Templates/ObjectObserverWindow.h>

namespace Portakal
{
	Array<ObjectObserverWindow*> EditorObjectAPI::sWindows;

	void EditorObjectAPI::RegisterWindow(ObjectObserverWindow* pWindow)
	{
		sWindows.Add(pWindow);
	}
	void EditorObjectAPI::RemoveWindow(ObjectObserverWindow* pWindow)
	{
		sWindows.Remove(pWindow);
	}
	void EditorObjectAPI::SignalNewObject(Class* pObject)
	{
		for (unsigned int i = 0; i < sWindows.GetCursor(); i++)
			sWindows[i]->OnSignalNewObject(pObject);
	}
}