#include "EditorObjectAPI.h"
#include <Editor/GUI/Window/Templates/ObjectObserverWindow.h>

namespace Portakal
{
	void EditorObjectAPI::RegisterWindow(ObjectObserverWindow* pWindow)
	{
		EditorObjectAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		pAPI->mWindows.Add(pWindow);
	}
	void EditorObjectAPI::RemoveWindow(ObjectObserverWindow* pWindow)
	{
		EditorObjectAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		pAPI->mWindows.Remove(pWindow);
	}
	void EditorObjectAPI::SignalNewObject(Class* pObject)
	{
		EditorObjectAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		for (unsigned int i = 0; i < pAPI->mWindows.GetCursor(); i++)
			pAPI->mWindows[i]->OnSignalNewObject(pObject);
	}
	EditorObjectAPI::EditorObjectAPI()
	{

	}
	EditorObjectAPI::~EditorObjectAPI()
	{

	}
}