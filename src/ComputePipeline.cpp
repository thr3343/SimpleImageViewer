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
            .setLayoutCount=1,
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
                    .poolSizeCount=1,
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
                .descriptorSetCount=1,
                .pSetLayouts=&compDescriptorSetLayout,
            };



            VkDescriptorSet pDescriptorSet;

            vkAllocateDescriptorSets(tmpDevice_, &allocInfo, &pDescriptorSet);


            return pDescriptorSet;
        
}

void ComputePipeline::updateDescriptorSetArray(uint32_t size) const noexcept
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
void ComputePipeline::resizeThis(uint32_t size) noexcept
{       
           vmaUnmapMemory(a, compSSBO.alloc);
            vmaDestroyBuffer(a, compSSBO.buff, compSSBO.alloc);
            compSSBO = allocBuff(size,compSSBO.usageFlags,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
            updateDescriptorSetArray(size);
            vmaMapMemory(a, compSSBO.alloc, &data);
     
}

void ComputePipeline::BGR2RGBSwizzle(ImgLoader const &imgLoader, VkQueue queue, std::array<VkImage, Frames> image) const noexcept
{
    commSet.beginSingleTimeCommands();
    imgLoader.loadImg(commSet, queue, compSSBO);

    vkCmdBindPipeline(commSet.commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, compPipeline);
    vkCmdBindDescriptorSets(commSet.commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, compPipelineLayout, 0, 1, &compDescriptorSet, 0, nullptr);


    constexpr uint32_t rowPitch = 0;
    constexpr VkBufferImageCopy bufferImageCopy
    {
        .bufferOffset=0,
        .bufferImageHeight=height,
        .imageExtent=defres,
        .bufferRowLength=rowPitch,
        .imageOffset=0,
        .imageSubresource=subresource
    };

    // vkCmdCopyImageToBuffer(commSet.commandBuffer, TImg2.img, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, compSSBO.buff, 1, &bufferImageCopy);
    

    uint64_t scaleX=(defSize/4/32/128);  
    vkCmdDispatch(commSet.commandBuffer, scaleX, 1, 1);


    // #pragma nounroll
    for(const VkImage &img : image) 
    {
    imgLoader.transitionImageLayout(commSet.commandBuffer, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, img);
    vkCmdCopyBufferToImage(commSet.commandBuffer, compSSBO.buff, img, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &bufferImageCopy);
    imgLoader.transitionImageLayout(commSet.commandBuffer, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, img);
    }
    commSet.endSingleTimeCommands(queue, true, false);
}

[[nodiscard]] auto ComputePipeline::setupPipeline() const -> VkPipeline
{

    constexpr auto entryPoint = ("main");

    constexpr VkShaderModuleCreateInfo shaderModuleCreateInfo 
    {
        .sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize=Swizzle.size()*sizeof(uint32_t),
        .pCode=Swizzle.begin()

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