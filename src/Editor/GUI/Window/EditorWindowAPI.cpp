#include "EditorWindowAPI.h"
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
	EditorWindowAPI* EditorWindowAPI::_api = nullptr;

	EditorWindow* EditorWindowAPI::CreateWindow(Type* pType)
	{
		if (_api == nullptr)
			return nullptr;

		return _api->CreateWindowInternal(pType);
	}
	EditorWindow* EditorWindowAPI::CreateFromSettings(const EditorWindowSettings& settings)
	{
		return nullptr;
	}
	EditorWindowAPI::EditorWindowAPI()
	{
		_api = this;
	}
	EditorWindowAPI::~EditorWindowAPI()
	{
		_api = nullptr;
	}
	EditorWindow* EditorWindowAPI::CreateWindowInternal(Type* pTargetType)
	{
		if (!pTargetType->IsSubClassOf(typeof(EditorWindow)))
			return nullptr;

		EditorWindow* pWindow = (EditorWindow*)pTargetType->CreateDefaultHeapObject();
		if (pWindow == nullptr)
			return nullptr;

		/*
		* Set properties
		*/
		pWindow->OnInitialize();
		pWindow->OnShow();

		_windows.Add(pWindow);

		return pWindow;
	}
	void EditorWindowAPI::DeleteWindow(EditorWindow* pWindow)
	{
		if (pWindow == nullptr)
			return;

		pWindow->OnHide();
		pWindow->OnFinalize();

		_windows.Remove(pWindow);

		delete pWindow;
	}
	void EditorWindowAPI::PreValidate()
	{

	}
	void EditorWindowAPI::PostValidate()
	{

	}
	void EditorWindowAPI::Paint()
	{
		for (unsigned int i = 0; i < _windows.GetCursor(); i++)
		{
			EditorWindow* pWindow = _windows[i];

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
}