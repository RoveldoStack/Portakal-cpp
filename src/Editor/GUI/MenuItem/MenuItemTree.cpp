#include "MenuItemTree.h"
#include <Editor/GUI/MenuItem/GUIMenuItemBehaviour.h>

namespace Portakal
{
	MenuItemTree::MenuItemTree()
	{
		_name = "Root";
	}
	MenuItemTree::~MenuItemTree()
	{
		for (unsigned int i = 0; i < _subTrees.GetCursor(); i++)
			delete _subTrees[i];

		_subTrees.Clear();
	}
	void MenuItemTree::InsertSourceText(const String& sourceText, const Type* pType)
	{
		Array<String> nodes = GetTreeNodes(sourceText);

		if (nodes.GetCursor() <= 0)
			return;

		for (unsigned int i = 0; i < _subTrees.GetCursor(); i++)
		{
			MenuItemTree* pSubTree = _subTrees[i];

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
		_subTrees.Add(pNewTree);

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
		_behaviour->OnClick();
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
		for (unsigned int i = 0; i < _subTrees.GetCursor(); i++)
		{
			MenuItemTree* pTree = _subTrees[i];

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
		_subTrees.Add(pNewTree);

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
		_behaviour = (MenuItemBehaviour*)pType->CreateDefaultHeapObject();
	}
}