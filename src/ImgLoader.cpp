#include "ImgLoader.hpp"
#include <__fwd/string_view.h>
#include <array>
#include <corecrt.h>
#include <cstdint>
#include <smmintrin.h>
#include <string>
#include <string_view>
#include <vk_mem_alloc.h>
#include "fmt/core.h"
#include "imgLud.hpp"
#include "vec_u8string_view.hpp"
#include <filesystem>
#include <vulkan/vulkan_core.h>


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
  
  chkTst(vkAllocateCommandBuffers(device, &allocateInfo, PreTestBuffer.data() ));
  return PreTestBuffer;
}

// void ImgLoader::copyImage2Image(vmaImage vkImage, VkCommandBuffer commandBufferSets, VkImage stagingBuffer) const
// {
//     constexpr VkImageCopy copyRegion
//     {
//       .srcSubresource=subresource,
//       .srcOffset=VkOffset3D{},
//       .dstSubresource=subresource,
// 	    .dstOffset=VkOffset3D{},
//       .extent=defres
//     };
    

// 	//copy the buffer into the image
//     constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
//                                                     .flags = ( VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) };
//   vkBeginCommandBuffer(commandBufferSets, &beginInfo1);
//   {
//     transitionImageLayout(commandBufferSets, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, stagingBuffer);
//     vkCmdCopyImage(commandBufferSets, vkImage.img, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, stagingBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);
//     transitionImageLayout(commandBufferSets, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, stagingBuffer);
//   }
//   vkEndCommandBuffer( commandBufferSets );
// }


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
constexpr std::string_view fail = std::string_view{"FAIL!"};
//This Function generates very ugly ASM (likely due to heap Allocations from std::string); May be worth optimising this later
[[gnu::pure]] auto testDir(  std::string ax="imgs/") noexcept -> std::string_view
{
      // const std::filesystem::path png{".png"};
      for (const auto& dir_entry : std::filesystem::directory_iterator{ax}->path().filename()) 
      {
          if(dir_entry.extension()==".png")
          {
            return ax.append(dir_entry.string());
          }
      }
      return fail;
}

//TODO() Create Fake image to fill the Framebuffer>Swapchain Image if Dedocded/Decomrpessed bitMap s too small
//Or PRefill All SwapChain Images with a Def/Black background via Image Copy to SwapChain Directly overwrite any occluded Pixels

//Edit: not nessacery as an empty SwapChain>frameBuffer is Empty/black/Uninitialised Anyway, Only Scaling is needed/isues only occur if Resolution is Smaller than the current vkImage/ViewPort
struct imgDetails
{
  uint16_t width, height;
  uint8_t bitDepth;
  VkFormat format;

  vmaBuffer allocBuffer;

};


void ImgLoader::loadImg(VkCommSet commandBufferSets, VkQueue queue, vmaImage vmaImage) const
{
    auto a = clock();
    auto imgDir=testDir();
        fmt::print("Opening: {}\n", imgDir.data());
        /* std::to_array("imgs/tst.png").data() */
        FILE *f = fopen64(imgDir.data(), "rb");

        



        fmt::print("Opened Image in : {}\n", clock() - a/CLOCKS_PER_SEC);





    int x, y, cnls;
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


    transitionImageLayout(commandBufferSets.commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, vmaImage);
    vmaImage.current=VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    copyBuffer2Image(vmaImage, commandBufferSets, stagingBuffer, queue);
   

}

void ImgLoader::transitionImageLayout( VkCommandBuffer commandBuffer, VkImageLayout newLayout, vmaImage const&image) const
{
  const VkImageLayout oldLayout = image.current;
  VkImageMemoryBarrier barrier{
    .sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
    .pNext               = VK_NULL_HANDLE,
    .oldLayout           = oldLayout,
    .newLayout           = ( newLayout ),
    .srcQueueFamilyIndex = ( 2 ),
    .dstQueueFamilyIndex = ( 2 ),
    .image               = ( image.img ),
    .subresourceRange    = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1}
      
  };

  VkPipelineStageFlags sourceStage      = 0;
  VkPipelineStageFlags destinationStage = 0;
  
  switch ( oldLayout+newLayout )
  {

    case VK_IMAGE_LAYOUT_PREINITIALIZED+VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
    case VK_IMAGE_LAYOUT_UNDEFINED+VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
    {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        barrier.dstAccessMask = ( VK_ACCESS_TRANSFER_WRITE_BIT);
        sourceStage           = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage      = VK_PIPELINE_STAGE_TRANSFER_BIT;
        break;
    } 
    case VK_IMAGE_LAYOUT_UNDEFINED+VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
    {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = ( VK_ACCESS_TRANSFER_READ_BIT);
        sourceStage           = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage      = VK_PIPELINE_STAGE_TRANSFER_BIT;
        break;
    }
    case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL+VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
    {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = ( VK_ACCESS_SHADER_WRITE_BIT);
        sourceStage           = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage      = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
        break;
    }
    case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL+VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
    {
        barrier.srcAccessMask = VK_ACCESS_NONE;
        barrier.dstAccessMask = VK_ACCESS_NONE;
        sourceStage           = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage      = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
        break;
    }
    default:  fmt::print( "Unsupported layout transition: {} {}", oldLayout, newLayout ), exit(1);
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