#include "Vkbase.hpp"
#include <array>

#include <cstdint>
#include <fmt/core.h>

#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_win32.h>

constexpr bool ENABLE_VALIDATION_LAYERS = false;

constexpr auto *validationLayers = "VK_LAYER_KHRONOS_validation";
constexpr auto extensions       = std::to_array({ VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME}); 

constexpr auto valdFeatures     = std::to_array({ VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT, VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT});

auto Vkbase::getVer()  const noexcept -> uint32_t
{
        uint32_t a;
        vkEnumerateInstanceVersion(&a);
        return a;
}  

    



auto Vkbase::createInstance() -> VkInstance
{
        

        constexpr VkValidationFeaturesEXT  extValidationFeatures
        {
                VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
                nullptr,
                valdFeatures.size(),
                valdFeatures.begin(),
        };
        
    
        const VkApplicationInfo vkApplInfo 
        {
                VK_STRUCTURE_TYPE_APPLICATION_INFO,
                VK_NULL_HANDLE,
                "SimpleImageView",
                vkVer,
                "No Engine",
                vkVer,
                vkVer
        };
        
        
  
        
  
        const VkInstanceCreateInfo InstCreateInfo 
        {
                .sType                          = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                .pNext                          = ENABLE_VALIDATION_LAYERS ? &extValidationFeatures : nullptr,
                .pApplicationInfo               = &vkApplInfo,
                .enabledLayerCount              = ENABLE_VALIDATION_LAYERS ? 1u : 0u,
                .ppEnabledLayerNames            = ENABLE_VALIDATION_LAYERS ? &validationLayers : nullptr,
                .enabledExtensionCount          = static_cast<uint32_t>(( extensions.size() )),
                .ppEnabledExtensionNames        = extensions.begin(),

        };

        //auto vki = nullptr;
        VkInstance vki;
        vkCreateInstance(&InstCreateInfo, nullptr, &vki);

        return vki;
}

auto Vkbase::createSurface()  -> VkSurfaceKHR
{
      
    VkSurfaceKHR surface;
    fmt::print( "Creating Surface\n");;
  VkWin32SurfaceCreateInfoKHR createSurfaceInfo = {
        .sType                       = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
        .hwnd                        = hwnd,
        .hinstance                   = inst,
        .pNext                       = VK_NULL_HANDLE
};
  vkCreateWin32SurfaceKHR( instance, &createSurfaceInfo, nullptr, &surface);
  return surface;
}


void Vkbase::clean()
{
        fmt::print("Clean!\n");
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
}

auto getPhyDevProps(VkPhysicalDevice physDevice) -> VkPhysicalDeviceProperties
{
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(physDevice, &deviceProperties);
        return deviceProperties;
}



auto Vkbase::createPhysDevice() -> VkPhysicalDevice
{
  fmt::print( "Picking Physical Device\n");
   uint32_t deviceCount;
   vkEnumeratePhysicalDevices( instance, &deviceCount, nullptr ) ;

 
   std::vector<VkPhysicalDevice> ppPhysicalDevicesdeviceCount(deviceCount);

   fmt::print("Enumerate Physical Device\n");
   vkEnumeratePhysicalDevices( instance, &deviceCount, ppPhysicalDevicesdeviceCount.data() );

for(VkPhysicalDevice physDevs : ppPhysicalDevicesdeviceCount)
{
        if(getPhyDevProps(physDevs).deviceType==VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) return physDevs;
}
  return ppPhysicalDevicesdeviceCount[0];
 
}


// auto enumerateQueues() -> std::initializer_list<VkQueue>
// {
        
// }
auto Vkbase::createDevice() -> VkDevice
{
 // fmt::print( "Creating Device\n");

  //enumerateQueues();

  
  uint32_t pQueueFamilyPropertyCount;
  vkGetPhysicalDeviceQueueFamilyProperties( physDevice, &pQueueFamilyPropertyCount, VK_NULL_HANDLE );

  
  

 constexpr float priority = 1.0f;
//  const VkDeviceQueueCreateInfo deviceQueueCreateInfo 
//  {
//         VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
//         nullptr,
//         0,
//         0,
//         1,
//         &priority,
//  };
//  const VkDeviceQueueCreateInfo deviceQueueCreateInfo2 
//  {
//         VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
//         nullptr,
//         0,
//         1,
//         1,
//         &priority,
//  }; 
 VkDeviceQueueCreateInfo deviceQueueCreateInfo3 
 {
        VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        nullptr,
        0,
        2,
        1,
        &priority,
 };
 auto queueSetInitList ={deviceQueueCreateInfo3};
  VkPhysicalDeviceVulkan13Features vk13F
  {
    .sType=VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
    .pNext=nullptr,
    .synchronization2=true,
  };


   VkPhysicalDeviceVulkan12Features deviceVulkan12Features = {
    .sType                           = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
    .pNext                           = &vk13F,
    .descriptorBindingPartiallyBound = true,
    .imagelessFramebuffer            = true,

  };

 

  VkPhysicalDeviceFeatures2 deviceFeatures2 = { .sType    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
                                                .pNext    = &deviceVulkan12Features,
                                                /* .features = deviceFeatures */ };


  vkGetPhysicalDeviceFeatures2( physDevice, &deviceFeatures2 );

        constexpr auto * deviceExtensions = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

        // constexpr uint32_t extCount= extensions.size();
  const VkDeviceCreateInfo deviceCreateInfo 
  {
        .sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext=&deviceFeatures2,
        // .flags=0,
        .queueCreateInfoCount=1,
        .pQueueCreateInfos=queueSetInitList.begin(),
        // .enabledLayerCount=1,
        .ppEnabledLayerNames= ENABLE_VALIDATION_LAYERS  ? &validationLayers : nullptr,
        .enabledExtensionCount= 1,
        .ppEnabledExtensionNames=&deviceExtensions,
        .pEnabledFeatures= nullptr

  };




  VkDevice device;

  vkCreateDevice(physDevice, &deviceCreateInfo, nullptr, &device);
 
  
  return device;
        
}

 auto Vkbase::getQueue(uint32_t QI) -> DiscreteQueue
 {
        
        VkQueue GraphicsQueue;
        vkGetDeviceQueue(device, QI, 0, &GraphicsQueue );
        return {GraphicsQueue, QI};
 }
