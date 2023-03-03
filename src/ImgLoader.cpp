#include "ImgLoader.hpp"
#include <vk_mem_alloc.h>
#include "fmt/core.h"
#include "imgLud.hpp"
#include "vec_u8string_view.hpp"


auto ImgLoader::genCommPool(uint32_t QueuefamilyIndex) const -> VkCommandPool
{
  
  VkCommandPoolCreateInfo  poolInfo
  {
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .flags=VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
    .queueFamilyIndex = 2,
  };
  return doPointerAlloc5<VkCommandPool>( &poolInfo, vkCreateCommandPool );
 
}



auto ImgLoader::doGenCommnd(uint32_t count, VkCommandPool commandPool) const -> std::array<VkCommandBuffer, Frames>
{
  std::array<VkCommandBuffer, Frames> PreTestBuffer;
   const VkCommandBufferAllocateInfo allocateInfo{ .sType              =  VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ,
                                                  .commandPool        =  commandPool ,
                                                  .level              =  VK_COMMAND_BUFFER_LEVEL_PRIMARY ,
                                                  .commandBufferCount = count};
  fmt::print("{} {}\n", allocateInfo.commandBufferCount, "Command Buffers");
  
  chkTst(vkAllocateCommandBuffers(tmpDevice_, &allocateInfo, PreTestBuffer.data() ));
  return PreTestBuffer;
}

void ImgLoader::copyImage2Image(vmaImage vkImage, VkCommandBuffer commandBufferSets, VkImage stagingBuffer) const
{
    constexpr VkImageCopy copyRegion
    {
      .srcSubresource=subresource,
      .srcOffset=VkOffset3D{},
      .dstSubresource=subresource,
	    .dstOffset=VkOffset3D{},
      .extent=defres
    };
    

	//copy the buffer into the image
    constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags = ( VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) };
  vkBeginCommandBuffer(commandBufferSets, &beginInfo1);
  {
    transitionImageLayout(commandBufferSets, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, stagingBuffer);
    vkCmdCopyImage(commandBufferSets, vkImage.img, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, stagingBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);
    transitionImageLayout(commandBufferSets, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, stagingBuffer);
  }
  vkEndCommandBuffer( commandBufferSets );
}


vmaImage copyBuffer2Image(vmaImage &vkImage, VkCommSet commandBufferSets, vmaBuffer stagingBuffer, VkQueue queue)
{
      constexpr VkBufferImageCopy copyRegion
    {
	    .bufferOffset = 0,

	    .imageSubresource=subresource,
	    .imageExtent = defres,
    };
 
  fmt::print("Allocating img:");
	//copy the buffer into the image
  
  vkCmdCopyBufferToImage(commandBufferSets.commandBuffer, stagingBuffer.buff, vkImage.img, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);

        // fmt::print("%s %ld \n", "Copied Buff-ToImg in :", clock() - a/CLOCKS_PER_SEC);

    return vkImage;
}

void ImgLoader::loadImg(VkCommSet commandBufferSets, VkQueue queue, vmaImage vmaImage) const
{
    auto a = clock();
    int x, y, cnls;
        vec_u8string_view fn=vec_u8string_view::initHelper({R"(tst.png)"});
        FILE *f = fopen64(fn.cbegin(), "rb");

        if(_mm_testc_si128(fn.getExtensionfromSubString(), png)) fmt::println("IS PNG Image!");
        fmt::print("Opened Image in : {}\n", clock() - a/CLOCKS_PER_SEC);

        
    auto limg = tstA::loadImg(*f, x, y, cnls);
    // std::cout << sizeof(limg) <<"--"<< x <<"--"<< y <<"--"<< cnls << "\n";
    fmt::print("Loaded Image in : {}\n", clock() - a/CLOCKS_PER_SEC);
 
     uint32_t imageSize = width * height*4UL;


    constexpr VkOffset2D Offs{width, height};



    auto stagingBuffer = allocBuff(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT|VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, true);
    //memSys::addMappedSection(VmaAllocation, imageSize);
    vmaMapMemory(this->a, stagingBuffer.alloc, (&stagingBuffer.aData));
    {

	    memcpy(stagingBuffer.aData, limg, imageSize);

    }
    vmaUnmapMemory(this->a, stagingBuffer.alloc);
        fmt::print("Copied Image in : {}\n", clock() - a/CLOCKS_PER_SEC);


    transitionImageLayout(commandBufferSets.commandBuffer, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, vmaImage.img);
    vmaImage.current=VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    copyBuffer2Image(vmaImage, commandBufferSets, stagingBuffer, queue);
   

}

void ImgLoader::transitionImageLayout( VkCommandBuffer commandBuffer, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkImage const& image) const
{
   
  VkImageMemoryBarrier barrier = {
    .sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
    .pNext               = VK_NULL_HANDLE,
    .oldLayout           = oldLayout,
    .newLayout           = ( newLayout ),
    .srcQueueFamilyIndex = ( 0 ),
    .dstQueueFamilyIndex = ( 0 ),
    .image               = ( image ),
    .subresourceRange    = { .aspectMask     = static_cast<VkImageAspectFlags>( ( format ) ),
                             .baseMipLevel   = ( 0 ),
                             .levelCount     = ( 1 ),
                             .baseArrayLayer = ( 0 ),
                             .layerCount     = ( 1 ) },
  };

  if ( newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL )
  {
    if ( format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT )
    {
      barrier.subresourceRange.aspectMask = ( barrier.subresourceRange.aspectMask | VK_IMAGE_ASPECT_STENCIL_BIT );
    }
  }

  VkPipelineStageFlags sourceStage      = 0;
  VkPipelineStageFlags destinationStage = 0;
  switch ( oldLayout )
  {
    case VK_IMAGE_LAYOUT_PREINITIALIZED: barrier.srcAccessMask = ( VK_ACCESS_MEMORY_READ_BIT ); break;
    
    case VK_IMAGE_LAYOUT_UNDEFINED: barrier.srcAccessMask = ( VK_ACCESS_SHADER_READ_BIT ); break;

    case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL: barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT; break;
    case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL: barrier.srcAccessMask = VK_ACCESS_NONE; break;

    case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR: barrier.srcAccessMask = VK_ACCESS_NONE; break;
    case VK_IMAGE_LAYOUT_GENERAL: barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT; break;

    default:  fmt::print( "Unsupported layout transition" ), exit(1);
  }

  switch ( newLayout )
  {
    case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
      {
        barrier.subresourceRange.aspectMask = ( VK_IMAGE_ASPECT_DEPTH_BIT );
        barrier.dstAccessMask = ( VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT );
        sourceStage           = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage      = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
        break;
      }
    case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
      {
        barrier.subresourceRange.aspectMask = ( VK_IMAGE_ASPECT_COLOR_BIT );
        barrier.dstAccessMask = ( VK_ACCESS_SHADER_READ_BIT );
        sourceStage           = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage      = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        break;
      }
    case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
    {
        barrier.subresourceRange.aspectMask = ( VK_IMAGE_ASPECT_COLOR_BIT );
        barrier.dstAccessMask = ( VK_ACCESS_TRANSFER_READ_BIT );
        sourceStage           = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage      = VK_PIPELINE_STAGE_TRANSFER_BIT;
        break;
    }
    case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
    {
        barrier.subresourceRange.aspectMask = ( VK_IMAGE_ASPECT_COLOR_BIT );
        barrier.dstAccessMask = ( VK_ACCESS_SHADER_READ_BIT );
        sourceStage           = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
        destinationStage      = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
        break;
    }
    case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
    {
        barrier.subresourceRange.aspectMask = ( VK_IMAGE_ASPECT_COLOR_BIT );
        barrier.dstAccessMask = ( VK_ACCESS_NONE );
        sourceStage           = VK_PIPELINE_STAGE_NONE;
        destinationStage      = VK_PIPELINE_STAGE_NONE;
        break;
    }case VK_IMAGE_LAYOUT_GENERAL:
    {
        barrier.subresourceRange.aspectMask = ( VK_IMAGE_ASPECT_COLOR_BIT );
        barrier.dstAccessMask = ( VK_ACCESS_TRANSFER_WRITE_BIT);
        sourceStage           = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage      = VK_PIPELINE_STAGE_TRANSFER_BIT;
        break;
    }
    default:  fmt::print( "Unsupported layout transition" ), exit(1);
  }

  vkCmdPipelineBarrier( 
            commandBuffer, 
            sourceStage, 
            destinationStage, 
            0, 
            0, 
            VK_NULL_HANDLE, 
            0, 
            VK_NULL_HANDLE,
            1,
            &barrier );
}




[[gnu::pure]] auto constexpr fma2(auto a, auto b, auto c) noexcept
{
  return (a*b)+c;
}
[[gnu::pure]] auto consteval tPow(auto a)
{
  return a*a;
}

[[gnu::pure]] auto constexpr dot(VkExtent2D extent)
{
  return extent.height*extent.width;
}


[[gnu::pure]] auto __vectorcall aspect(VkExtent2D extent)
{
  constexpr auto asp =static_cast<double>(width)/height;

  auto asp3 = static_cast<float>(extent.width)/extent.height;
  return (asp3>asp) ? VkOffset2D{static_cast<int>(height-(width/asp3)), 0} : VkOffset2D{0, static_cast<int>(fma2(width, asp3, -width))};
}