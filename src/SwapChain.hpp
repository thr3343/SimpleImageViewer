#pragma once
#include "defs.tpp"
#include "TMp.hpp"
#include "MemSys2.hpp"
#include <array>
#include <cstdint>




struct SwapchainCapabilities {
    uint8_t                          curImageCount;
    VkFormat                         format;
    VkExtent2D                       currentExtent;
    VkImageUsageFlags                currentUsage;
};

struct SwapChain : Tmp
{
   
    SwapchainCapabilities extent;
    VkSwapchainKHR swapchain;
    VkPresentModeKHR presentMode;
    std::array<VkImage, Frames> swapChainImages;

     explicit SwapChain(Tmp swap, uint32_t ActiveQueueFamily)
         :
           extent(handleSwapChainCapabilities()),
           swapchain(createSwapChain(ActiveQueueFamily)),
           swapChainImages(getSwapChainImages(Frames, ActiveQueueFamily)),
           SwapChain::Tmp(swap){}; // TODO(Vcmp): use Move Construction to avoid duplciating the handles: (Minor Mem Leak)

     auto handleSwapChainCapabilities() -> SwapchainCapabilities;
     auto createSwapChain(uint32_t) -> VkSwapchainKHR;
     auto createRenderPass(VkImageLayout initial=VK_IMAGE_LAYOUT_UNDEFINED, bool load=false) -> VkRenderPass;
     auto createFramebuffers() -> VkFramebuffer;

     auto setupImageFormats() -> VkSurfaceFormatKHR;

     [[nodiscard]] auto getSwapChainImages(uint32_t, uint32_t)
         -> std::array<VkImage, Frames>;
     [[nodiscard]] auto createImageViews(std::array<VkImage, Frames> image)
         -> std::array<VkImageView, Frames>;

     [[nodiscard]] auto createImageView(vmaImage image) const -> VkImageView;

     [[gnu::cold]] ~SwapChain() { vkDestroySwapchainKHR(tmpDevice_, swapchain, nullptr); }
};