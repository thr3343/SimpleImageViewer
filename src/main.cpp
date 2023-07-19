#include <GLFW/glfw3.h>
#include <ctime>
#include <vulkan/vulkan_core.h>

#include "FrameBuffer.hpp"
#include "Vkbase.hpp"
#include "SwapChain.hpp"
#include "MemSys2.hpp"
#include "ImgLoader.hpp"
#include "defs.tpp"
#include "fakeFBO.hpp"
#include "fmt/core.h"
#include "renderer2.hpp"
#include "Pipeline2.hpp"


constexpr size_t sso_size = std::string{}.capacity();

/*todo(thr3343): 
    Maybe Add Basic (Unit) Testing.....
    *Directory recursion/Recursive Directory Walking...
*/
template<typename type>
[[gnu::const]]  auto fillSet(VkSemaphore a) noexcept -> std::array<type, Frames>
{
    std::array<type, Frames> aa;
    aa.fill(a);
    return aa;
}


namespace
{

     GPUDevice gpuDevice = createDevice();

     SwapChain swapChain{gpuDevice, gpuDevice.computeQueue.queuefamilyVarient};
    const MemSys2 memSys2{vkVer, gpuDevice, gpuDevice.computeQueue};
     
     Framebuffer frameBuffer{swapChain.width, swapChain.height, swapChain.swapChainImages, gpuDevice};
    const Pipeline2 graphicsPipeline{swapChain.width, swapChain.height, gpuDevice, frameBuffer.renderPass};
    // const ComputePipeline computePipeline{memSys2, swapChain};
    const ImgLoader imgLoader{gpuDevice.computeQueue, memSys2};
    const renderer2 R2;

    fakeFBO fakevfbo{graphicsPipeline.pipeline, 
    graphicsPipeline.commandPool,
    frameBuffer.renderPass,
    frameBuffer.frameBuffer, 
    frameBuffer.imageViews,
    graphicsPipeline.vkLayout,
    graphicsPipeline.commandBuffer};


  std::array<VkSemaphore, Frames> FinishedSemaphore=gpuDevice.doSet<VkSemaphore>(vkCreateCSemaphore, vkCreateSemaphore);
  std::array<VkSemaphore, Frames> AvailableSemaphore=gpuDevice.doSet<VkSemaphore>(vkCreateCSemaphore, vkCreateSemaphore);
  std::array<VkFence, Frames> frameFences=gpuDevice.doSet<VkFence>(vkFenceCreateInfo, vkCreateFence);


    bool rSkip=false;
    //const std::array<VkSemaphore, Frames> FinishedSemaphore=fillSet<VkSemaphore>(computePipeline.BGR2RGBSwizzle(imgLoader, device.computeQueue.queue, swapChain.swapChainImages, computePipeline.compSSBO, computePipeline.compSSBODst));
   
}  // namespace
uint32_t i;
uint32_t tmSecs;

   consteval std::string_view minDef(std::string_view a, int ax=16)
   {
        return std::string_view{a.cend()-16, 16};
   }
auto main() -> int
{
  
   fmt::println("sso_size{}", sso_size);

 
    while(!glfwWindowShouldClose(swapChain.window))
    {
        
        static constinit DWORD prevTime;

        const auto x = clock();

        glfwPollEvents(); // PeekMessageA(msg, vkbase.window, WM_KEYFIRST, WM_MOVING, PM_REMOVE);
          vkResetFences(gpuDevice.device, 1, &frameFences[R2.currentFrame]);
        fakevfbo.doCommndRec(swapChain.width, swapChain.height, R2.currentFrame, x);
       
    
        R2.drawFrame({fakevfbo.commandBuffers[R2.currentFrame]});
        

        if(prevTime+CLOCKS_PER_SEC<clock())
        {
            tmSecs++;
            prevTime=x;
            fmt::println("{}",i);
            i=0;
        }

        i++;
    }

    fmt::print("No Window! \n");
    glfwDestroyWindow(swapChain.window);
    // swapChain.~SwapChain();
}

void getFrameBufferSize()
{
        
       
      
        fmt::println("Recreate SwapChain");
        //vkWaitForFences(gpuDevice.device, Frames, frameFences.data(), true, -1);
        vkDeviceWaitIdle(gpuDevice.device);
      
            uint32_t width = 0, height = 0;
            while (width == 0 || height == 0) {
                glfwGetFramebufferSize(swapChain.window, reinterpret_cast<int*>(&width), reinterpret_cast<int*>(&height));
                glfwWaitEvents();
                 fmt::println("FAIL!");
             }
        
           {


                swapChain.swapchain = swapChain.createSwapChain(width, height, 0);
                swapChain.swapChainImages = swapChain.getSwapChainImages(Frames, 0);
                frameBuffer={width, height, frameBuffer.renderPass, swapChain.swapChainImages, gpuDevice};
                
                
                fakevfbo.frameBuffer=frameBuffer.frameBuffer; 
                fakevfbo.imageViews=frameBuffer.imageViews;
            }
           

        //vkResetFences(gpuDevice.device, Frames, frameFences.data());

  rSkip=false;


}

void renderer2::drawFrame(std::initializer_list<VkCommandBuffer> commandBuffer) const noexcept
{

VkResult a = vkAcquireNextImageKHR( gpuDevice.device, swapChain.swapchain, 10000, AvailableSemaphore[currentFrame], nullptr, &imgIndx );
  if(a==VK_ERROR_OUT_OF_DATE_KHR||a==VK_SUBOPTIMAL_KHR || rSkip)
  {
            rSkip=false;
            //chkTst(a);
            getFrameBufferSize();
  }
  else if(a!=VK_SUCCESS&& a!=VK_SUBOPTIMAL_KHR){ chkTst(a);}



  constexpr VkPipelineStageFlags t=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
      const  VkSubmitInfo           info{
              .sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO,
              .waitSemaphoreCount = 1,
              .pWaitSemaphores    = &AvailableSemaphore[currentFrame],
              .pWaitDstStageMask  = &t,
              .commandBufferCount = 1,
              .pCommandBuffers= commandBuffer.begin(),
              .signalSemaphoreCount = 1,
              .pSignalSemaphores = &FinishedSemaphore[currentFrame]
  };
  
  chkTst(vkQueueSubmit(gpuDevice.graphicsQueue.queue, 1, &info, frameFences[currentFrame]));

  const VkPresentInfoKHR VkPresentInfoKHR1 alignas(32)
  { 
    .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
    .swapchainCount = 1,
    .pSwapchains    = &swapChain.swapchain,
    .pImageIndices  = (&imgIndx),
    .pResults       = nullptr,
    .waitSemaphoreCount=1,
    .pWaitSemaphores=&FinishedSemaphore[currentFrame]
  };




    int ax = (vkQueuePresentKHR( gpuDevice.computeQueue.queue, &VkPresentInfoKHR1));
    if(a==VK_ERROR_OUT_OF_DATE_KHR||a==VK_SUBOPTIMAL_KHR || rSkip)
    {
                rSkip=false;
                //chkTst(a);
                getFrameBufferSize();
    }
    else if(a!=VK_SUCCESS&& a!=VK_SUBOPTIMAL_KHR){ chkTst(a);}
   
              chkTst(vkWaitForFences(gpuDevice.device, 1, &frameFences[currentFrame], false, -1));
  currentFrame=++currentFrame%Frames;
}
