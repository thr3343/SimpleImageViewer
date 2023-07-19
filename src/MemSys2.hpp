#pragma once
#include "defs.tpp"
#include "Vkbase.hpp"

#include <cstdint>
#include <vulkan/vulkan_core.h>


constexpr VkImageSubresourceLayers subresource alignas(16) = {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
	    .mipLevel = 0,
	    .baseArrayLayer = 0,
	    .layerCount = 1,
        };
// constexpr VkDeviceSize defSize=static_cast<const VkDeviceSize>(width*height)*4Ul;
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

struct defExtent2D
{
    uint16_t width, height;
};
 struct imageViewDetails
 {
    uint16_t width, height;
    VkImage img;
    VkFormat format;
    VkImageUsageFlags usageFlags;
    VkImageLayout current;
    void addImg();

 };
struct [[gnu::aligned(32)]] vmaImage
{
    VkImage img; 
    VkExtent2D extent;
    uint32_t size;
    VkImageUsageFlags usageFlags;
    VkImageLayout current;
    VmaAllocation alloc;
    VkFormat format;
    VkImageView view;
    void* aData;

};
constexpr VkExtent3D defres{UINT16_MAX, UINT16_MAX, 1};


constexpr VkExtent2D defres2D{UINT16_MAX, UINT16_MAX};
// /*fake enums:*/  using VkMemoryPropertyFlags = uint32_t;
struct MemSys2:GPUDevice
{
    void* data;
    VmaAllocator a;
    DiscreteQueue q;
    constexpr explicit MemSys2(uint32_t vkVer, GPUDevice tmp, DiscreteQueue defQ): q(defQ), a(setupAlloc(vkVer)), GPUDevice{tmp} {};

    [[nodiscard]] auto setupAlloc(uint32_t) const -> VmaAllocator;
    [[nodiscard]] auto allocBuff(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags, bool=false) const -> vmaBuffer;
    [[nodiscard]] auto allocImg(VkExtent2D, VkFormat, VkImageUsageFlags=VK_IMAGE_USAGE_TRANSFER_SRC_BIT|VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_STORAGE_BIT, VkImageView=nullptr) const -> vmaImage;
};