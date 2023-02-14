#include "VkCommSet.hpp"


#include <vulkan/vulkan_core.h>

 
void VkCommSet::beginSingleTimeCommands() const
{
     VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags = ( VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) };

                                                
  chkTst(vkBeginCommandBuffer(this->commandBuffer, &beginInfo1));
}
VkCommandBuffer VkCommSet::doGenCommnd(VkCommandPool commandPool)
{
  VkCommandBuffer PreTestBuffer;

   const VkCommandBufferAllocateInfo allocateInfo{ .sType              =  VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ,
                                                  .commandPool        =  commandPool ,
                                                  .level              =  VK_COMMAND_BUFFER_LEVEL_PRIMARY ,
                                                  .commandBufferCount = 1};

  vkAllocateCommandBuffers(tmpDevice_, &allocateInfo, &PreTestBuffer );

  return PreTestBuffer;
}
VkCommandPool VkCommSet::genCommPool(uint32_t QueueFamilyIndex)
{
  VkCommandPoolCreateInfo  poolInfo = {
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .flags=VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
    .queueFamilyIndex = QueueFamilyIndex,
  };
 
  return doPointerAlloc5<VkCommandPool>(&poolInfo, vkCreateCommandPool);
 
}

void VkCommSet::endSingleTimeCommands(VkQueue queue, bool submit, bool wait) const
{
  vkEndCommandBuffer( commandBuffer );
  if(!submit) return;
  const VkSubmitInfo       submitInfo1 = {
          .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, .pNext = VK_NULL_HANDLE, .commandBufferCount = ( 1 ), .pCommandBuffers = &commandBuffer
  };
//   a = ( a ^ 1 );
  vkQueueSubmit( queue, 1, &submitInfo1, VK_NULL_HANDLE );
  if(wait) (vkQueueWaitIdle( queue ));
//   vkResetCommandPool( device, ( commandPool2 ), VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT );
}