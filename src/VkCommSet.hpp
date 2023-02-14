#pragma once
#include "defs.tpp"
#include "TMp.hpp"
#include <cstdint>

struct VkCommSet:Tmp
{
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    VkFence fence=setupFence();

    VkCommandPool genCommPool(uint32_t);
    VkCommandBuffer doGenCommnd(VkCommandPool);
     explicit VkCommSet(Tmp tmp, uint32_t i=2): commandPool(genCommPool(i)),commandBuffer(doGenCommnd(commandPool)), Tmp{tmp} {};
    void beginSingleTimeCommands() const;
    void endSingleTimeCommands(VkQueue queue, bool submit=true, bool wait=false) const;
    [[nodiscard]] auto setupFence() const noexcept -> VkFence;
};