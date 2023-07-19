#include "fakeFBO.hpp"
#include <cstdint>


using v4 [[gnu::vector_size(16), gnu::aligned(16)]] = float;



void fakeFBO::doCommndRec(uint32_t width, uint32_t height, uint32_t a, clock_t time) const
{

  
      constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags =  VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT };

    const VkRect2D renderArea = { .offset = { 0, 0 }, .extent = {width, height} };


  
  // static constexpr VkDeviceSize offsets[] = { 0 };
  // uint32_t i = 0; 
  const auto at = static_cast<float>(time)/1000;

  const v4 iTime{static_cast<float>(width), static_cast<float>(height), at, sinf(at)};

  /* for(const VkCommandBuffer &commandBuffer : commandBuffers)
  {*/VkRenderPassAttachmentBeginInfo RenderPassAttachments
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO,
    .attachmentCount = 1,
    .pAttachments = &imageViews[a]
  };

  const VkRenderPassBeginInfo renderPassInfo = {
    .sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ,
    .pNext = &RenderPassAttachments,
    .renderPass      = renderPass ,
    .framebuffer =  frameBuffer ,
    .renderArea      = renderArea,
    // .clearValueCount = 1,
    // .pClearValues    = &clearValues2,
  };
  vkBeginCommandBuffer(commandBuffers[a], &beginInfo1 );


    vkCmdBeginRenderPass(commandBuffers[a], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE );

    vkCmdBindPipeline(commandBuffers[a], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeLine );

    vkCmdPushConstants(commandBuffers[a],layout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(v4), &iTime);


    vkCmdDraw( commandBuffers[a], ( 3), 1, 0, 0 );

    vkCmdEndRenderPass( commandBuffers[a] );
    vkEndCommandBuffer( commandBuffers[a]);
    // i++;
  // }
  // return commandBuffer;

}