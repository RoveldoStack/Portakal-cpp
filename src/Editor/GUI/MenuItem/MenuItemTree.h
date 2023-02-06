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

		FORCEINLINE String GetName() const noexcept { return mName; }
		FORCEINLINE Array<MenuItemTree*> GetSubTrees() const noexcept { return mSubTrees; }
		FORCEINLINE bool HasSubTrees() const noexcept { return mSubTrees.GetCursor() > 0; }

		void SetName(const String& name) { mName = name; }
		void InsertSourceText(const String& sourceText, const Type* pType);
		void Invoke();
	private:
		Array<String> GetTreeNodes(const String& sourceText) const noexcept;
		void InsertTreeNodes(Array<String> nodes, const Type* pType);
		void SetBehaviour(const Type* pType);
	private:
		Array<MenuItemTree*> mSubTrees;
		MenuItemBehaviour* mBehaviour;
		String mName;
	};
}