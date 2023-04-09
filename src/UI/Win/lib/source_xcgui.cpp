//
// Created by HuiYi on 2023/4/9.
//
#include "source_xcgui.h"

#if defined(__LP64__) || defined(_WIN64)
// 64-bit code
#include "x64/xcgui_x64.cpp"
#else
// 32-bit code
#include "x86/xcgui_x86.cpp"
#endif
