#pragma once
#include "FrameBuffer.hpp"
#include "Vkbase.hpp"
#include <cstdint>
#include <vulkan/vulkan_core.h>
struct Framebuffer : GPUDevice
{
    VkRenderPass renderPass;
    std::array<VkImageView, Frames> imageViews;
    VkFramebuffer frameBuffer;
    Framebuffer(uint32_t width, uint32_t height, std::array<VkImage, Frames> images, GPUDevice gpuDevice) : 
            renderPass(createRenderPass(VK_IMAGE_LAYOUT_UNDEFINED, false)),
            imageViews(createImageViews(images)),
            frameBuffer(createFramebuffers(width, height)),
            GPUDevice{gpuDevice}
            {};

    Framebuffer(uint32_t width, uint32_t height, VkRenderPass renderPass, std::array<VkImage, Frames> images, GPUDevice gpuDevice) : 
            renderPass(renderPass),
            imageViews(createImageViews(images)),
            frameBuffer(createFramebuffers(width, height)),
            GPUDevice{gpuDevice}
            {};
    auto createFramebuffers(uint32_t, uint32_t) -> VkFramebuffer;
    auto createRenderPass(VkImageLayout initial, bool load) -> VkRenderPass;
    auto createImageViews(std::array<VkImage, Frames> images) -> std::array<VkImageView, Frames>;
    ~Framebuffer() = default;
};