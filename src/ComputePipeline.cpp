#include "ComputePipeline.hpp"
#include <cstdint>
#include <vk_mem_alloc.h>
#include "Swizzle.inl"

[[nodiscard]] auto ComputePipeline::setupDescriptorSetLayout() const -> VkDescriptorSetLayout
{

    VkDescriptorSetLayoutBinding bindings
    {
        .binding=0,
        .descriptorType=VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        .descriptorCount=1,
        .stageFlags=VK_SHADER_STAGE_COMPUTE_BIT,
        .pImmutableSamplers=nullptr,
    };

        
    VkDescriptorSetLayoutCreateInfo layoutInfo
    {
        .sType=VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount=1,
        .pBindings=&bindings,
    };

    return doPointerAlloc5<VkDescriptorSetLayout>(&layoutInfo, vkCreateDescriptorSetLayout);

  
}

[[nodiscard]] auto ComputePipeline::setupLayout() const -> VkPipelineLayout
{
     VkPipelineLayoutCreateInfo pipelineLayoutInfo
     {
            .sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            .pSetLayouts=&compDescriptorSetLayout,
     };

    return doPointerAlloc5<VkPipelineLayout>(&pipelineLayoutInfo, vkCreatePipelineLayout);
    
}
[[nodiscard]] auto ComputePipeline::setupDescriptorPool() const -> VkDescriptorPool
{
    
                constexpr VkDescriptorPoolSize poolSizes
                {
                    .type=VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                    .descriptorCount=1,
                };


                VkDescriptorPoolCreateInfo VkQueryPoolCreateInfo
                {
                    .sType=VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
                    .maxSets=1,
                    .pPoolSizes=&poolSizes,
                };

              return doPointerAlloc5<VkDescriptorPool>(&VkQueryPoolCreateInfo, vkCreateDescriptorPool);
}
[[nodiscard]] auto ComputePipeline::allocDescriptorSet() const -> VkDescriptorSet
{
   

            VkDescriptorSetAllocateInfo allocInfo
            {
                .sType=VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
                .descriptorPool=compDescriptorPool,
                .pSetLayouts=&compDescriptorSetLayout,
            };



            VkDescriptorSet pDescriptorSet;

            vkAllocateDescriptorSets(tmpDevice_, &allocInfo, &pDescriptorSet);


            return pDescriptorSet;
        
}

[[gnu::pure]] void ComputePipeline::updateDescriptorSetArray(uint32_t size) const noexcept
{
     VkDescriptorBufferInfo bufferInfos
     {
            .buffer=compSSBO.buff,
            .offset=0,
            .range=size,
     };



        VkWriteDescriptorSet ssboDescriptorWrite
        {
            .sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .dstSet=compDescriptorSet,
            .dstBinding=0,
            .dstArrayElement=0,
            .descriptorCount=1,
            .descriptorType=VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
            .pBufferInfo=&bufferInfos,
        };



        vkUpdateDescriptorSets(tmpDevice_, 1, &ssboDescriptorWrite, 0, nullptr);
}
[[gnu::pure]] void ComputePipeline::resizeThis(uint32_t size) noexcept
{       
           vmaUnmapMemory(a, compSSBO.alloc);
            vmaDestroyBuffer(a, compSSBO.buff, compSSBO.alloc);
            compSSBO = allocBuff(size,compSSBO.usageFlags,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
            updateDescriptorSetArray(size);
            vmaMapMemory(a, compSSBO.alloc, &data);
     
}

[[nodiscard]] auto ComputePipeline::setupPipeline() const -> VkPipeline
{

    constexpr auto entryPoint = ("main");

    constexpr VkShaderModuleCreateInfo shaderModuleCreateInfo 
    {
        .sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize=ax.size(),
        .pCode=ax.data()

    };

    VkPipelineShaderStageCreateInfo compShaderStageInfo
    {
        .sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage=VK_SHADER_STAGE_COMPUTE_BIT,
        .module=doPointerAlloc5<VkShaderModule>(&shaderModuleCreateInfo, vkCreateShaderModule),
        .pName=entryPoint,
    };



    VkComputePipelineCreateInfo ComputePipelineCreateInfo 
    {
        .sType=VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .flags=VK_PIPELINE_CREATE_DISPATCH_BASE, 
        .stage=compShaderStageInfo,
        .layout=compPipelineLayout,
        .basePipelineHandle=VK_NULL_HANDLE,
        .basePipelineIndex=-1
       
    };

    VkPipeline compPipeLine;
    vkCreateComputePipelines(tmpDevice_, nullptr, 1, &ComputePipelineCreateInfo, nullptr, &compPipeLine);
    return compPipeLine;
}