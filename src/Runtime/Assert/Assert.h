#pragma once
#include <Runtime/Log/Log.h>
#include <Runtime/Platform/PlatformMessage.h>

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Assert.h>
#endif

#ifdef PORTAKAL_SAFE
#define ASSERT(expression,title,message,...) if(!(expression)) {Portakal::PlatformMessage::ShowMessageBox(title,message,Portakal::PlatformMessageBoxFlags::IconStop); LOG(title,message,__VA_ARGS__); ASSERT_IMPL(expression)} 
#else
#define ASSERT(expression,title,message,...)
#endif
