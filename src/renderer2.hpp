#pragma once
#include "Vkbase.hpp"
#include "defs.tpp"
#include <array>
#include <vulkan/vulkan_core.h>



constexpr VkSemaphoreCreateInfo vkCreateCSemaphore{VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, nullptr};

constexpr VkFenceCreateInfo vkFenceCreateInfo{.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, .flags=VK_FENCE_CREATE_SIGNALED_BIT};
      
struct [[clang::trivial_abi]] renderer2
{

  [[gnu::hot, gnu::always_inline]] [[nodiscard]] inline auto drawFrame(std::initializer_list<VkCommandBuffer> commandBuffer) const noexcept -> bool;



  static constinit inline uint32_t               imgIndx;
  static constinit inline uint8_t               currentFrame;
template <typename type>

 

  static constexpr const uint32_t                TmUt = 1000000000;

 
} __attribute__((aligned(64)));
