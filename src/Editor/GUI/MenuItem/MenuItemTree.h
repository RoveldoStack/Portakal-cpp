#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Reflection/Type.h>

namespace Portakal
{
	class MenuItemBehaviour;
	class PORTAKAL_API MenuItemTree
	{
	public:
		MenuItemTree();
		~MenuItemTree();

		FORCEINLINE String GetName() const noexcept { return _name; }
		FORCEINLINE Array<MenuItemTree*> GetSubTrees() const noexcept { return _subTrees; }
		FORCEINLINE bool HasSubTrees() const noexcept { return _subTrees.GetCursor() > 0; }

		void SetName(const String& name) { _name = name; }
		void InsertSourceText(const String& sourceText, const Type* pType);
		void Invoke();
	private:
		Array<String> GetTreeNodes(const String& sourceText) const noexcept;
		void InsertTreeNodes(Array<String> nodes, const Type* pType);
		void SetBehaviour(const Type* pType);
	private:
		Array<MenuItemTree*> _subTrees;
		MenuItemBehaviour* _behaviour;
		String _name;
	};
}