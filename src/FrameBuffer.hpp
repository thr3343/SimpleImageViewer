#pragma once
#include "FrameBuffer.hpp"
#include "Vkbase.hpp"
#include <cstdint>
#include <vulkan/vulkan_core.h>
struct Framebuffer : GPUDevice
{
    VkRenderPass renderPass;
    VkFramebuffer frameBuffer;
    std::array<VkImageView, Frames> imageViews;
    Framebuffer(std::array<VkImage, Frames> images, GPUDevice gpuDevice) : 
            renderPass(createRenderPass(VK_IMAGE_LAYOUT_UNDEFINED, false)),
            imageViews(createImageViews(images)),
            frameBuffer(createFramebuffers()),
            GPUDevice{gpuDevice}
            {};
    auto createFramebuffers() -> VkFramebuffer;
    auto createRenderPass(VkImageLayout initial, bool load) -> VkRenderPass;
    auto createImageViews(std::array<VkImage, Frames> images) -> std::array<VkImageView, Frames>;

};