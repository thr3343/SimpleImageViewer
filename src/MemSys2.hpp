#pragma once
#include "defs.tpp"
#include "Vkbase.hpp"
#include <cstddef>
#include <cstdint>
#include <vulkan/vulkan_core.h>
 static const constinit void *aData;

constexpr VkImageSubresourceLayers subresource = {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
	    .mipLevel = 0,
	    .baseArrayLayer = 0,
	    .layerCount = 1,
        };
constexpr VkDeviceSize defSize=static_cast<const VkDeviceSize>(width*height)*4Ul;
struct  [[gnu::aligned(32)]] vmaBuffer
{

 constexpr vmaBuffer(VkBuffer buff, VmaAllocation alloc, VkDeviceSize size,
            VkBufferUsageFlags usageFlags)
     noexcept : buff(buff), alloc(alloc), size(size), usageFlags(usageFlags) {}
  VkBuffer buff;
  VkDeviceSize size;
  VmaAllocation alloc;
  VkBufferUsageFlags usageFlags;
  void* aData;
};

struct [[gnu::aligned(32)]] vmaImage
{
    VkImage img; 
    VkExtent2D extent;
    uint32_t size;
    VkImageLayout initial;
    VkImageLayout current;
    VkFormat format;
};
constexpr auto defres=VkExtent3D{width, height, 1};
// /*fake enums:*/  using VkMemoryPropertyFlags = uint32_t;
struct MemSys2:Tmp
{
    void* data;
    VmaAllocator a;
    DiscreteQueue q;
    constexpr explicit MemSys2(uint32_t vkVer, Tmp tmp, DiscreteQueue defQ): q(defQ), a(setupAlloc(vkVer)), Tmp{tmp} {};

    [[nodiscard]] auto setupAlloc(uint32_t) const -> VmaAllocator;
    [[nodiscard]] auto allocBuff(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags, bool=false) const -> vmaBuffer;
    [[nodiscard]] auto allocImg(VkExtent3D =defres, uint32_t=defSize, VkImageUsageFlags=VK_IMAGE_USAGE_TRANSFER_SRC_BIT|VK_IMAGE_USAGE_TRANSFER_DST_BIT) const -> vmaImage;
};