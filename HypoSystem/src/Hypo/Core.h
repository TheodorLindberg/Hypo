#pragma once



#ifndef HYPO_STATIC
#define HYPO_BUILD_DLL
#endif


#define HYPO_PLATFORM_WINDOWS


#ifdef HYPO_BUILD_DLL
	#define HYPO_API_EXPORTS __declspec(dllexport)
	#define HYPO_API_IMPORTS __declspec(dllimport)
#elif HYPO_STATIC
	#define HYPO_API_EXPORTS
	#define HYPO_API_IMPORTS
#else
	#error Build option not set
#endif



#ifdef HYPO_PLATFORM_WINDOWS
#else
	#error Hypo only supports Windows!
#endif
#define HYPO_NDEBUG

#ifdef HYPO_NDEBUG
	#define HYPO_ENABLE_ASSERTS
#endif

#ifdef HYPO_ENABLE_ASSERTS
	#define HYPO_ASSERT(x, ...) { if(!(x)) { HYPO_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HYPO_CORE_ASSERT(x, ...) { if(!(x)) { HYPO_CORE_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HYPO_CORE_ASSERT(x, ...) 
	#define HYPO_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)
#define GET_BIT(value, bit) (value & BIT(bit))
#define IS_SET(value, bit) ( GET_BIT(value,bit) == 1 )

#define HYPO_ENABLED 1
#define HYPO_DISABLED 0

#define HYPO_ENABLE 1
#define HYPO_DISABLE 0

#define HYPO_TRUE 1
#define HYPO_FALSE 0

//Should propably be set by user 
#ifdef HYPO_NDEBUG
	#define HYPO_ENGINE_RUNTIME_CHECK HYPO_ENABLE
#else
	#define HYPO_ENGINE_RUNTIME_CHECK HYPO_DISABLE
#endif

#if HYPO_ENGINE_RUNTIME_CHECK == HYPO_ENABLED
	#define HYPO_RUNTIME_CHECK_UNIFORMS HYPO_ENABLE
	#define HYPO_RUNTIME_CHECK_ATTRIBUTES HYPO_ENABLE
	#define HYPO_RUNTIME_CHECK_VERTEX_ARRAY_ATTRIBUTES HYPO_ENABLE
#else
	#define HYPO_RUNTIME_CHECK_UNIFORMS HYPO_DISABLE
	#define HYPO_RUNTIME_CHECK_ATTRIBUTES HYPO_DISABLE
	#define HYPO_RUNTIME_CHECK_VERTEX_ARRAY_ATTRIBUTES HYPO_DISABLE
#endif

