#pragma once
#include "defs.tpp"
#include "TMp.hpp"
#include "VkCommSet.hpp"
#include "MemSys2.hpp"





struct ComputePipeline : MemSys2
{
    explicit ComputePipeline(MemSys2 const& Memsys) noexcept :commSet{Memsys, Memsys.q.queuefamilyVarient}, MemSys2(Memsys){};
    VkCommSet commSet;
    VkDescriptorSetLayout compDescriptorSetLayout=setupDescriptorSetLayout();
    vmaBuffer compSSBO=allocBuff(width*height*4,VK_BUFFER_USAGE_STORAGE_BUFFER_BIT|VK_BUFFER_USAGE_TRANSFER_SRC_BIT|VK_BUFFER_USAGE_TRANSFER_DST_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    VkPipelineLayout compPipelineLayout=setupLayout();
    VkPipeline compPipeline=setupPipeline();
    VkPipelineCache compPipelineCache;

    VkDescriptorPool compDescriptorPool=setupDescriptorPool();
    VkDescriptorSet compDescriptorSet=allocDescriptorSet();
    [[nodiscard]] auto setupPipeline() const -> VkPipeline;
    [[nodiscard]] auto setupDescriptorSetLayout() const -> VkDescriptorSetLayout;
    [[nodiscard]] auto setupLayout() const -> VkPipelineLayout;
    [[nodiscard]] auto setupDescriptorPool() const -> VkDescriptorPool;
    [[nodiscard]] auto allocDescriptorSet() const -> VkDescriptorSet;
    [[gnu::pure]] void updateDescriptorSetArray(uint32_t=width*height*4) const noexcept;
    [[gnu::pure]] void resizeThis(uint32_t=width*height*4) noexcept;
    [[gnu::pure]] void reLoad();
};