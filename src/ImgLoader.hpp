#pragma once

#include "MemSys2.hpp"

#include "VkCommSet.hpp"
#include <array>


struct ImgLoader:MemSys2
{
    VkCommandPool commandPool;
    std::array<VkCommandBuffer, Frames> commandBuffers=doGenCommnd(Frames, commandPool);
    

    constexpr ImgLoader(DiscreteQueue queue, MemSys2  memSys2):
                    MemSys2{memSys2}, 
                    commandPool(genCommPool(queue.queuefamilyVarient)){};


    [[nodiscard]] auto doGenCommnd(uint32_t count, VkCommandPool commandPool) const -> std::array<VkCommandBuffer, Frames>;
    [[nodiscard]] auto genCommPool(uint32_t) const -> VkCommandPool;

    void loadImg(VkCommSet, VkQueue, vmaImage) const;
    void transitionImageLayout( VkCommandBuffer commandBuffer, VkImageLayout newLayout, vmaImage const& image) const;
    void copyImage2Image(vmaImage vkImage, VkCommandBuffer commandBufferSets, VkImage stagingBuffer) const;

   [[gnu::cold]] ~ImgLoader()
    = default;
};