#pragma once


#ifdef WIN32
#ifdef NDEBUG
#define LIB_PATH "D:/Projects/utl/Release/"
#else
#define LIB_PATH "D:/Projects/utl/Debug/"
#endif // NDEBUG


#define LIB_NAME "utl.lib"

#define LIB LIB_PATH LIB_NAME

#pragma comment(lib, LIB)






#else
#error LIBDECL
#endif // WIN32

