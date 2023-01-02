#include "Win32Dialog.h"
#include <Windows.h>
#include <tchar.h>
#include <ShlObj_core.h>
#include <comdef.h>

namespace Portakal
{
    void Win32Dialog::CreateOpenFileDialog(const String& filter)
    {
        if (SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
        {
            IFileOpenDialog* pFileDialog = nullptr;
            IShellItemFilter* pFilter = nullptr;

            if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pFileDialog))))
            {
                if (SUCCEEDED(pFileDialog->Show(NULL)))
                {
                    IShellItem* pItem = nullptr;
                    if (SUCCEEDED(pFileDialog->GetResult(&pItem)))
                    {
                        PWSTR pszFilePath;
                        if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath)))
                        {
                            MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                            CoTaskMemFree(pszFilePath);
                        }
                        pItem->Release();
                    }
                }
            }

            pFileDialog->Release();
        }
        CoUninitialize();
    }
    String Win32Dialog::CreateOpenFolderDialog()
    {
        String output;

        /*
        * Initialize com lib
        */
        if (SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
        {
            IFileOpenDialog* pFileDialog = nullptr;
            IShellItemFilter* pFilter = nullptr;

            /*
            * Create a file open dialog interface
            */
            if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pFileDialog))))
            {
                /*
                * Set folder options
                */
                pFileDialog->SetOptions(FOS_PICKFOLDERS);

                /*
                * Show the interface
                */
                if (SUCCEEDED(pFileDialog->Show(NULL)))
                {
                    /*
                    * Wait and get the result
                    */
                    IShellItem* pItem = nullptr;
                    if (SUCCEEDED(pFileDialog->GetResult(&pItem)))
                    {
                        /*
                        * Collect the return file sys path
                        */
                        PWSTR pszFilePath;
                        if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath)))
                        {
                            _bstr_t b(pszFilePath);
                            output = b.operator const char* ();

                            CoTaskMemFree(pszFilePath);
                        }
                        pItem->Release();
                    }
                }
            }

            pFileDialog->Release();
        }

        /*
        * Finalize com lib
        */
        CoUninitialize();

        return output;
    }
}