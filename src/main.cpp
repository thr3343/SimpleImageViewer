
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
#include "SPIRVUtil.hpp"



namespace
{

    const Vkbase vkbase;
    const Tmp tmp{vkbase.instance, vkbase.device, vkbase.physDevice, vkbase.surface};
    const SwapChain swapChain{tmp};
    const VkCommSet commSet{tmp, vkbase.TransferQueue.queuefamilyVarient};
    const MemSys2 MemSys2{vkbase.vkVer, tmp, vkbase.TransferQueue};
    
    const ImgLoader imgLoader{vkbase.PresentQueue, MemSys2};
    const renderer2 R2{tmp};
   
}  // namespace
uint32_t i;
uint32_t tmSecs;

[[gnu::pure]] auto main() -> int
{
    // vmaImage defImg=imgLoader.allocImg();

    // imgLoader.vkRecImg(defImg.img, renderer2::currentFrame, vkbase.GraphicsQueue);

    SPIRVUtil::loadShader();
    commSet.beginSingleTimeCommands();
    imgLoader.transitionImageLayout(commSet.commandBuffer, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, imgLoader.vmaImg.img);
    commSet.endSingleTimeCommands(vkbase.TransferQueue.queue, true);
    while(IsWindow(vkbase.window))
    {
        static LPMSG msg;
        static DWORD prevTime;

        const auto x = clock();

        
          
       
        PeekMessageA(msg, vkbase.window, WM_KEYFIRST, WM_MOVING, PM_REMOVE);
       
        chkTst(vkWaitForFences(vkbase.device, 1, &R2.fence[renderer2::currentFrame], false, -1));
        imgLoader.copyImage2Image(imgLoader.vmaImg, imgLoader.commandBuffers[renderer2::currentFrame], swapChain.image[renderer2::imgIndx]);
        R2.drawFrame({imgLoader.commandBuffers[renderer2::currentFrame]});
        

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

void renderer2::drawFrame(std::initializer_list<VkCommandBuffer> commandBuffer) const noexcept
{

  chkTst(vkWaitForFences(vkbase.device, 1, &R2.fence2[renderer2::imgIndx], false, -1));
  vkResetFences(vkbase.device, 1, &R2.fence2[renderer2::imgIndx]);
  chkTst(vkAcquireNextImageKHR( vkbase.device, swapChain.swapchain, -1, nullptr, fence2[imgIndx], reinterpret_cast<uint32_t*>(&imgIndx) ));
  
  constexpr VkPipelineStageFlags t=VK_PIPELINE_STAGE_TRANSFER_BIT;
      const VkSubmitInfo info
      {
              .sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                .waitSemaphoreCount=1,
                .pWaitSemaphores=&PresentSemaphore[currentFrame],
              .pWaitDstStageMask  = &t,
              .commandBufferCount = 1,
              .pCommandBuffers= commandBuffer.begin(),
              .signalSemaphoreCount=1,
              .pSignalSemaphores=&PresentSemaphore[currentFrame]
      };

 vkResetFences(vkbase.device, 1, &R2.fence[renderer2::imgIndx]);
    chkTst(vkQueueSubmit( vkbase.PresentQueue.queue, 1, &info, fence[imgIndx]));
 
  
    const VkPresentInfoKHR VkPresentInfoKHR1{ .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                                                    .pWaitSemaphores=&PresentSemaphore[currentFrame],
                                                                    .swapchainCount = 1,
                                                                    .pSwapchains    = &swapChain.swapchain,
                                                                    .pImageIndices  = reinterpret_cast<uint32_t*>(&imgIndx),
                                                                    .pResults       = nullptr };




//   chkTst(vkWaitForFences(vkbase.device, 1, &fence[imgIndx], false, -1));
  
  currentFrame=++currentFrame%Frames;
  chkTst(vkQueuePresentKHR( vkbase.PresentQueue.queue, &VkPresentInfoKHR1 ));

}
