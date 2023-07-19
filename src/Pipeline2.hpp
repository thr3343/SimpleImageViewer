
#include "Defs.tpp"
#include "Vkbase.hpp"
#include "test.inl"
#include <array>
#include <vulkan/vulkan_core.h>



 static constexpr uint8_t OFFSETOF_COLOR = 3 * sizeof( float );
  static constexpr uint8_t OFFSET_POS     = 0;



constexpr std::array<VkShaderModuleCreateInfo, 2> shaderStages2{VsMCI3temp, VsMCI4temp};

struct [[clang::trivial_abi]] Pipeline2:GPUDevice
{
     VkPipelineLayout vkLayout=genLayout();
     VkPipeline pipeline;
     VkCommandPool commandPool=genCommPool();
     std::array<VkCommandBuffer, Frames>commandBuffer=doGenCommnd(commandPool);
     explicit Pipeline2(uint32_t width, uint32_t height, GPUDevice gpuDevice, VkRenderPass renderPass): 
            pipeline(genPipeline(width, height, renderPass, VK_CULL_MODE_NONE, -1)), 
            GPUDevice{gpuDevice} 
     {};

     
    constexpr auto genPipeline(uint32_t, uint32_t, VkRenderPass, VkCullModeFlagBits, int32_t) const -> VkPipeline;
    void genCommBuffers();
   [[nodiscard]] auto genCommPool() const -> VkCommandPool;
   [[nodiscard]] auto doGenCommnd(VkCommandPool) const -> std::array<VkCommandBuffer, Frames>;
   [[nodiscard]] auto genLayout() const -> VkPipelineLayout;
   [[nodiscard]] constexpr auto genShaderPiplineStage(VkShaderModuleCreateInfo, VkShaderStageFlagBits) const -> VkPipelineShaderStageCreateInfo;
} __attribute__((aligned(128)));

constexpr auto Pipeline2::genShaderPiplineStage(VkShaderModuleCreateInfo a, VkShaderStageFlagBits stageFlag) const -> VkPipelineShaderStageCreateInfo
    {
      
        
        return {
          .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
          .stage  = stageFlag,
          .module = doPointerAllocX2<VkShaderModule>( &a),
          .pName  = "main",

        };
    }




constexpr auto Pipeline2::genPipeline(uint32_t width, uint32_t height, VkRenderPass renderPass, VkCullModeFlagBits cullMode, int32_t baseIndex) const -> VkPipeline
{
    // Thankfully Dont; need to worry about compiling the Shader Files AnyMore due
  // to teh ability to premptively use the SPRI-V Compielr (e.g.GLSLC) prior to compile time...
  // std::cout << ( "Setting up PipeLine" ) << "\n";

  const VkPipelineShaderStageCreateInfo vertexStage = genShaderPiplineStage(shaderStages2[0], VK_SHADER_STAGE_VERTEX_BIT);
  const VkPipelineShaderStageCreateInfo fragStage = genShaderPiplineStage(shaderStages2[1], VK_SHADER_STAGE_FRAGMENT_BIT);
  
  const auto shaderStages = std::to_array({fragStage, vertexStage});

  //  constexpr VkVertexInputBindingDescription VxL{ 0, ( 24 ), VK_VERTEX_INPUT_RATE_VERTEX };

  //  constexpr auto attributeDescriptions = std::to_array<VkVertexInputAttributeDescription>({
  //     { .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = OFFSET_POS },
  //   { .location = 2, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = OFFSETOF_COLOR },
  //   // { .location = 3, .binding = 0, .format = VK_FORMAT_R32G32_SFLOAT, .offset = 0 },
  //   // { .location = 4, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = sizeof(float) * 2}
  // });

    VkPipelineVertexInputStateCreateInfo vkPipelineVertexInputStateCreateInfo {
    .sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    .vertexBindingDescriptionCount   = 0,
    .pVertexBindingDescriptions      = nullptr,
    .vertexAttributeDescriptionCount = 0,
    .pVertexAttributeDescriptions    = nullptr
  };

   constexpr VkPipelineInputAssemblyStateCreateInfo inputAssembly { .sType    = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
                                                                            .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
                                                                            .primitiveRestartEnable = VK_FALSE };
const VkViewport vkViewport{ .x = 0.0F, .y = 0.0F, .width = static_cast<float>(width), .height = static_cast<float>(height), .minDepth = 0.0F, .maxDepth = 1.0F };

const VkRect2D scissor{ .offset { 0, 0 }, .extent{ width, height } };

  const VkPipelineViewportStateCreateInfo vkViewPortState {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, .viewportCount = 1, .pViewports = &vkViewport, .scissorCount = 1, .pScissors = &scissor
  };

  const VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization {
    .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
    .depthClampEnable        = VK_FALSE,
    .rasterizerDiscardEnable = VK_FALSE,
    .polygonMode             = VK_POLYGON_MODE_FILL,
    .cullMode                = cullMode,  // WARNING: VERY IMPORTANT!:
                                                       // Make sure the culling direction is correct
                                                       // as it applies even to 2DVecs/Fixed
                                                       // Function Runtime/Evaluated Shaders
                                                       // with no transforms and with fixed
                                                       // Const/Pre-Determined Runtime
                                                       // Variables
    .frontFace       = VK_FRONT_FACE_COUNTER_CLOCKWISE,
    .depthBiasEnable = VK_FALSE,
    .lineWidth       = 1.0F,
  };

  constexpr VkPipelineMultisampleStateCreateInfo multisampling { .sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
                                                                   .rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT,
                                                                   .sampleShadingEnable   = VK_FALSE,
                                                                   .minSampleShading      = 1.0F,
                                                                   .pSampleMask           = VK_NULL_HANDLE,
                                                                   .alphaToCoverageEnable = VK_FALSE,
                                                                   .alphaToOneEnable      = VK_FALSE };

  constexpr VkPipelineDepthStencilStateCreateInfo depthStencil {
    .sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
    .depthTestEnable       = VK_FALSE,
    .depthWriteEnable      = VK_FALSE,
    .depthCompareOp        = VK_COMPARE_OP_EQUAL,
    .depthBoundsTestEnable = VK_FALSE,
    .stencilTestEnable     = VK_FALSE,
  };
   constexpr VkPipelineColorBlendAttachmentState colorBlendAttachment {
    .blendEnable    = VK_FALSE,
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,

  };
   VkPipelineColorBlendStateCreateInfo colorBlending {
    .sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
    .logicOpEnable   = VK_FALSE,
    .logicOp         = VK_LOGIC_OP_COPY,
    .attachmentCount = 1,
    .pAttachments    = &colorBlendAttachment,

  };


  const VkGraphicsPipelineCreateInfo pipelineInfo{ .sType      = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
                                                   .stageCount = shaderStages.size(),
                                                   .pStages    = shaderStages.data(),
                                                   // .pNext=VK_NULL_HANDLE,
                                                   .pVertexInputState   = &vkPipelineVertexInputStateCreateInfo,
                                                   .pInputAssemblyState = &inputAssembly,
                                                   .pViewportState      = &vkViewPortState,
                                                   .pRasterizationState = &VkPipeLineRasterization,
                                                   .pMultisampleState   = &multisampling,
                                                   .pDepthStencilState  = &depthStencil,
                                                   .pColorBlendState    = &colorBlending,
                                                   .layout              = vkLayout,
                                                   .renderPass          = renderPass,
                                                   .basePipelineIndex=baseIndex};

  return doPointerAllocX<VkPipeline>(&pipelineInfo);
}