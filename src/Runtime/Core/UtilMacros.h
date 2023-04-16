#pragma once

#define GENERATE_FLAG_OPERATORS(name,type)\
FORCEINLINE static name operator |(const name a, const name b)\
{\
    return (name)((type)a | (type)b);\
}\
FORCEINLINE static bool operator &(const name a, const name b)\
{\
    return ((type)a & (type)b);\
}