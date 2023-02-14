
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <vulkan/vulkan_core.h>
#include <windef.h>
#include <winuser.h>
#include "VkCtx.hpp"
#include "VkCommSet.hpp"
#include "MemSys2.hpp"
#include "ImgLoader.hpp"
#include "renderer2.hpp"
#include "ComputePipeline.hpp"




namespace
{

    const Vkbase vkbase;
    const Tmp tmp{vkbase.instance, vkbase.device, vkbase.physDevice, vkbase.surface};
    const SwapChain swapChain{tmp};
    // const VkCommSet commSet{tmp, vkbase.TransferQueue.queuefamilyVarient};
    const MemSys2 memSys2{vkbase.vkVer, tmp, vkbase.PresentQueue};
    const ComputePipeline computePipeline{memSys2};
   
    const ImgLoader imgLoader{vkbase.PresentQueue, memSys2};
    const renderer2 R2{tmp};
   
}  // namespace
uint32_t i;
uint32_t tmSecs;



auto main() -> int
{
    computePipeline.BGR2RGBSwizzle(imgLoader, vkbase.PresentQueue.queue, swapChain.image);
    
    while(IsWindow(vkbase.window))
    {
        static LPMSG msg;
        static DWORD prevTime;

        const auto x = clock();

        
          
       
        PeekMessageA(msg, vkbase.window, WM_KEYFIRST, WM_MOVING, PM_REMOVE);
       
        // chkTst(vkWaitForFences(vkbase.device, 1, &R2.fence[renderer2::currentFrame], false, -1));
        R2.drawFrame();
        

        if(prevTime+CLOCKS_PER_SEC<clock())
        {
            tmSecs++;
            prevTime=x;
            printf("%i \n", i);
            i=0;
        }

        i++;
    }

    printf("No Window! \n");

    swapChain.~SwapChain();
    vkbase.~Vkbase();
}

void renderer2::drawFrame() const noexcept
{

  chkTst(vkWaitForFences(vkbase.device, 1, &R2.fence2[currentFrame], false, -1));
  vkResetFences(vkbase.device, 1, &R2.fence2[currentFrame]);
  //TODO(thr3343): Replace fence Setup with Semaphore
  chkTst(vkAcquireNextImageKHR( vkbase.device, swapChain.swapchain, -1, nullptr, fence2[renderer2::currentFrame], reinterpret_cast<uint32_t*>(&imgIndx) ));
  
  constexpr VkPipelineStageFlags t=VK_PIPELINE_STAGE_TRANSFER_BIT;
      // const VkSubmitInfo info
      // {
      //         .sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      //           .waitSemaphoreCount=1,
      //           .pWaitSemaphores=&PresentSemaphore[currentFrame],
      //         .pWaitDstStageMask  = &t,
      //         .commandBufferCount = 1,
      //         .pCommandBuffers= commandBuffer.begin(),
      //         .signalSemaphoreCount=1,
      //         .pSignalSemaphores=&PresentSemaphore[currentFrame]
      // };

//  vkResetFences(vkbase.device, 1, &R2.fence[renderer2::imgIndx]);
    // chkTst(vkQueueSubmit( vkbase.PresentQueue.queue, 1, &info, fence[imgIndx]));
 
  
    const VkPresentInfoKHR VkPresentInfoKHR1{ .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                                                    // .pWaitSemaphores=&PresentSemaphore[currentFrame],
                                                                    .swapchainCount = 1,
                                                                    .pSwapchains    = &swapChain.swapchain,
                                                                    .pImageIndices  = reinterpret_cast<uint32_t*>(&imgIndx),
                                                                    .pResults       = nullptr };




//   chkTst(vkWaitForFences(vkbase.device, 1, &fence[imgIndx], false, -1));
  
  currentFrame=++currentFrame%Frames;
  chkTst(vkQueuePresentKHR( vkbase.PresentQueue.queue, &VkPresentInfoKHR1 ));

}
