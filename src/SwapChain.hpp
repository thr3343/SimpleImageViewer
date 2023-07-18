#pragma once
#include "defs.tpp"
#include "MemSys2.hpp"
#include <array>
#include <cstdint>




struct SwapchainCapabilities {
    uint8_t                          curImageCount;
    VkFormat                         format;
    VkExtent2D                       currentExtent;
    VkImageUsageFlags                currentUsage;
};

struct SwapChain : GPUDevice,  Win
{
   
    VkSurfaceKHR surface;
    SwapchainCapabilities extent;
    VkSwapchainKHR swapchain;
    std::array<VkImage, Frames> swapChainImages;
    VkPresentModeKHR presentMode=VK_PRESENT_MODE_FIFO_KHR;

     explicit SwapChain(GPUDevice swap, uint32_t ActiveQueueFamily)
         :
           surface(createSurface()),
           extent(handleSwapChainCapabilities()),
           swapchain(createSwapChain(ActiveQueueFamily)),
           swapChainImages(getSwapChainImages(Frames, ActiveQueueFamily)),
           SwapChain::GPUDevice(swap){}; // TODO(Vcmp): use Move Construction to avoid duplciating the handles: (Minor Mem Leak)
     [[nodiscard]] auto createSurface() -> VkSurfaceKHR;
     auto handleSwapChainCapabilities() -> SwapchainCapabilities;
     auto createSwapChain(uint32_t) -> VkSwapchainKHR;
     [[gnu::unused]] auto createRenderPass(VkImageLayout initial=VK_IMAGE_LAYOUT_UNDEFINED, bool load=false) -> VkRenderPass;
     [[gnu::unused]] auto createFramebuffers() -> VkFramebuffer;

     [[gnu::unused]] auto setupImageFormats() -> VkSurfaceFormatKHR;

     [[nodiscard]] auto getSwapChainImages(uint32_t, uint32_t)
         -> std::array<VkImage, Frames>;
     [[nodiscard]] auto createImageViews(std::array<VkImage, Frames> image)
         -> std::array<VkImageView, Frames>;

     [[nodiscard]] auto createImageView(vmaImage image) const -> VkImageView;

     [[gnu::cold]] ~SwapChain() { vkDestroySwapchainKHR(device, swapchain, nullptr); }
};