#include "GUIMainMenuItemModule.h"
#include <Editor/GUI/MenuItem/GUICustomMenuItem.h>
#include <Editor/GUI/MenuItem/GUIMenuItemBehaviour.h>
#include <Editor/GUI/MenuItem/MenuItemTemplates.h>
#include <Editor/GUI/MenuItem/MenuItemTree.h>
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
    void GUIMainMenuItemModule::OnInitialize()
    {
        LoadMainMenuItems();
    }
    void GUIMainMenuItemModule::OnFinalize()
    {

    }
    void GUIMainMenuItemModule::OnPreTick()
    {

    }
   
    void PaintMenuItemTree(MenuItemTree* pTree)
    {
        if (pTree->GetName() == "Root")
        {
            Array<MenuItemTree*> subTrees = pTree->GetSubTrees();
            for (unsigned int i = 0; i < subTrees.GetCursor(); i++)
                PaintMenuItemTree(subTrees[i]);
            return;
        }

        if (pTree->HasSubTrees())
        {
            if (ImGui::BeginMenu(*pTree->GetName()))
            {
                Array<MenuItemTree*> subTrees = pTree->GetSubTrees();
                for (unsigned int i = 0; i < subTrees.GetCursor(); i++)
                    PaintMenuItemTree(subTrees[i]);

                ImGui::EndMenu();
            }
        }
        else
        {
            if (ImGui::MenuItem(*pTree->GetName()))
            {
                pTree->Invoke();
            }
        }
    }
    void GUIMainMenuItemModule::OnTick()
    {
        /*
        * Render main menu bar items
        */
        if (ImGui::BeginMainMenuBar())
        {
            PaintMenuItemTree(_tree);
            ImGui::EndMainMenuBar();
        }
    }
    void GUIMainMenuItemModule::OnPostTick()
    {

    }
    void GUIMainMenuItemModule::PreValidate()
    {
        /*
        * Delete the existing tree
        */
        delete _tree;
    }
    void GUIMainMenuItemModule::PostValidate()
    {
        LoadMainMenuItems();
    }
    void GUIMainMenuItemModule::OnEvent(WindowEvent* pEvent)
    {

    }
    void GUIMainMenuItemModule::LoadMainMenuItems()
    {
        _tree = new MenuItemTree();

        Array<Type*> behaviours;
        const Array<Type*> types = Assembly::GetProcessAssembly()->GetTypes();
        for (unsigned int i = 0; i < types.GetCursor(); i++)
        {
            const Type* pType = types[i];

            const GUICustomMenuItem* pAttribute = pType->GetAttribute<GUICustomMenuItem>();

            if (pAttribute != nullptr)
            {
                _tree->InsertSourceText(pAttribute->GetLocation(), pType);
            }
        }
    }
}