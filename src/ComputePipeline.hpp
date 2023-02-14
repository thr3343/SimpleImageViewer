#pragma once
#include "defs.tpp"
#include "TMp.hpp"
#include "VkCommSet.hpp"
#include "MemSys2.hpp"
#include "ImgLoader.hpp"
#include <array>





struct ComputePipeline : MemSys2
{
    explicit ComputePipeline(MemSys2 const& Memsys) noexcept :commSet{Memsys, Memsys.q.queuefamilyVarient}, MemSys2{Memsys}{ updateDescriptorSetArray(compSSBO.size);};
    VkCommSet commSet;
    VkDescriptorSetLayout compDescriptorSetLayout=setupDescriptorSetLayout();
    vmaBuffer compSSBO=allocBuff(defSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT|VK_BUFFER_USAGE_TRANSFER_SRC_BIT|VK_BUFFER_USAGE_TRANSFER_DST_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, true);
    VkPipelineLayout compPipelineLayout=setupLayout();
    VkPipeline compPipeline=setupPipeline();
    // VkPipelineCache compPipelineCache;

    VkDescriptorPool compDescriptorPool=setupDescriptorPool();
    VkDescriptorSet compDescriptorSet=allocDescriptorSet();
    [[nodiscard]] auto setupPipeline() const -> VkPipeline;
    [[nodiscard]] auto setupDescriptorSetLayout() const -> VkDescriptorSetLayout;
    [[nodiscard]] auto setupLayout() const -> VkPipelineLayout;
    [[nodiscard]] auto setupDescriptorPool() const -> VkDescriptorPool;
    [[nodiscard]] auto allocDescriptorSet() const -> VkDescriptorSet;
    void updateDescriptorSetArray(uint32_t=defSize) const noexcept;
    void resizeThis(uint32_t=defSize) noexcept;
    [[gnu::pure]] void reLoad();
    
    [[gnu::pure]] void BGR2RGBSwizzle(ImgLoader &imgLoader, VkQueue queue, std::array<VkImage, Frames> image) const noexcept;
};