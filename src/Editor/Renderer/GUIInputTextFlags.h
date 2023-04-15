#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API GUIInputTextFlags
	{
        None = 0,
        Decimal = 1 << 0,   // Allow 0123456789.+-*/
        HexaDecimal = 1 << 1,   // Allow 0123456789ABCDEFabcdef
        Uppercase = 1 << 2,   // Turn a..z into A..Z
        NoBlank= 1 << 3,   // Filter out spaces, tabs
        AutoSelectAll = 1 << 4,   // Select entire text when first taking mouse focus
        EnterReturnsTrue = 1 << 5,   // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider looking at the IsItemDeactivatedAfterEdit() function.
        AllowTab = 1 << 10,  // Pressing TAB input a '\t' character into the text field
        AllowCtrlEnterForNewLine = 1 << 11,  // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
        NoHorizontalScroll = 1 << 12,  // Disable following the cursor horizontally
        AlwaysOverwrite = 1 << 13,  // Overwrite mode
        ReadOnly = 1 << 14,  // Read-only mode
        Password = 1 << 15,  // Password mode, display all characters as '*'
        NoUndoRedo = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
        Scientific = 1 << 17,  // Allow 0123456789.+-*/eE (Scientific notation input)
	};

    FORCEINLINE static GUIInputTextFlags operator |(const GUIInputTextFlags a, const GUIInputTextFlags b)
    {
        return (GUIInputTextFlags)((unsigned int)a | (unsigned int)b);
    }

    FORCEINLINE static bool operator &(const GUIInputTextFlags a, const GUIInputTextFlags b)
    {
        return ((unsigned int)a & (unsigned int)b);
    }
}