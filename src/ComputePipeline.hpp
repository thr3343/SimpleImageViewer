#pragma once
#include "defs.tpp"
#include "TMp.hpp"
#include "VkCommSet.hpp"
#include "MemSys2.hpp"
#include "ImgLoader.hpp"
#include "SwapChain.hpp"
#include <array>
#include <vulkan/vulkan_core.h>






struct ComputePipeline : MemSys2
{
    VkCommSet commSet;
    vmaImage compSSBO;
    
    explicit ComputePipeline(MemSys2 const& Memsys, const SwapChain& swapChain) noexcept : 
            commSet{Memsys, Memsys.q.queuefamilyVarient}, 
            compSSBO(allocImg(defres, defSize, VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_TRANSFER_SRC_BIT|VK_IMAGE_USAGE_STORAGE_BIT)), 
            MemSys2{Memsys}
            { 
                compSSBO.view=swapChain.createImageView(compSSBO);
                updateDescriptorSetArray(compSSBO.size);
            };
            
    VkDescriptorType descriptorVarient=determineDescriptorVarient(compSSBO);
    VkDescriptorSetLayout compDescriptorSetLayout=setupDescriptorSetLayout();
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
    [[nodiscard, gnu::pure]] auto determineDescriptorVarient(vmaImage) const -> VkDescriptorType;

    void updateDescriptorSetArray(uint32_t=defSize) const noexcept;
    void resizeThis(uint32_t=defSize) noexcept;
    void reLoad();
    
    void BGR2RGBSwizzle(ImgLoader const&imgLoader, VkQueue queue, std::array<VkImage, Frames> image) const noexcept;
};