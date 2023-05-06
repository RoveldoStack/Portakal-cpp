#include "EditorObjectModule.h"
#include <Editor/GUI/Object/EditorObjectAPI.h>

namespace Portakal
{
	void EditorObjectModule::OnInitialize()
	{
		mAPI = new EditorObjectAPI();
	}
	void EditorObjectModule::OnFinalize()
	{
		delete mAPI;
		mAPI = nullptr;
	}
	void EditorObjectModule::OnPreTick()
	{

	}
	void EditorObjectModule::OnTick()
	{

	}
	void EditorObjectModule::OnPostTick()
	{

	}
	void EditorObjectModule::PreValidate()
	{

	}
	void EditorObjectModule::PostValidate()
	{

	}
	void EditorObjectModule::OnEvent(WindowEvent* pEvent)
	{

	}
}