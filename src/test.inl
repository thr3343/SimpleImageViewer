

#include "21_shader_ubo.frag.inl"
#include "21_shader_ubo.vert.inl"
#include "shader_tempTst.vert.inl"
#include "shader_tempTst.frag.inl"
#include <vulkan/vulkan_core.h>




//ShaderSPIRVUtils(): FragMod(Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &VsMCI2, "vkCreateShaderModule" )), VertMod(Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &VsMCI, "vkCreateShaderModule" )) {};

 static constexpr VkShaderModuleCreateInfo VsMCI = {

    .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .pNext    = VK_NULL_HANDLE,
    .codeSize = sizeof(vert),
    .pCode    = vert.data(),
  };

  static constexpr VkShaderModuleCreateInfo VsMCI2 = {

    .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .pNext    = VK_NULL_HANDLE,
    .codeSize = sizeof(frag),
    .pCode    = frag.data(),
  };  
  
  static constexpr VkShaderModuleCreateInfo VsMCI3temp = {

    .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .pNext    = VK_NULL_HANDLE,
    .codeSize = sizeof(vert2),
    .pCode    = vert2.data(),
  };
  
  static constexpr VkShaderModuleCreateInfo VsMCI4temp = {

    .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .pNext    = VK_NULL_HANDLE,
    .codeSize = sizeof(frag2),
    .pCode    = frag2.data(),
  };
