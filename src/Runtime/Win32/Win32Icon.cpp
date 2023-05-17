#include "Win32Icon.h"
#include <Windows.h>
#include <Runtime/Graphics/Texture/TextureLoader.h>
#include <Runtime/Window/WindowAPI.h>
#include <Runtime/Win32/Win32Window.h>

namespace Portakal
{
	void Win32Icon::LoadIconFromPath(const String& path,Window* pTargetWindow)
	{
		/*
		* Load and validate
		*/
		TextureLoadResult result = {};
		if (!TextureLoader::LoadTextureFromDisk(path, result))
		{
			LOG("Win32Icon", "Failed to load icon texture");
			return;
		}

		if (result.pData == nullptr)
			return;

		/*
		* Swap bytes for RGB->BGR
		*/
		const unsigned int textureSize = result.Width * result.Height * 4; // Always 4
		for (unsigned int i = 0; i < textureSize; i += 4)
		{
			const Byte r = result.pData[i];
			const Byte b = result.pData[i+2];

			result.pData[i] = b;
			result.pData[i + 2] = r;
		}
		HICON icon = NULL;

		/*
		* Get win32 window handle
		*/
		HWND windowHandle = ((Win32Window*)pTargetWindow)->GetWin32WindowHandle();
		HDC windowDeviceContext = ((Win32Window*)pTargetWindow)->GetWin32WindowDeviceContext();

		/*
		* Create icon out of the texture
		*/
		ICONINFO iconInfo = {
			TRUE, // fIcon, set to true if this is an icon, set to false if this is a cursor
			NULL, // xHotspot, set to null for icons
			NULL, // yHotspot, set to null for icons
			NULL, // Monochrome bitmap mask, set to null initially
			NULL  // Color bitmap mask, set to null initially
		};

		HBITMAP bitmap = CreateBitmap(result.Width, result.Height, 1, 32, result.pData);
		iconInfo.hbmColor = bitmap;
		if (bitmap)
		{
			iconInfo.hbmMask = CreateCompatibleBitmap(windowDeviceContext, result.Width, result.Height);
			if (iconInfo.hbmMask)
			{
				icon = CreateIconIndirect(&iconInfo);
				if (icon == NULL)
				{
					LOG("Win32Icon", "Failed to create icon indirect");
					return;
				}
				DeleteObject(iconInfo.hbmMask);
			}
			DeleteObject(iconInfo.hbmColor);
		}

		if (icon == NULL)
		{
			LOG("Win32Icon", "Failed to create icon");
			return;
		}
		/*
		* Send message
		*/
		SendMessage(windowHandle, WM_SETICON, ICON_SMALL, (LPARAM)icon);
		SendMessage(windowHandle, WM_SETICON, ICON_SMALL2, (LPARAM)icon);
		SendMessage(windowHandle, WM_SETICON, ICON_BIG, (LPARAM)icon);


	}
}