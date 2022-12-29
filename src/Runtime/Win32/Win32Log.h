#pragma once
#include <stdio.h>

#define LOG_IMPL(title,message,...) printf("[%s]:",title); printf(message,__VA_ARGS__); printf("\n");