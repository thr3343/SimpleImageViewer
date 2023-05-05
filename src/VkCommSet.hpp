#pragma once
#include "defs.tpp"
#include "Vkbase.hpp"
#include <cstdint>

struct VkCommSet:GPUDevice
{
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    VkFence fence=setupFence();

    VkCommandPool genCommPool(uint32_t);
    VkCommandBuffer doGenCommnd(VkCommandPool);
     explicit VkCommSet(GPUDevice tmp, uint32_t i=2): commandPool(genCommPool(i)),commandBuffer(doGenCommnd(commandPool)), GPUDevice{tmp} {};
    void beginSingleTimeCommands() const;
    void endSingleTimeCommands(VkQueue queue, bool submit=true, bool wait=false) const;
    auto endSingleTimeCommandsAlt(VkQueue queue, bool submit=true, bool wait=false) const -> VkSemaphore;
    [[nodiscard]] auto setupFence() const noexcept -> VkFence;
};