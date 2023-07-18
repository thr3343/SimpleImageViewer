#include "Pipeline2.hpp"



auto Pipeline2::doGenCommnd(VkCommandPool commandPool) const -> std::array<VkCommandBuffer, Frames>
{
  std::array<VkCommandBuffer, Frames> PreTestBuffer{};
   const VkCommandBufferAllocateInfo allocateInfo{ .sType              =  VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ,
                                                  .commandPool        =  commandPool ,
                                                  .level              =  VK_COMMAND_BUFFER_LEVEL_PRIMARY ,
                                                  .commandBufferCount = Frames};

  vkAllocateCommandBuffers(device, &allocateInfo, PreTestBuffer.data() );
  return PreTestBuffer;
}



auto Pipeline2::genCommPool() const -> VkCommandPool
{
 constexpr VkCommandPoolCreateInfo  poolInfo = {
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .flags=VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
    .queueFamilyIndex = 0,
  };
  return doPointerAlloc5<VkCommandPool>( &poolInfo, vkCreateCommandPool );
 
}


auto Pipeline2::genLayout() const -> VkPipelineLayout
{
  
  static constexpr VkPushConstantRange vkPushConstantRange{
    .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
    .offset     = 0,
    .size       = 32,
  };

  constexpr VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo = { .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                                                                     /*  . setLayoutCount         = 1,
                                                                      .pSetLayouts            = &UniformBufferObject::descriptorSetLayout, */
                                                                      .pushConstantRangeCount = 1,
                                                                      .pPushConstantRanges    = &vkPushConstantRange };

  // std::cout << ( "using pipeLine with Length: " ) << sizeof( SwapChainSupportDetails::swapChainImageViews );
  return doPointerAlloc5<VkPipelineLayout>( &vkPipelineLayoutCreateInfo, vkCreatePipelineLayout);
}