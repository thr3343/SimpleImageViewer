#include "ComputePipeline.hpp"
#include <array>
#include <cstdint>
#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>
#include "Swizzle.inl"

constexpr uint32_t numImgs=2;

[[nodiscard, gnu::pure]] auto ComputePipeline::determineDescriptorVarient(vmaImage vmaImage) const -> VkDescriptorType
{

    return vmaImage.usageFlags&VK_IMAGE_USAGE_STORAGE_BIT?VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
}

template<typename type>
auto enumBindings(auto strct)
{
     auto arr=std::to_array<type>({strct, strct});
    for(uint32_t a=0;a<numImgs;a++)
    {
        arr[a].binding=a;
    }
    return arr;
}

[[nodiscard]] auto ComputePipeline::setupDescriptorSetLayout() const -> VkDescriptorSetLayout
{

    VkDescriptorSetLayoutBinding bindings
    {
        .binding=0,
        .descriptorType=descriptorVarient,
        .descriptorCount=1,
        .stageFlags=VK_SHADER_STAGE_COMPUTE_BIT,
        .pImmutableSamplers=nullptr,
    };

    auto layouts=enumBindings<VkDescriptorSetLayoutBinding>(bindings);

        
    VkDescriptorSetLayoutCreateInfo layoutInfo
    {
        .sType=VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount=numImgs,
        .pBindings=layouts.data(),
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
    
    VkDescriptorPoolSize poolSizes
    {
        .type=descriptorVarient,
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
  auto x = std::to_array<VkDescriptorImageInfo>(
    {
    {nullptr,compSSBO.view,compSSBO.current},
    {nullptr,compSSBODst.view,compSSBODst.current}
    }
    );




    auto  ssboDescriptorWrites = std::to_array<VkWriteDescriptorSet>({VkWriteDescriptorSet{
        .sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet=compDescriptorSet,
        .dstBinding=0,
        .dstArrayElement=0,
        .descriptorCount=1,
        .descriptorType=descriptorVarient,
        .pImageInfo=&x[0],
    },VkWriteDescriptorSet{
        .sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet=compDescriptorSet,
        .dstBinding=1,
        .dstArrayElement=0,
        .descriptorCount=1,
        .descriptorType=descriptorVarient,
        .pImageInfo=&x[1],
    }});
    
  
    ssboDescriptorWrites[0].pImageInfo=&x[0];
    ssboDescriptorWrites[1].pImageInfo=&x[1];



    vkUpdateDescriptorSets(tmpDevice_, numImgs, ssboDescriptorWrites.data(), 0, nullptr);
}
void ComputePipeline::resizeThis(uint32_t size) noexcept
{       
    vmaUnmapMemory(a, compSSBO.alloc);
    vmaDestroyImage(a, compSSBO.img, compSSBO.alloc);
    compSSBO = allocImg(defres,defSize,compSSBO.usageFlags, compSSBO.view);
    updateDescriptorSetArray(size);
    vmaMapMemory(a, compSSBO.alloc, &data);
    
    vmaUnmapMemory(a, compSSBODst.alloc);
    vmaDestroyImage(a, compSSBODst.img, compSSBODst.alloc);
    compSSBODst = allocImg(defres,defSize,compSSBODst.usageFlags, compSSBODst.view);
    updateDescriptorSetArray(size);
    vmaMapMemory(a, compSSBODst.alloc, &data);
     
}

//TODO(thr3343): Find a better way of handling.storing current imageLayputs in const member functions/PassThrough e.g.

auto ComputePipeline::BGR2RGBSwizzle(ImgLoader const &imgLoader, VkQueue queue, std::array<VkImage, Frames> image, vmaImage src, vmaImage dst) const noexcept -> VkSemaphore
{
    commSet.beginSingleTimeCommands();
    imgLoader.loadImg(commSet, queue, compSSBO);


    // imgLoader.transitionImageLayout(commSet.commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, compSSBO);
    imgLoader.transitionImageLayout(commSet.commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, compSSBODst);
 
    updateDescriptorSetArray();

    vkCmdBindPipeline(commSet.commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, compPipeline);
    vkCmdBindDescriptorSets(commSet.commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, compPipelineLayout, 0, 1, &compDescriptorSet, 0, nullptr);


    constexpr uint32_t rowPitch = 0;
    constexpr VkImageCopy bufferImageCopy
    {
        .dstOffset{0},
        .srcOffset{0},
        .dstSubresource=subresource,
        .srcSubresource=subresource,
        .extent=defres
    };
    constexpr uint64_t scaleX=(width/32);  
    constexpr uint64_t scaleY=(height/32);  
    vkCmdDispatch(commSet.commandBuffer, scaleX, scaleY, 1);


 std::array<VkImageMemoryBarrier, Frames> barriers;
       


    // #pragma nounroll
    for(auto a=0;a<Frames;a++) 
    {

        barriers[a]={VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,nullptr,0,0,VK_IMAGE_LAYOUT_UNDEFINED,VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, 2, 2, image[a], {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1}};

        vkCmdCopyImage(commSet.commandBuffer, compSSBODst.img, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image[a], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &bufferImageCopy);
        

    };
vkCmdPipelineBarrier( 
            commSet.commandBuffer, 
            VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, 
            VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 
            0, 
            0, 
            VK_NULL_HANDLE, 
            0, 
            VK_NULL_HANDLE,
            Frames,
            barriers.data() );

    
   return commSet.endSingleTimeCommandsAlt(queue, true, false);
}

[[nodiscard]] auto ComputePipeline::setupPipeline() const -> VkPipeline
{

    constexpr auto entryPoint = ("main");

    constexpr VkShaderModuleCreateInfo shaderModuleCreateInfo 
    {
        .sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize=Swizzle2.size()*sizeof(uint32_t),
        .pCode=Swizzle2.data()

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