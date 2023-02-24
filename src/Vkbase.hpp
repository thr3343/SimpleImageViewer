#pragma once
#include "defs.tpp"
#include "TMp.hpp"
#include "Win.hpp"
#include <cstdint>
//#define VK_NO_PROTOTYPES

struct DiscreteQueue
{

  constexpr DiscreteQueue(VkQueue queue, uint32_t queuefamilyVarient)
      noexcept : queue(queue), queuefamilyVarient(queuefamilyVarient) {}


  constexpr DiscreteQueue(const DiscreteQueue &) = default;
  consteval DiscreteQueue(DiscreteQueue &&) noexcept = default;
  constexpr auto operator=(const DiscreteQueue &) -> DiscreteQueue & = default;
  consteval auto operator=(DiscreteQueue &&) noexcept -> DiscreteQueue & = default;
  VkQueue queue;
  uint32_t queuefamilyVarient;
  // uint32_t prio=1;
  // uint32_t capabilities=0;
} __attribute__((aligned(16)));


struct Vkbase : Win
{

  Vkbase(const Vkbase &) = delete;
  Vkbase(Vkbase &&) noexcept = default;
  auto operator=(const Vkbase &) -> Vkbase & = delete;
  auto operator=(Vkbase &&) -> Vkbase & = default;
  Vkbase() noexcept =default;

  uint32_t vkVer = getVer();
  VkInstance instance = createInstance();
  VkSurfaceKHR surface = createSurface();
  VkPhysicalDevice physDevice = createPhysDevice();
  VkDevice device = createDevice();
  // DiscreteQueue GraphicsQueue = getQueue(0);
  // DiscreteQueue TransferQueue = getQueue(1);
  DiscreteQueue PresentQueue = getQueue(2);

  [[nodiscard]] auto getVer() -> uint32_t;
  [[nodiscard]] auto createInstance() -> VkInstance;
  [[nodiscard]] auto createSurface() -> VkSurfaceKHR;
  [[nodiscard]] auto createPhysDevice() -> VkPhysicalDevice;
  [[nodiscard]] auto createDevice() -> VkDevice;
  [[nodiscard]] auto getQueue(uint32_t) -> DiscreteQueue;

  void clean();

  ~Vkbase() { clean(); }



};