#pragma once

#ifdef PORTAKAL_OS_WINDOWS
#define PORTAKAL_API_IMPL __declspec(dllexport)
#else
#define PORTAKAL_API_IMPL
#endif
