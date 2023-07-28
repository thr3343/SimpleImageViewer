#include "Vkbase.hpp"
#include <array>

#include <cstdint>
#include <fmt/core.h>

#include <vector>
#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_win32.h>

constexpr bool DEBUG = false;

constexpr auto *validationLayers = "VK_LAYER_KHRONOS_validation";
constexpr auto extensions       = std::to_array({ VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME}); 

constexpr auto valdFeatures     = std::to_array({ VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT, VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT});

[[nodiscard, gnu::const]] auto getVer()  noexcept -> uint32_t
{
        fmt::println("Get vkVer!");
        uint32_t a;
        vkEnumerateInstanceVersion(&a);
        return a;
}  

[[nodiscard, gnu::const]] auto createInstance() -> VkInstance
{
        fmt::println("Create Instance!");

        constexpr VkValidationFeaturesEXT  extValidationFeatures {
                VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
                nullptr,
                valdFeatures.size(),
                valdFeatures.begin(),
        };
        
        const VkApplicationInfo vkApplInfo {
                VK_STRUCTURE_TYPE_APPLICATION_INFO,
                nullptr,
                "SimpleImageView",
                vkVersion,
                "No Engine",
                vkVersion,
                vkVersion
        };
  
        VkInstanceCreateInfo InstCreateInfo {
                .sType                          = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                .pNext                          = DEBUG ? &extValidationFeatures : nullptr,
                .pApplicationInfo               = &vkApplInfo,
                .enabledLayerCount              = DEBUG ? 1u : 0u,
                .ppEnabledLayerNames            = DEBUG ? &validationLayers : nullptr,
                .enabledExtensionCount          = extensions.size(),
                .ppEnabledExtensionNames        = extensions.begin(),
        };

        VkInstance vki;
        vkCreateInstance(&InstCreateInfo, nullptr, &vki);
        return vki;
}
    
//Only the Compute queue is used currently as only the compute pipeline is needed atm.
struct QueueFamilyVarients
{
        uint32_t computePresentFamily;
};

auto getQueueFamilies(VkPhysicalDevice physDevice) -> std::vector<VkQueueFamilyProperties>
{
        uint32_t famQueueCount;
        vkGetPhysicalDeviceQueueFamilyProperties(physDevice, &famQueueCount, nullptr);
        std::vector<VkQueueFamilyProperties> availableQueues(famQueueCount);

        vkGetPhysicalDeviceQueueFamilyProperties(physDevice, &famQueueCount, availableQueues.data());
        return availableQueues;
}

auto determineQueueFamilies(VkPhysicalDevice physDevice) -> uint32_t
{
        
        const auto availableQueues=getQueueFamilies(physDevice);
        //Fallback if onyl one queue is available:
        if(availableQueues.size()==1) return 0;
        uint32_t i=0;
        for(const auto& QueueInfo : availableQueues)
        {
                const bool hasCompute = (QueueInfo.queueFlags&VK_QUEUE_COMPUTE_BIT);
                const bool hasGraphics = (QueueInfo.queueFlags&VK_QUEUE_GRAPHICS_BIT);
                //Try to use the Dedicated Compute Queue if Available - Also Compute Support also (typically almost Always) implies Present Support as well, and therefore does not need to be explicitly checked
                if(hasCompute&~hasGraphics)
                {
                        fmt::println("Using Queue Family: {}", i);
                        return i;
                }
                i++;
        }
        fmt::println("Failed Queue Enumeration!");
        exit(1);



}





const VkInstance instance = createInstance();

auto getPhyDevProps(VkPhysicalDevice physDevice) -> VkPhysicalDeviceProperties
{
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(physDevice, &deviceProperties);
        return deviceProperties;
}



auto createPhysDevice() -> VkPhysicalDevice
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
auto createDevice() -> GPUDevice
{
        fmt::println("Creating GPUDevice!");

  const auto physDevice=createPhysDevice();
       const uint32_t computeQueueFamily = determineQueueFamilies(physDevice);
       constexpr uint32_t graphicsQueueFamily =0 ; //Gra[hcis Family is almost always Zero]. Regardless of the Platform + Arch
  
  

        constexpr float priority = 1.0f;
 
        const auto deviceQueueCreateInfos = std::to_array<VkDeviceQueueCreateInfo>( 
        {{
                VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                nullptr,
                0,
                graphicsQueueFamily,
                1,
                &priority,
        },{
                VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                nullptr,
                0,
                computeQueueFamily,
                1,
                &priority,
        }});


        VkPhysicalDeviceVulkan12Features deviceVulkan12Features{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES};
        VkPhysicalDeviceFeatures2 deviceFeatures2 = {VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, &deviceVulkan12Features};


        vkGetPhysicalDeviceFeatures2( physDevice, &deviceFeatures2 );
        deviceVulkan12Features.imagelessFramebuffer=true;

        
        constexpr auto * deviceExtensions = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

        const VkDeviceCreateInfo deviceCreateInfo 
        {
                .sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                .pNext=&deviceVulkan12Features,
                // .flags=0,
                .queueCreateInfoCount=deviceQueueCreateInfos.size(),
                .pQueueCreateInfos=deviceQueueCreateInfos.data(),
                // .enabledLayerCount=1,
                .ppEnabledLayerNames= DEBUG  ? &validationLayers : nullptr,
                .enabledExtensionCount= 1,
                .ppEnabledExtensionNames=&deviceExtensions,
                .pEnabledFeatures= &deviceFeatures2.features

        };




  VkDevice device;

  vkCreateDevice(physDevice, &deviceCreateInfo, nullptr, &device);
 
    VkQueue GraphicsQueue;
        vkGetDeviceQueue(device, graphicsQueueFamily, 0, &GraphicsQueue );
    VkQueue ComputeQueue;
        vkGetDeviceQueue(device, computeQueueFamily, 0, &ComputeQueue );
  //Compute + Present Performance regresses when enabling Graphics Queue, Possibly either due to Archietcure Quirks (i.e. Pascall GPU) and/or Sync related

  return {device, {ComputeQueue, computeQueueFamily}, {GraphicsQueue, graphicsQueueFamily}, instance, physDevice};
        
}

/*  auto Vkbase::getQueue(uint32_t QI) -> DiscreteQueue
 {
        
        VkQueue GraphicsQueue;
        vkGetDeviceQueue(device.device, QI, 0, &GraphicsQueue );
        return {GraphicsQueue, QI};
 } */
