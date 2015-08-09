#pragma once

#ifndef _LIB_REACTOR_API
#define _LIB_REACTOR_API
#endif

#ifdef _LIB_REACTOR_API
#define LIB_REACTOR_API __declspec(dllexport)
#else
#define LIB_REACTOR_API __declspec(dllimport)
#endif

#pragma warning( disable: 4251 )
