#include "SwapChain.hpp"
#include <cstdint>
#include <vector>
#include <cstdio>
#include <vulkan/vulkan_core.h>




auto SwapChain::getSwapChainImages(uint32_t size) -> std::array<VkImage, Frames>
{
  printf( "get SwapChain Images\n");
  std::array<VkImage, Frames> image;
constexpr uint32_t a = 2;
  VkImageCreateInfo VkImageCreateInfo{
    .sType=VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
    .flags=VK_IMAGE_CREATE_EXTENDED_USAGE_BIT,
    .imageType=VK_IMAGE_TYPE_2D,
    .format=VK_FORMAT_B8G8R8A8_SRGB,
    .extent{width,height,1},
    .mipLevels=1,
    .arrayLayers=1,
    .samples=VK_SAMPLE_COUNT_1_BIT,
    .tiling=VK_IMAGE_TILING_OPTIMAL,
    .usage=VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_STORAGE_BIT,
    .queueFamilyIndexCount=1,
    .pQueueFamilyIndices=&a,
    .initialLayout=VK_IMAGE_LAYOUT_UNDEFINED
  };
  
  vkCreateImage(tmpDevice_, &VkImageCreateInfo, nullptr, image.data());

  vkGetSwapchainImagesKHR( tmpDevice_, swapchain, &size, image.data());
  return image;
}


  auto SwapChain::createImageViews(std::array<VkImage, Frames> images) -> std::array<VkImageView, Frames>
  {
    printf( "Creating Image Views\n");
    int i = 0;
    std::array<VkImageView, Frames> imageViews;

    VkImageSubresourceRange subresourceRange{  VK_IMAGE_ASPECT_COLOR_BIT,0,1,0,1};
    
    for ( const VkImage & swapchainImage : images )
    {
      VkImageViewCreateInfo createInfo
      {
          .sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
          .image    = swapchainImage,
          .viewType = VK_IMAGE_VIEW_TYPE_2D,
          .format   = extent.format,
          .subresourceRange=subresourceRange,
      };

      imageViews[i]=doPointerAlloc5<VkImageView>(&createInfo, vkCreateImageView);
      
      i++;
    }
    return imageViews;
  }


auto SwapChain::handleSwapChainCapabilities() -> SwapchainCapabilities
{
      VkSurfaceCapabilitiesKHR capabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(tmpPhysDevice_, tmpSurface_, &capabilities );
  printf("%s, %u\n", "maxImageCount", capabilities.maxImageCount);
  printf("%s, %u\n", "supportedUsageFlags", capabilities.supportedUsageFlags);
  printf("minExtent:Width, %i %i\n",capabilities.minImageExtent.width, capabilities.minImageExtent.height);
  printf("maxExtent:Width, %i %i\n",capabilities.maxImageExtent.width, capabilities.maxImageExtent.height);
  //std::cout <<"maxExtent"<< capabilities.maxImageExtent<<"\n";
  return SwapchainCapabilities{Frames, VK_FORMAT_B8G8R8A8_SRGB, capabilities.currentExtent, capabilities.supportedUsageFlags};
}

void getFormats(VkPhysicalDevice physDevm, VkSurfaceKHR surface, uint32_t& count, VkSurfaceFormatKHR *)
{
   vkGetPhysicalDeviceSurfaceFormatsKHR(physDevm, surface, &count, nullptr );
}

auto SwapChain::setupImageFormats() -> VkSurfaceFormatKHR
{
   
    uint32_t surfaceFormatCount;
    uint32_t presentModeCount;
  
    getFormats(tmpPhysDevice_, tmpSurface_, surfaceFormatCount, nullptr );
    vkGetPhysicalDeviceSurfacePresentModesKHR(tmpPhysDevice_, tmpSurface_, &presentModeCount, nullptr );
    
    std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
    std::vector<VkPresentModeKHR> presentModes(presentModeCount);
    
    getFormats(tmpPhysDevice_, tmpSurface_, surfaceFormatCount, surfaceFormats.data() );
    vkGetPhysicalDeviceSurfacePresentModesKHR(tmpPhysDevice_, tmpSurface_, &presentModeCount, presentModes.data() );

    

    VkSurfaceFormatKHR   swapChainImageFormat{VK_FORMAT_UNDEFINED, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};

    for ( const VkSurfaceFormatKHR & surfaceFormat1 : surfaceFormats )
    {
        swapChainImageFormat= (surfaceFormat1.format != VK_FORMAT_B8G8R8A8_SRGB)?swapChainImageFormat:surfaceFormat1;
        if(swapChainImageFormat.format!=VK_FORMAT_UNDEFINED) break;
        
    }
    
    
    for ( const VkPresentModeKHR & presentMode1 : presentModes )
    {
        presentMode = (presentMode1  == VK_PRESENT_MODE_IMMEDIATE_KHR)? VK_PRESENT_MODE_IMMEDIATE_KHR : VK_PRESENT_MODE_FIFO_KHR;
        if(presentMode==VK_PRESENT_MODE_IMMEDIATE_KHR) break;
    }
       
    
    return swapChainImageFormat;
}

auto SwapChain::createSwapChain()->VkSwapchainKHR
{
    printf("%s %i\n","ImageCount: ", Frames);
    
  constexpr uint32_t a = 2;
    const VkSwapchainCreateInfoKHR createInfo{

      .sType   = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .pNext   = nullptr,
      .surface = tmpSurface_,

  
      .minImageCount    = Frames,
      .imageFormat      = extent.format,
      .imageColorSpace  = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
      .imageExtent      = extent.currentExtent,
      .imageArrayLayers = 1,
      .imageUsage       = VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_STORAGE_BIT,

      .imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE, //Is concurrent even needed in many cases...
      .queueFamilyIndexCount = 0,
      .pQueueFamilyIndices   = &a,
      

      .preTransform   = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
      .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
      .presentMode    = VK_PRESENT_MODE_IMMEDIATE_KHR,
      .clipped        = true,

      .oldSwapchain = VK_NULL_HANDLE
    };
   
    return doPointerAlloc5<VkSwapchainKHR>(&createInfo, vkCreateSwapchainKHR);
}

// auto SwapChain::createRenderPass(VkImageLayout initial, bool load) -> VkRenderPass
// {

//    printf( "Creating RenderPass\n");
//   VkAttachmentDescription colorAttachment
//   {
//     .format         = VK_FORMAT_B8G8R8A8_SRGB,  // SwapChainSupportDetails::swapChainImageFormat,
//     .samples        = VK_SAMPLE_COUNT_1_BIT,
//     .loadOp         = VK_ATTACHMENT_LOAD_OP_NONE_EXT,
//     .storeOp        = VK_ATTACHMENT_STORE_OP_NONE, //Interestign Bugs: VK_ATTACHMENT_STORE_OP_STORE_DONT_CARE
//     .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_NONE_EXT,
//     .stencilStoreOp = VK_ATTACHMENT_STORE_OP_NONE,
//     .initialLayout  = initial,
//     .finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
//   };
//   VkAttachmentReference colorAttachmentRef{0, VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL};
//   VkSubpassDescription  subpass{ .pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS,
//                                                   .inputAttachmentCount = 1,
//                                                   .pInputAttachments    = &colorAttachmentRef };

 

//    VkRenderPassCreateInfo vkRenderPassCreateInfo1
//    {
//       .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
//       .attachmentCount = 1,
//       .pAttachments    = &colorAttachment,
//       .subpassCount    = 1,
//       .pSubpasses      = &subpass,
//    };
 
//   return doPointerAlloc5<VkRenderPass>(&vkRenderPassCreateInfo1, vkCreateRenderPass);
// }


  auto SwapChain::createFramebuffers() -> VkFramebuffer
  {
        printf("Creating FrameBuffers\n");


    constexpr auto format = VK_FORMAT_B8G8R8A8_SRGB;
    VkFramebufferAttachmentImageInfo FramebufferAttachmentImage
    {
      .sType  = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO,
      .usage  = VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_STORAGE_BIT, //Nvidia Driver bug with Usages/Varients is now fixed in an eailer 473.** Driver Branch and does/no longer needs an offset tp be corrected manually
      .width  = width,
      .height = height,
      .layerCount=1,
      .viewFormatCount=1,
      .pViewFormats=&extent.format
    };


    VkFramebufferAttachmentsCreateInfo FramebufferAttachments
    {
      .sType=VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO,
      .attachmentImageInfoCount=1,
      .pAttachmentImageInfos=&FramebufferAttachmentImage,
    };
    
    VkFramebufferCreateInfo framebufferCreateInfo
    {
          .sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
          .pNext                   = &FramebufferAttachments,
          .flags                   = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT,
          // .renderPass              = renderPass,
          // .attachmentCount         = 1,
          .pAttachments            = nullptr,
          .width                   = width,
          .height                  = height,
          .layers                  = 1,
    };
      
    return doPointerAlloc5<VkFramebuffer>(&framebufferCreateInfo, vkCreateFramebuffer);;
    
  

}
