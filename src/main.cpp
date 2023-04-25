#include <GLFW/glfw3.h>
#include "Vkbase.hpp"
#include "SwapChain.hpp"
#include "MemSys2.hpp"
#include "ImgLoader.hpp"
#include "fmt/core.h"
#include "renderer2.hpp"
#include "ComputePipeline.hpp"


constexpr size_t sso_size = std::string{}.capacity();

/*todo(thr3343): 
    Maybe Add Basic (Unit) Testing.....
    *Directory recursion/Recursive Directory Walking...
*/


namespace
{

    const Vkbase vkbase;
    const Tmp tmp{vkbase.instance, vkbase.device.device, vkbase.physDevice, vkbase.surface};
    const SwapChain swapChain{tmp, vkbase.device.computeQueue.queuefamilyVarient};
    const MemSys2 memSys2{vkbase.vkVer, tmp, vkbase.device.computeQueue};
     
    const ComputePipeline computePipeline{memSys2, swapChain};
    const ImgLoader imgLoader{vkbase.device.computeQueue, memSys2};
    const renderer2 R2{tmp};
   
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

    computePipeline.BGR2RGBSwizzle(imgLoader, vkbase.device.computeQueue.queue, swapChain.swapChainImages);
    
    while(!glfwWindowShouldClose(vkbase.window))
    {
        
        static constinit DWORD prevTime;

        const auto x = clock();

        
          
        glfwPollEvents(); // PeekMessageA(msg, vkbase.window, WM_KEYFIRST, WM_MOVING, PM_REMOVE);
       
    
        R2.drawFrame();
        

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
    glfwDestroyWindow(vkbase.window);
    swapChain.~SwapChain();
    vkbase.~Vkbase();
}

void renderer2::drawFrame() const noexcept
{

  chkTst(vkAcquireNextImageKHR( vkbase.device.device, swapChain.swapchain, 10000, FinishedSemaphore[imgIndx], nullptr, &imgIndx ));
  

      
  const VkPresentInfoKHR VkPresentInfoKHR1 alignas(32)
  { 
    .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
    .swapchainCount = 1,
    .pSwapchains    = &swapChain.swapchain,
    .pImageIndices  = (&imgIndx),
    .pResults       = nullptr,
    .waitSemaphoreCount=1,
    .pWaitSemaphores=&FinishedSemaphore[imgIndx]
  };


  currentFrame=++currentFrame%Frames;

  chkTst(vkQueuePresentKHR( vkbase.device.computeQueue.queue, &VkPresentInfoKHR1 ));

}
