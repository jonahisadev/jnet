#pragma once

#if defined(__APPLE__) || defined(__linux__)
#define OS_UNIX
#elif defined(_WIN32)
#define OS_WIN
#endif