#include "ImgLoader.hpp"
#include <array>
#include <cstdint>
#include <ctime>
#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>
#include "imgLud.hpp"
#include "VkCommSet.hpp"


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
  printf("%i %s\n",allocateInfo.commandBufferCount, "Command Buffers");
  
  chkTst(vkAllocateCommandBuffers(tmpDevice_, &allocateInfo, PreTestBuffer.data() ));
  return PreTestBuffer;
}

void ImgLoader::copyImage2Image(vmaImage vkImage, VkCommandBuffer commandBufferSets, VkImage stagingBuffer) const
{
       VkImageCopy copyRegion
    {
      .srcSubresource=subresource,
      .srcOffset=VkOffset3D{0, 0, 0},
      .dstSubresource=subresource,
	    .dstOffset=VkOffset3D{0, 0, 0},
      .extent=defres

    };
    
  // printf("Allocating img:");
	//copy the buffer into the image
    constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags = ( VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) };
  vkBeginCommandBuffer(commandBufferSets, &beginInfo1);
  {
    transitionImageLayout(commandBufferSets, VK_FORMAT_B8G8R8A8_UNORM, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, stagingBuffer);
    vkCmdCopyImage(commandBufferSets, vkImage.img, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, stagingBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);
    transitionImageLayout(commandBufferSets, VK_FORMAT_B8G8R8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, stagingBuffer);
    // vkImage.current=VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
  }
  
  vkEndCommandBuffer( commandBufferSets );


        // printf("%s %ld \n", "Copied Buff-ToImg in :", clock() - a/CLOCKS_PER_SEC);

    
}


vmaImage copyImage2Buffer(vmaImage vkImage, VkCommSet commandBufferSets, vmaBuffer stagingBuffer, VkQueue queue)
{
      constexpr VkBufferImageCopy copyRegion
    {
	    .bufferOffset = 0,

	    .imageSubresource=subresource,
	    .imageExtent = defres,
    };

  printf("Allocating img:");
	//copy the buffer into the image
  
  {
    vkCmdCopyBufferToImage(commandBufferSets.commandBuffer, stagingBuffer.buff, vkImage.img, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);
    // transitionImageLayout(commandBufferSets.commandBuffer, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, vkImage.img);
    // vkImage.current=VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
  }
  
        // printf("%s %ld \n", "Copied Buff-ToImg in :", clock() - a/CLOCKS_PER_SEC);

    return vkImage;
}

void ImgLoader::loadImg(VkCommSet commandBufferSets, VkQueue queue, vmaBuffer stagingBuffer)
{
    auto a = clock();
    int x, y, cnls;
        FILE *f = fopen64(R"(tst.png)", "rb");
        printf("%s %ld \n", "Opened Image in :", clock() - a/CLOCKS_PER_SEC);

        
    auto limg = tstA::loadImg(*f, x, y, cnls);
    // std::cout << sizeof(limg) <<"--"<< x <<"--"<< y <<"--"<< cnls << "\n";
    printf("%s %ld \n", "Loaded Image in :", clock() - a/CLOCKS_PER_SEC);
 
     uint32_t imageSize = width * height*4UL;


    constexpr VkOffset2D Offs{width, height};

    // auto stagingBuffer = allocBuff(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT|VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, true);
    //memSys::addMappedSection(VmaAllocation, imageSize);
    vmaMapMemory(this->a, stagingBuffer.alloc, (&data));
    {

	    memcpy(data, limg, imageSize);

    }
    vmaUnmapMemory(this->a, stagingBuffer.alloc);
        printf("%s %ld \n", "Copied Image in :", clock() - a/CLOCKS_PER_SEC);

	  // memSys::mapMem(limg, imageSize);

	// tstA::freeImg(limg);

   
    // auto vkImage= allocImg(defres, imageSize, VK_IMAGE_USAGE_TRANSFER_SRC_BIT|VK_IMAGE_USAGE_TRANSFER_DST_BIT);
   
    // return copyImage2Buffer(vkImage, commandBufferSets, stagingBuffer, queue);
   

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

    default:  printf( "Unsupported layout transition" ), exit(1);
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
    default:  printf( "Unsupported layout transition" ), exit(1);
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


/* void ImgLoader::vkRecImg(VkImage const& img, int a, VkQueue queue) const
{
  auto xyl=aspect(VkExtent2D{width, height});
  int aa = fma2(width, height, 10);
  
  VkImageBlit imgBlt
  {
    .srcSubresource=subresource,
    .srcOffsets={{0,0,0},VkOffset3D{width, height, 1}},
    .dstSubresource=subresource,
    .dstOffsets={{-xyl.y,xyl.x,0},{width+(xyl.y>>1),height-(xyl.x>>1),1}},
  };


    constexpr VkRect2D renderArea = { .offset = { 0, 0 }, .extent = {width, height} };


  
  static constexpr VkDeviceSize offsets[] = { 0 };

  VkCommSet commSet{*this};

  commSet.beginSingleTimeCommands();
  vkCmdBlitImage(commSet.commandBuffer, vmaImg.img, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, img, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &imgBlt, VK_FILTER_LINEAR);
        

  
  transitionImageLayout(commSet.commandBuffer, VK_FORMAT_B8G8R8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, img);

  commSet.endSingleTimeCommands(queue, false);

  
} */