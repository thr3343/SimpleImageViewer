#pragma once
#include "defs.tpp"
#include "TMp.hpp"
#include <cstdint>

struct VkCommSet:Tmp
{
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;

    VkCommandPool genCommPool(uint32_t);
    VkCommandBuffer doGenCommnd(VkCommandPool);
    constexpr explicit VkCommSet(Tmp tmp, uint32_t i=2): commandPool(genCommPool(i)),commandBuffer(doGenCommnd(commandPool)), Tmp{tmp} {};
    void beginSingleTimeCommands() const;
    void endSingleTimeCommands(VkQueue queue, bool=true, bool=false) const;
};