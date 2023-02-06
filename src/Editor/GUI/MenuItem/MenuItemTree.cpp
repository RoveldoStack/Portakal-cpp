#include "MenuItemTree.h"
#include <Editor/GUI/MenuItem/GUIMenuItemBehaviour.h>

namespace Portakal
{
	MenuItemTree::MenuItemTree()
	{
		mName = "Root";
	}
	MenuItemTree::~MenuItemTree()
	{
		for (unsigned int i = 0; i < mSubTrees.GetCursor(); i++)
			delete mSubTrees[i];

		mSubTrees.Clear();
	}
	void MenuItemTree::InsertSourceText(const String& sourceText, const Type* pType)
	{
		Array<String> nodes = GetTreeNodes(sourceText);

		if (nodes.GetCursor() <= 0)
			return;

		for (unsigned int i = 0; i < mSubTrees.GetCursor(); i++)
		{
			MenuItemTree* pSubTree = mSubTrees[i];

			if (pSubTree->GetName() == nodes[0])
			{
				nodes.RemoveIndex(0);

				if (nodes.GetCursor() <= 0)
					return;

				pSubTree->InsertTreeNodes(nodes, pType);
				return;
			}
		}

		MenuItemTree* pNewTree = new MenuItemTree();
		mSubTrees.Add(pNewTree);

		pNewTree->SetName(nodes[0]);

		nodes.RemoveIndex(0);

		if (nodes.GetCursor() <= 0)
		{
			pNewTree->SetBehaviour(pType);
			return;
		}

		pNewTree->InsertTreeNodes(nodes, pType);
	}
	void MenuItemTree::Invoke()
	{
		mBehaviour->OnClick();
	}
	Array<String> MenuItemTree::GetTreeNodes(const String& sourceText) const noexcept
	{
		Array<String> nodes;
		String dummy;

		for (unsigned int i = 0; i < sourceText.GetCursor(); i++)
		{
			if (sourceText[i] == '/')
			{
				nodes.Add(dummy);
				dummy.Clear();
				continue;
			}
			dummy += sourceText[i];
		}

		nodes.Add(dummy);

		return nodes;
	}
	void MenuItemTree::InsertTreeNodes(Array<String> nodes, const Type* pType)
	{
		for (unsigned int i = 0; i < mSubTrees.GetCursor(); i++)
		{
			MenuItemTree* pTree = mSubTrees[i];

			if (pTree->GetName() == nodes[0])
			{
				nodes.RemoveIndex(0);

				if (nodes.GetCursor() <= 0)
					return;

				pTree->InsertTreeNodes(nodes, pType);
				return;
			}
		}

		MenuItemTree* pNewTree = new MenuItemTree();
		mSubTrees.Add(pNewTree);

		pNewTree->SetName(nodes[0]);

		nodes.RemoveIndex(0);

		if (nodes.GetCursor() <= 0)
		{
			pNewTree->SetBehaviour(pType);
			return;
		}

		pNewTree->InsertTreeNodes(nodes, pType);
	}
	void MenuItemTree::SetBehaviour(const Type* pType)
	{
		mBehaviour = (MenuItemBehaviour*)pType->CreateDefaultHeapObject();
	}
}