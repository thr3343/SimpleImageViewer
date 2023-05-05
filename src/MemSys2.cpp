#include "MemSys2.hpp"
#include "vk_mem_alloc.h"
#include <cstdint>
#include <cassert>
#include <vulkan/vulkan_core.h>


auto MemSys2::setupAlloc(uint32_t vkVer) const -> VmaAllocator
{
    VmaAllocatorCreateInfo allocatorCreateInfo
    {
        .physicalDevice=physDevice,
        .device=device,
        .instance=instance,
        .vulkanApiVersion=vkVer
    };
    VmaAllocator allocator;
    vmaCreateAllocator(&allocatorCreateInfo, &allocator);
    return allocator;
}

auto MemSys2::allocBuff(VkDeviceSize size, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags properties, bool host) const -> vmaBuffer
{

    VkBufferCreateInfo VkBufferCreateInfo
    {
      .sType=VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size=size,
      .usage=usageFlags,
      .sharingMode=VK_SHARING_MODE_EXCLUSIVE,
      .queueFamilyIndexCount=1,
      .pQueueFamilyIndices=&q.queuefamilyVarient,
    };
  // VmaAllocation vmaAllocation;
    VmaAllocationCreateInfo VmaAllocationCreateInfo
    {
      .flags=static_cast<VmaAllocationCreateFlags>((!host?VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT:VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT|VMA_ALLOCATION_CREATE_HOST_ACCESS_ALLOW_TRANSFER_INSTEAD_BIT)),
      .usage=!host?VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE:VMA_MEMORY_USAGE_AUTO_PREFER_HOST,
      .requiredFlags=properties,
      .memoryTypeBits=0,
      .pool=nullptr
    };
    VkBuffer b;
    VmaAllocation alloc;
    vmaCreateBuffer(a, &VkBufferCreateInfo, &VmaAllocationCreateInfo, &b, &alloc, nullptr);
    return {b, alloc, size, usageFlags};
}

auto determineSize(VkExtent2D extent, VkFormat fmt) -> uint32_t
{
    uint32_t byteSize;
    switch(fmt)
    {
      case VK_FORMAT_B8G8R8A8_UINT: byteSize=4; break;
      case VK_FORMAT_B8G8R8_UINT: byteSize=3; break;
      default: byteSize=4;
    };
    return byteSize*extent.width*extent.height;
}

auto MemSys2::allocImg(VkExtent2D extent, VkFormat format, VkImageUsageFlags usage, VkImageView view) const -> vmaImage
{


    const uint32_t size = determineSize(extent, format);

    VkImageCreateInfo bufferCreateInfo
    {
        .sType=VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .imageType=VK_IMAGE_TYPE_2D,
        .format=format,
        .extent={extent.width, extent.height, 1}, //Always use Depth 1
        .mipLevels=1,
        .arrayLayers=1,
        .samples=VK_SAMPLE_COUNT_1_BIT,
        .tiling=VK_IMAGE_TILING_OPTIMAL,
        .usage=usage,
        .sharingMode=VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount=1,
        .pQueueFamilyIndices=&q.queuefamilyVarient,
        .initialLayout=VK_IMAGE_LAYOUT_UNDEFINED,

    };

   	constexpr VmaAllocationCreateInfo dimg_allocinfo = 
    {
      .flags=VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT,
      .usage=VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE,
      .memoryTypeBits=0,
      .pool=nullptr
    };

    VkImage img;
    VmaAllocation alloc;
    vmaCreateImage(a, &bufferCreateInfo, &dimg_allocinfo, &img, &alloc, nullptr);
    return {img, {extent.width, extent.height}, size, usage, VK_IMAGE_LAYOUT_UNDEFINED, alloc, VK_FORMAT_B8G8R8A8_UINT,view};
}