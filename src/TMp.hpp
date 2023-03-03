#pragma once
#define VK_NO_STDDEF_H
#include "defs.tpp"
#include <cstdint>
#include <fmt/core.h>
#include <cstdlib>
#include <vulkan/vk_platform.h>




using callArg = int (VKAPI_PTR*)(VkDevice device, const void* pCreateInfo, const void* pAllocator, void* pCommandPool);
using PFN_vkVoidFunction = void (VKAPI_PTR*)(void);

struct [[gnu::aligned(32)]] Tmp
{
  [[no_unique_address]] VkInstance tmpInst_;
  [[no_unique_address]] VkDevice tmpDevice_;
  [[no_unique_address]] VkPhysicalDevice tmpPhysDevice_;
  [[no_unique_address]] VkSurfaceKHR tmpSurface_;
//  PFN_vkCreateCommandPool a_;
    template<typename type>
    [[nodiscard]] constexpr  auto doPointerAlloc5(auto* __restrict__ strct, auto pHndle) const noexcept -> type
    {
        type pHndl; 
        reinterpret_cast<callArg>(pHndle)(tmpDevice_, strct, nullptr, &pHndl);
      
        return pHndl;
    };
};

constexpr void chkTst(int buh = 0) noexcept
{
  if constexpr(checks)
  {
      switch (buh) 
      {
        case 1:  fmt::print("VK_NOT_READY\n"); break;
        case 2: fmt::print("VK_TIMEOUT\n"); break;
        case 3: fmt::print("VK_EVENT_SET\n"); break;
        case 4: fmt::print("VK_EVENT_RESET\n"); break;
        case 5: fmt::print("VK_INCOMPLETE\n"); break;
        case -1: fmt::print("VK_ERROR_OUT_OF_HOST_MEMORY\n"); break;
        case -2: fmt::print("VK_ERROR_OUT_OF_DEVICE_MEMORY\n"); break;
        case -3: fmt::print("VK_ERROR_INITIALIZATION_FAILED\n"); break;
        case -4: fmt::print("VK_ERROR_DEVICE_LOST\n"); break;
        case -5: fmt::print("VK_ERROR_MEMORY_MAP_FAILED\n"); break;
        case -6: fmt::print("VK_ERROR_LAYER_NOT_PRESENT\n"); break;
        case -7: fmt::print("VK_ERROR_EXTENSION_NOT_PRESENT\n"); break;
        case -8: fmt::print("VK_ERROR_FEATURE_NOT_PRESENT\n"); break;
        case -9: fmt::print("VK_ERROR_INCOMPATIBLE_DRIVER\n"); break;
        case -10: fmt::print("VK_ERROR_TOO_MANY_OBJECTS\n"); break;
        case -11: fmt::print("VK_ERROR_FORMAT_NOT_SUPPORTED\n"); break;
        case -12: fmt::print("VK_ERROR_FRAGMENTED_POOL\n"); break;
        case -13: fmt::print("VK_ERROR_UNKNOWN\n"); break;
        case -1000069000: fmt::print("VK_ERROR_OUT_OF_POOL_MEMORY = \n"); break;
        case -1000072003: fmt::print("VK_ERROR_INVALID_EXTERNAL_HANDLE = \n"); break;
        case -1000161000: fmt::print("VK_ERROR_FRAGMENTATION = \n"); break;
        case -1000257000: fmt::print("VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS = \n"); break;
        case 1000297000: fmt::print("VK_PIPELINE_COMPILE_REQUIRED = \n"); break;
        case -1000000000: fmt::print("VK_ERROR_SURFACE_LOST_KHR = \n"); break;
        case -1000000001: fmt::print("VK_ERROR_NATIVE_WINDOW_IN_USE_KHR = \n"); break;
        case 1000001003: fmt::print("VK_SUBOPTIMAL_KHR = \n"); break;
        case -1000001004: fmt::print("VK_ERROR_OUT_OF_DATE_KHR = \n"); break;
        case -1000003001: fmt::print("VK_ERROR_INCOMPATIBLE_DISPLAY_KHR = \n"); break;
        case -1000011001: fmt::print("VK_ERROR_VALIDATION_FAILED_EXT = \n"); break;
        case -1000012000: fmt::print("VK_ERROR_INVALID_SHADER_NV = \n"); break;
        case -1000023000: fmt::print("VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR = \n"); break;
        case -1000023001: fmt::print("VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR = \n"); break;
        case -1000023002: fmt::print("VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR = \n"); break;
        case -1000023003: fmt::print("VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR = \n"); break;
        case -1000023004: fmt::print("VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR = \n"); break;
        case -1000023005: fmt::print("VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR = \n"); break;
        case -1000158000: fmt::print("VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT = \n"); break;
        case -1000174001: fmt::print("VK_ERROR_NOT_PERMITTED_KHR = \n"); break;
        case -1000255000: fmt::print("VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT = \n"); break;
        case 1000268000: fmt::print("VK_THREAD_IDLE_KHR = \n"); break;
        case 1000268001: fmt::print("VK_THREAD_DONE_KHR = \n"); break;
        case 1000268002: fmt::print("VK_OPERATION_DEFERRED_KHR = \n"); break;
        case 1000268003: fmt::print("VK_OPERATION_NOT_DEFERRED_KHR = \n"); break;
        case -1000338000: fmt::print("VK_ERROR_COMPRESSION_EXHAUSTED_EXT = \n"); break;
        default: [[likely]] return;
        // case VK_SUCCESS: { return;}
      }
      [[unlikely]]exit(1);
  }


}