#pragma once

#ifdef PORTAKAL_COMPILER_MSVC
#define FORCEINLINE __forceinline
#elif PORTAKAL_COMPILER_CLANG
#define FORCEINLINE_IMPL
#elif PORTAKAL_COMPILER_GCC
#define FORCEINLINE_IMPL
#elif PORTAKAL_COMPILER_INVALID
#error("Invalid Portakal compiler, Portakal does not support the present compiler or there are none targeted!")
#endif