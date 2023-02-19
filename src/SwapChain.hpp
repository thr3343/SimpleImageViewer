#pragma once
#include "defs.tpp"
#include "TMp.hpp"
#include "MemSys2.hpp"
#include <array>
#include <cstdint>
#include <vulkan/vulkan_core.h>




struct V32X2UI {
    uint32_t    width;
    uint32_t    height;
} __attribute__((aligned(8)));


struct SwapchainCapabilities {
    uint8_t                         curImageCount;
    VkFormat                         format;
    VkExtent2D                       currentExtent;
    VkImageUsageFlags                currentUsage;
};

struct SwapChain : Tmp
{
   
    SwapchainCapabilities extent;
    // VkRenderPass renderPass;
    // VkSurfaceFormatKHR format;
    // VkFramebuffer frameBuffer;
    VkSwapchainKHR swapchain;
    VkPresentModeKHR presentMode;
    std::array<VkImage, Frames> image;
    //  std::array<VkImageView, Frames> imageViews;
     explicit SwapChain(Tmp swap)
         :

           extent(handleSwapChainCapabilities()),
        //    renderPass(createRenderPass()),
           // format(setupImageFormats(physDevice, VkSurfaceKHR)),
        //    frameBuffer(createFramebuffers()), 
           swapchain(createSwapChain()),
           image(getSwapChainImages(Frames)),
        //    imageViews(createImageViews(image)),
           SwapChain::Tmp(swap){}; // TODO(Vcmp): use Move Construction to avoid duplciating the handles: (Minor Mem Leak)

     auto handleSwapChainCapabilities() -> SwapchainCapabilities;
     auto createSwapChain() -> VkSwapchainKHR;
     auto createRenderPass(VkImageLayout initial=VK_IMAGE_LAYOUT_UNDEFINED, bool load=false) -> VkRenderPass;
     auto createFramebuffers() -> VkFramebuffer;

     auto setupImageFormats() -> VkSurfaceFormatKHR;

     [[nodiscard]] auto getSwapChainImages(uint32_t)
         -> std::array<VkImage, Frames>;
     [[nodiscard]] auto createImageViews(std::array<VkImage, Frames> image)
         -> std::array<VkImageView, Frames>;

     [[nodiscard]] auto createImageView(vmaImage image) const -> VkImageView;

     [[gnu::cold, gnu::noreturn]] ~SwapChain() 
     {
       
       for (auto a=0;a<Frames;a++) 
       {
            // vkDestroyImageView(tmpDevice_, imageViews[a], nullptr);
            // vkDestroyImage(tmpDevice_, image[a], nullptr);
       }
    //    vkDestroyRenderPass(tmpDevice_, renderPass, nullptr);
    //    vkDestroyFramebuffer(tmpDevice_, frameBuffer, nullptr);
       vkDestroySwapchainKHR(tmpDevice_, swapchain, nullptr);

       
    }
};