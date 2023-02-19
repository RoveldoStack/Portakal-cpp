#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Reflection/Type.h>

namespace Portakal
{
	class MenuItemBehaviour;

	/// <summary>
	/// Represents a menu item tree hierarchy
	/// </summary>
	class PORTAKAL_API MenuItemTree
	{
	public:
		MenuItemTree();
		~MenuItemTree();

		/// <summary>
		/// retrurns the name of the tree
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetName() const noexcept { return mName; }

		/// <summary>
		/// Returns the sub trees
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<MenuItemTree*> GetSubTrees() const noexcept { return mSubTrees; }

		/// <summary>
		/// Returns whether it has any sub trees at all
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool HasSubTrees() const noexcept { return mSubTrees.GetCursor() > 0; }

		/// <summary>
		/// Sets the name
		/// </summary>
		/// <param name="name"></param>
		void SetName(const String& name) { mName = name; }

		/// <summary>
		/// Inserts a new text into the tree
		/// </summary>
		/// <param name="sourceText"></param>
		/// <param name="pType"></param>
		void InsertSourceText(const String& sourceText, const Type* pType);

		/// <summary>
		/// Invokes the tree method
		/// </summary>
		void Invoke();
	private:

		/// <summary>
		/// Returns the tree nodes
		/// </summary>
		/// <param name="sourceText"></param>
		/// <returns></returns>
		Array<String> GetTreeNodes(const String& sourceText) const noexcept;

		/// <summary>
		/// Inserts the tree nodes as text
		/// </summary>
		/// <param name="nodes"></param>
		/// <param name="pType"></param>
		void InsertTreeNodes(Array<String> nodes, const Type* pType);

		/// <summary>
		/// Sets the behaviour
		/// </summary>
		/// <param name="pType"></param>
		void SetBehaviour(const Type* pType);
	private:
		Array<MenuItemTree*> mSubTrees;
		MenuItemBehaviour* mBehaviour;
		String mName;
	};
}