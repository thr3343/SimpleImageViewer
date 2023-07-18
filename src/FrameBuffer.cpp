#include "FrameBuffer.hpp"
#include "fmt/core.h"
#include <cstdint>
#include <vulkan/vulkan_core.h>

auto Framebuffer::createFramebuffers() -> VkFramebuffer
{
        fmt::print("Creating FrameBuffers\n");

    // const VkExtent2D xy{width, height};
    constexpr auto format = VK_FORMAT_B8G8R8A8_SRGB;
    VkFramebufferAttachmentImageInfo FramebufferAttachmentImage
    {
      .sType  = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO,
      .usage  = VK_IMAGE_USAGE_TRANSFER_SRC_BIT|VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
      .width  = width,
      .height = height,
      .layerCount=1,
      .viewFormatCount=1,
      .pViewFormats=&format
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
          .renderPass              = renderPass,
          .attachmentCount            = 1,
          .pAttachments            = nullptr,
          .width                   = width,
          .height                  = height,
          .layers                  = 1,
    };
      
    return doPointerAlloc5<VkFramebuffer>(&framebufferCreateInfo, vkCreateFramebuffer);;
    
  

}



//Posibel BUg fix: Don't use self-reference to the parent Struct vkImage Array and instead just use a passed VkImage paramter so it isn't accidentally Overridden!
  auto Framebuffer::createImageViews(std::array<VkImage, Frames> images) -> std::array<VkImageView, Frames>
  {
    // std::cout << ( "Creating Image Views" ) << "\n";
    int i = 0;
    std::array<VkImageView, Frames> imageViews;
    for ( const VkImage & swapchainImage : images )
    {
      VkImageViewCreateInfo createInfo = {};
      createInfo.sType                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

      createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
      createInfo.format   = VK_FORMAT_B8G8R8A8_SRGB;

      //     createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
      // createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
      // createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
      //     createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

      createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
      createInfo.subresourceRange.baseMipLevel   = 0;
      createInfo.subresourceRange.levelCount     = 1;
      createInfo.subresourceRange.baseArrayLayer = 0;
      createInfo.subresourceRange.layerCount     = 1;

      createInfo.image = swapchainImage;

      imageViews[i]=doPointerAlloc5<VkImageView>(&createInfo, vkCreateImageView);
      i++;
    }
    return imageViews;
  }

//COuld Turn this into an Dedicated Object or even amore complex "Scene" Aggregate"
auto Framebuffer::createRenderPass(VkImageLayout initial, bool load) -> VkRenderPass
{
    // std::cout << ( "Creating RenderPass" ) << "\n";
      static const VkAttachmentDescription colorAttachment{
    .format         = VK_FORMAT_B8G8R8A8_SRGB,  // SwapChainSupportDetails::swapChainImageFormat,
    .samples        = VK_SAMPLE_COUNT_1_BIT,
    .loadOp         = VK_ATTACHMENT_LOAD_OP_NONE_EXT,
    .storeOp        = VK_ATTACHMENT_STORE_OP_NONE, //Interestign Bugs: VK_ATTACHMENT_STORE_OP_STORE_DONT_CARE
    .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
    .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
    .initialLayout  = initial,
    .finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
  };
  static constexpr VkAttachmentReference colorAttachmentRef{ .attachment = 0, .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
  static constexpr VkSubpassDescription  subpass{ .pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS,
                                                  .colorAttachmentCount = 1,
                                                  .pColorAttachments    = &colorAttachmentRef };

                                                  
  static constexpr VkSubpassDependency  VkSubpassDependency
  {
    .srcSubpass=VK_SUBPASS_CONTENTS_INLINE,
    .dstSubpass=VK_SUBPASS_CONTENTS_INLINE,
    .srcStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
    .dstStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
    .srcAccessMask=0,
    .dstAccessMask=VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT

  };

  constexpr VkRenderPassCreateInfo vkRenderPassCreateInfo1 = {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
    //   .flags=VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT,
    .attachmentCount = 1,
    .pAttachments    = &colorAttachment,
    .subpassCount    = 1,
    .pSubpasses      = &subpass,
    // .dependencyCount=1,
    // .pDependencies=&VkSubpassDependency
  };

  return doPointerAlloc5<VkRenderPass>(&vkRenderPassCreateInfo1, vkCreateRenderPass );

}