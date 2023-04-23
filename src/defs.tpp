#pragma once
#define VULKAN_H_ 1

#define _WINNT_
#define _WINDOWS_

#include <cstdint>
#define _LIBCPP_CSTDINT
#define _LIBCPP_STDINT_H
#define _LIBCPP___ASSERT
#define _LIBCPP___CONFIG

#define VEC_CALL(vec) [[nodiscard, gnu::const, gnu::nodebug, gnu::aligned(32), clang::min_vector_width(sizeof(vec))]]  

constexpr uint8_t Frames = 8u;
constexpr uint16_t width = 1920;
constexpr uint16_t height = 1080;
constexpr bool checks =false;

//Vulkan Defs

using VkInstance = struct VkInstance_T*;
using VkQueue = struct VkQueue_T*;
using VkSurfaceKHR = struct VkSurfaceKHR_T*;
using VkPhysicalDevice = struct VkPhysicalDevice_T*;
using VkDevice = struct VkDevice_T*;
using VkInstance = struct VkInstance_T*;
using VkSwapchainKHR = struct VkSwapchainKHR_T*;
using VkCommandPool = struct VkCommandPool_T*;
using VkCommandBuffer = struct VkCommandBuffer_T*;
using VkBuffer = struct VkBuffer_T*;
using VkImage = struct VkImage_T*;
using VkSemaphore = struct VkSemaphore_T*;
using VkFence = struct VkFence_T*;
using VkPipelineLayout = struct VkPipelineLayout_T*;
using VkPipeline = struct VkPipeline_T*;
using VkPipelineCache = struct VkPipelineCache_T*;
using VkDescriptorSet = struct VkDescriptorSet_T*;
using VkDescriptorPool = struct VkDescriptorPool_T*;
using VkDescriptorSetLayout = struct VkDescriptorSetLayout_T*;
//Can't forward declare Enums or Structs (Without definition conflicts), So will need to use Vulkan header includes in headers which will inhibit compilation time

//VMA Defs

using VmaAllocator = struct VmaAllocator_T*;
using VmaAllocation = struct VmaAllocation_T*;

//win32 defs

    using DWORD = unsigned long;
    using QWORD = uint64_t;
		using  LPCWSTR = const wchar_t*;
		using  HANDLE = void* ;
		using  HINSTANCE = struct HINSTANCE__*;
		using  HWND = struct HWND__*;
		using  HMONITOR = struct HMONITOR__*;
		using SECURITY_ATTRIBUTES = struct _SECURITY_ATTRIBUTES ;

    using WPARAM = unsigned long long;
    using LPARAM = long long;
    using LRESULT = long long;
    using UINT = unsigned int;
    
    
    using WORD = unsigned short;


// .Misc
using GLFWwindow = struct GLFWwindow;