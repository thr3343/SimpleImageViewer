#pragma once

#include "MemSys2.hpp"
#include "Vkbase.hpp"
#include "VkCommSet.hpp"
#include <array>
#include <cstdint>

struct ImgLoader:MemSys2
{
    VkCommandPool commandPool;
    std::array<VkCommandBuffer, Frames> commandBuffers=doGenCommnd(Frames, commandPool);
    
    // vmaImage vmaImg;

    void loadImg(VkCommSet, VkQueue, vmaBuffer) const;
    void transitionImageLayout( VkCommandBuffer commandBuffer, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkImage const& image) const;
    // void vkRecImg(VkImage const& img, int a, VkQueue queue) const;
    [[nodiscard]] auto doGenCommnd(uint32_t count, VkCommandPool commandPool) const -> std::array<VkCommandBuffer, Frames>;
    [[nodiscard]] auto genCommPool(uint32_t) const -> VkCommandPool;
    void copyImage2Image(vmaImage vkImage, VkCommandBuffer commandBufferSets, VkImage stagingBuffer) const;

    constexpr  ImgLoader(DiscreteQueue queue, MemSys2  memSys2): 
                   
                    MemSys2{memSys2}, 
                    commandPool(genCommPool(queue.queuefamilyVarient)){};

   [[gnu::cold]] ~ImgLoader()
    = default;
};