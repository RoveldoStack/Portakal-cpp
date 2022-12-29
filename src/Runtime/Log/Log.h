#pragma once

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Log.h>
#endif

#define LOG(title,message,...) LOG_IMPL(title,message,__VA_ARGS__)