#pragma once
#include "defs.tpp"
#include "Win.hpp"
#include <cstdint>
#include <cstdio>
//#define VK_NO_PROTOTYPES

struct DiscreteQueue 
{

  DiscreteQueue(const DiscreteQueue &) = default;
  DiscreteQueue(DiscreteQueue &&) = default;
  auto operator=(const DiscreteQueue &) -> DiscreteQueue & = default;
  auto operator=(DiscreteQueue &&) -> DiscreteQueue & = default;
  constexpr DiscreteQueue(VkQueue queue, uint32_t queuefamilyVarient) noexcept
      : queue(queue), queuefamilyVarient(queuefamilyVarient) {}

  VkQueue queue;
  uint32_t queuefamilyVarient;
  // uint32_t prio=1;
  // uint32_t capabilities=0;
} __attribute__((aligned(16)));


struct GPUDevice
{
  VkDevice device;
  DiscreteQueue computeQueue;
  DiscreteQueue graphicsQueue;
  VkInstance instance;
  VkPhysicalDevice physDevice;
   template<typename type>
    [[nodiscard]] constexpr  auto doPointerAlloc5(auto* __restrict__ strct, auto pHndle) const noexcept -> type
    {
        type pHndl; 
        chkTst(pHndle(device, strct, nullptr, &pHndl));
      
        return pHndl;
    };
    template<typename type>
    constexpr auto doPointerAllocX(auto* strct) const -> type
    {
        type pHndl; 
        vkCreateGraphicsPipelines(device, nullptr, 1, strct, nullptr, &pHndl);
        return pHndl;
    }
    template<typename type>
    constexpr auto doPointerAllocX2(auto* strct) const -> type
    {
        type pHndl; 
        vkCreateShaderModule(device, strct, nullptr, &pHndl);
        return pHndl;
    }
    
    template <typename type>
    constexpr auto doSet( auto &s, auto f) -> std::array<type, Frames>
    {
      
      std::array<type, Frames> aa{};

      for(type  &i: aa)
      {
        i=doPointerAlloc5<type>( &s, f);
      }
      return aa;
    }
};

constexpr void chkTst(int buh = 0) noexcept
{
  if constexpr(checks)
  {
      switch (buh) 
      {
        case 1:  printf("VK_NOT_READY\n"); break;
        case 2: printf("VK_TIMEOUT\n"); break;
        case 3: printf("VK_EVENT_SET\n"); break;
        case 4: printf("VK_EVENT_RESET\n"); break;
        case 5: printf("VK_INCOMPLETE\n"); break;
        case -1: printf("VK_ERROR_OUT_OF_HOST_MEMORY\n"); break;
        case -2: printf("VK_ERROR_OUT_OF_DEVICE_MEMORY\n"); break;
        case -3: printf("VK_ERROR_INITIALIZATION_FAILED\n"); break;
        case -4: printf("VK_ERROR_DEVICE_LOST\n"); break;
        case -5: printf("VK_ERROR_MEMORY_MAP_FAILED\n"); break;
        case -6: printf("VK_ERROR_LAYER_NOT_PRESENT\n"); break;
        case -7: printf("VK_ERROR_EXTENSION_NOT_PRESENT\n"); break;
        case -8: printf("VK_ERROR_FEATURE_NOT_PRESENT\n"); break;
        case -9: printf("VK_ERROR_INCOMPATIBLE_DRIVER\n"); break;
        case -10: printf("VK_ERROR_TOO_MANY_OBJECTS\n"); break;
        case -11: printf("VK_ERROR_FORMAT_NOT_SUPPORTED\n"); break;
        case -12: printf("VK_ERROR_FRAGMENTED_POOL\n"); break;
        case -13: printf("VK_ERROR_UNKNOWN\n"); break;
        case -1000069000: printf("VK_ERROR_OUT_OF_POOL_MEMORY = \n"); break;
        case -1000072003: printf("VK_ERROR_INVALID_EXTERNAL_HANDLE = \n"); break;
        case -1000161000: printf("VK_ERROR_FRAGMENTATION = \n"); break;
        case -1000257000: printf("VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS = \n"); break;
        case 1000297000: printf("VK_PIPELINE_COMPILE_REQUIRED = \n"); break;
        case -1000000000: printf("VK_ERROR_SURFACE_LOST_KHR = \n"); break;
        case -1000000001: printf("VK_ERROR_NATIVE_WINDOW_IN_USE_KHR = \n"); break;
        case 1000001003: printf("VK_SUBOPTIMAL_KHR = \n"); break;
        case -1000001004: printf("VK_ERROR_OUT_OF_DATE_KHR = \n"); break;
        case -1000003001: printf("VK_ERROR_INCOMPATIBLE_DISPLAY_KHR = \n"); break;
        case -1000011001: printf("VK_ERROR_VALIDATION_FAILED_EXT = \n"); break;
        case -1000012000: printf("VK_ERROR_INVALID_SHADER_NV = \n"); break;
        case -1000023000: printf("VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR = \n"); break;
        case -1000023001: printf("VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR = \n"); break;
        case -1000023002: printf("VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR = \n"); break;
        case -1000023003: printf("VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR = \n"); break;
        case -1000023004: printf("VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR = \n"); break;
        case -1000023005: printf("VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR = \n"); break;
        case -1000158000: printf("VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT = \n"); break;
        case -1000174001: printf("VK_ERROR_NOT_PERMITTED_KHR = \n"); break;
        case -1000255000: printf("VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT = \n"); break;
        case 1000268000: printf("VK_THREAD_IDLE_KHR = \n"); break;
        case 1000268001: printf("VK_THREAD_DONE_KHR = \n"); break;
        case 1000268002: printf("VK_OPERATION_DEFERRED_KHR = \n"); break;
        case 1000268003: printf("VK_OPERATION_NOT_DEFERRED_KHR = \n"); break;
        case -1000338000: printf("VK_ERROR_COMPRESSION_EXHAUSTED_EXT = \n"); break;
        default: [[likely]] return;
        // case VK_SUCCESS: { return;}
      }
      [[unlikely]]exit(1);
  }
};

[[nodiscard, gnu::const]] auto getVer()  noexcept -> uint32_t;
[[nodiscard, gnu::const]] auto createDevice() -> GPUDevice;

const uint32_t vkVersion = getVer();