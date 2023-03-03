#pragma once
#include "TMp.hpp"
#include <array>
#include <vulkan/vulkan_core.h>



constexpr VkSemaphoreCreateInfo vkCreateCSemaphore{VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};

constexpr VkFenceCreateInfo vkFenceCreateInfo{.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, .flags=VK_FENCE_CREATE_SIGNALED_BIT};
      
struct [[clang::trivial_abi]] renderer2 : Tmp
{


  [[gnu::hot, gnu::always_inline]] inline void drawFrame() const noexcept;


   explicit renderer2(Tmp tmp): Tmp{tmp}{};

  static constinit inline uint32_t               imgIndx;
  static constinit inline uint8_t               currentFrame;
  
  template <typename type> constexpr auto doSet( auto &s, auto f) -> std::array<type, Frames>;
  


  std::array<VkSemaphore, Frames> AvailableSemaphore = doSet<VkSemaphore>(vkCreateCSemaphore, vkCreateSemaphore);
  std::array<VkSemaphore, Frames> PresentSemaphore = doSet<VkSemaphore>(vkCreateCSemaphore, vkCreateSemaphore);
  std::array<VkSemaphore, Frames> FinishedSemaphore = doSet<VkSemaphore>(vkCreateCSemaphore, vkCreateSemaphore);
  std::array<VkFence, Frames> fence = doSet<VkFence>(vkFenceCreateInfo, vkCreateFence);
  std::array<VkFence, Frames> fence2 = doSet<VkFence>(vkFenceCreateInfo, vkCreateFence);

  static constexpr const uint32_t                TmUt = 1000000000;

 
} __attribute__((aligned(128)));

template <typename type>
constexpr auto renderer2::doSet( auto &s, auto f) -> std::array<type, Frames>
{
   
   std::array<type, Frames> aa;

   for(type & i: aa)
   {
     i=doPointerAlloc5<type>( &s, f);
   }
  return aa;
}
