#include "PlatformDialog.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Dialog.h>
typedef Portakal::Win32Dialog PlatformAbstraction;
#endif

namespace Portakal
{
    void PlatformDialog::CreateOpenFileDialog(const String& filter)
    {
        PlatformAbstraction::CreateOpenFileDialog(filter);
    }
    String PlatformDialog::CreateOpenFolderDialog()
    {
        return PlatformAbstraction::CreateOpenFolderDialog();
    }
}