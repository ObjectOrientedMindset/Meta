#pragma once

#ifdef MT_PLATFORM_WINDOWS
	#ifdef MT_BUILD_DLL
		#define META_API __declspec(dllexport)
	#else
		#define META_API __declspec(dllimport)
	#endif
#else
	#error Meta only support Windows!
#endif	





