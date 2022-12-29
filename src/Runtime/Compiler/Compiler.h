#pragma once

#ifdef PORTAKAL_COMPILER_MSVC
#define FORCEINLINE_IMPL __forceinline
#elif PORTAKAL_COMPILER_CLANG
#define PORTAKAL_API
#define FORCEINLINE_IMPL
#elif PORTAKAL_COMPILER_GCC
#define PORTAKAL_API
#define FORCEINLINE_IMPL
#elif PORTAKAL_COMPILER_INVALID
#error("Invalid Portakal compiler, Portakal does not support the present compiler or there are none targeted!")
#endif