#pragma once

#ifdef UTIL_EXPORTS
#define UTIL_API __declspec( dllexport ) 
#else
#define UTIL_API __declspec( dllimport )
#endif
