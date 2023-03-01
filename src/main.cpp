
#include <cassert>
#include <cstdint>
#include <ctime>

#include "Vkbase.hpp"
#include "SwapChain.hpp"
#include "MemSys2.hpp"
#include "ImgLoader.hpp"
#include "renderer2.hpp"
#include "ComputePipeline.hpp"
#include "vec_u8string_view.hpp"



/*todo(thr3343): 
    Maybe Add Basic (Unit) Testing.....
    *Directory recursion/Recursive Directory Walking...
*/


namespace
{

    const Vkbase vkbase;
    const Tmp tmp{vkbase.instance, vkbase.device, vkbase.physDevice, vkbase.surface};
    const SwapChain swapChain{tmp};
    // const VkCommSet commSet{tmp, vkbase.TransferQueue.queuefamilyVarient};
    const MemSys2 memSys2{vkbase.vkVer, tmp, vkbase.PresentQueue};
     ComputePipeline computePipeline{memSys2, swapChain};
   
    const ImgLoader imgLoader{vkbase.PresentQueue, memSys2};
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

    /*todo(thr3343): 
    Maybe Add Basic (Unit) Testing.....
    *Directory recursion/Recursive Directory Walking...
*/
    vec_u8string_view directoryHandler=vec_u8string_view::initHelper({"testtesttesttesttesttesttesttesttesttest.png"});
    vec_u8string_view directoryHandler2=vec_u8string_view::initHelper({"test.png"});

    printf("%s\n",directoryHandler.getExtensionfromSubString());
    printf("%s\n",directoryHandler==directoryHandler2?"OK":"FAIL!");

    computePipeline.BGR2RGBSwizzle(imgLoader, vkbase.PresentQueue.queue, swapChain.image);
    
    while(!glfwWindowShouldClose(vkbase.window))
    {
        
        static DWORD prevTime;

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

  chkTst(vkWaitForFences(vkbase.device, 1, &R2.fence2[currentFrame], false, -1));

  vkResetFences(vkbase.device, 1, &R2.fence2[currentFrame]);
  
  //TODO(thr3343): Replace fence Setup with Semaphore
  chkTst(vkAcquireNextImageKHR( vkbase.device, swapChain.swapchain, -1, nullptr, fence2[renderer2::currentFrame], &imgIndx ));
  

      
  constexpr VkPresentInfoKHR VkPresentInfoKHR1 alignas(32)
  { 
    .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
    .swapchainCount = 1,
    .pSwapchains    = &swapChain.swapchain,
    .pImageIndices  = (&imgIndx),
    .pResults       = nullptr 
  };


  currentFrame=++currentFrame%Frames;

  chkTst(vkQueuePresentKHR( vkbase.PresentQueue.queue, &VkPresentInfoKHR1 ));

}
