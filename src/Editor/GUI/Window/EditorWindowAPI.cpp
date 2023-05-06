#include "EditorWindowAPI.h"
#include <Libs/ImGui/imgui.h>

namespace Portakal
{

	Array<EditorWindow*> EditorWindowAPI::GetWindows()
	{
		EditorWindowAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return {};

		return pAPI->mWindows;
	}
	EditorWindow* EditorWindowAPI::Create(Type* pType)
	{
		EditorWindowAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return nullptr;

		if (pType == nullptr)
			return nullptr;
		if (!pType->IsSubClassOf(typeof(EditorWindow)))
			return nullptr;

		EditorWindow* pWindow = (EditorWindow*)pType->CreateDefaultHeapObject();
		pWindow->_SetParentWindow(nullptr);
		pWindow->_SetPosition({ 0,0 });
		pWindow->_SetSize({ 0,0 });

		pWindow->OnInitialize();
		pWindow->OnShow();

		pAPI->mWindows.Add(pWindow);

		return pWindow;
	}
	EditorWindow* EditorWindowAPI::CreateFromSetting(const EditorWindowSetting& setting)
	{
		EditorWindowAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return nullptr;

		/*
		* Try find type
		*/
		Array<Type*> types = Assembly::GetProcessAssembly()->GetTypes();
		Type* pFoundType = nullptr;
		for (unsigned int i = 0; i < types.GetCursor(); i++)
		{
			Type* pType = types[i];
			if (pType->GetTypeName() == setting.Name)
			{
				if (pType->IsSubClassOf(typeof(EditorWindow)))
				{
					pFoundType = pType;
					break;
				}
			}
		}
		if (pFoundType == nullptr)
			return nullptr;

		/*
		* Create type
		*/
		EditorWindow* pWindow = (EditorWindow*)pFoundType->CreateDefaultHeapObject();
		pWindow->_SetParentWindow(nullptr);
		pWindow->_SetPosition({ 0,0 });
		pWindow->_SetSize({ 0,0 });
		pWindow->mID = setting.ID;
		pWindow->mDockState = setting.DockState;
		pWindow->OnInitialize();
		pWindow->OnShow();

		pAPI->mWindows.Add(pWindow);

		return pWindow;
	}
	void EditorWindowAPI::Paint()
	{
		EditorWindowAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		for (unsigned int i = 0; i < pAPI->mWindows.GetCursor(); i++)
		{
			EditorWindow* pWindow = pAPI->mWindows[i];

			bool bActive = true;
			const bool bFormerVisibleState = pWindow->IsVisible();
			bool bCurrentVisibleState = bFormerVisibleState;

			/*
			* Start rendering window
			*/
			bCurrentVisibleState = ImGui::Begin(*pWindow->GetType()->GetTypeName(),&bActive);

			/*
			* Invoke visibility change events
			*/
			if (bFormerVisibleState != bCurrentVisibleState) // visibility changed
			{
				if (bCurrentVisibleState)
					pWindow->OnShow();
				else
					pWindow->OnHide();
			}

			/*
			* Paint if visible
			*/
			if (bCurrentVisibleState)
				pWindow->OnPaint();

			/*
			* Check close request
			*/
			if (pWindow->HasCloseRequest() || !bActive)
			{
				DeleteWindow(pWindow);
				i--;
			}
			else // update states
			{
				const ImVec2 pos = ImGui::GetWindowPos();
				const ImVec2 size = ImGui::GetWindowSize();

				pWindow->_SetPosition({(unsigned int)pos.x,(unsigned int)pos.y});
				pWindow->_SetSize({(unsigned int)size.x,(unsigned int)size.y});
				pWindow->_SetVisibility(bCurrentVisibleState);
			}

			/*
			* Finalize rendering
			*/
			ImGui::End();
		}
	}
	void EditorWindowAPI::ClearAllWindows()
	{

	}
	void EditorWindowAPI::DeleteWindow(EditorWindow* pWindow)
	{
		EditorWindowAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		pWindow->OnHide();
		pWindow->OnFinalize();

		pAPI->mWindows.Remove(pWindow);

		delete pWindow;
	}

	EditorWindowAPI::EditorWindowAPI()
	{

	}

	EditorWindowAPI::~EditorWindowAPI()
	{

	}
}