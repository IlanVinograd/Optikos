#ifndef VULKAN_CONFIG_HPP
#define VULKAN_CONFIG_HPP

#define CONFIG_NULL_HANDLE nullptr

#include <vulkan/vulkan.h>

#include <cstdint>

#include "vk_mem_alloc.h"

struct SharedVulkanConfig
{
    const VkInstance*       instance       = nullptr;
    const VkPhysicalDevice* physicalDevice = nullptr;
    const VkDevice*         device         = nullptr;
    const VkSurfaceKHR*     surface        = nullptr;
    const VmaAllocator*     allocator      = nullptr;

    const VkQueue* graphicsQueue = nullptr;
    const VkQueue* presentQueue  = nullptr;

    const VkSwapchainKHR* swapChain       = nullptr;
    const VkFormat*       swapChainFormat = nullptr;
    const VkExtent2D*     swapChainExtent = nullptr;

    const VkRenderPass*     renderPass       = nullptr;
    const VkPipelineLayout* pipelineLayout   = nullptr;
    const VkPipeline*       graphicsPipeline = nullptr;
    const VkCommandPool*    commandPool      = nullptr;

    const uint32_t* currentFrame    = nullptr;
    const uint32_t* imageCount      = 0;
    const int*      frame_in_flight = 0;

    bool isValid() const
    {
        if (!instance || !physicalDevice || !device || !surface || !graphicsQueue ||
            !presentQueue || !swapChain || !swapChainFormat || !swapChainExtent || !renderPass ||
            !pipelineLayout || !graphicsPipeline || !commandPool)
        {
            return false;
        }
        return *instance != VK_NULL_HANDLE && *physicalDevice != VK_NULL_HANDLE &&
               *device != VK_NULL_HANDLE && *surface != VK_NULL_HANDLE &&
               *graphicsQueue != VK_NULL_HANDLE && *presentQueue != VK_NULL_HANDLE &&
               *swapChain != VK_NULL_HANDLE && *renderPass != VK_NULL_HANDLE &&
               *pipelineLayout != VK_NULL_HANDLE && *graphicsPipeline != VK_NULL_HANDLE &&
               *commandPool != VK_NULL_HANDLE && *swapChainFormat != VK_FORMAT_UNDEFINED &&
               swapChainExtent->width > 0 && swapChainExtent->height > 0;
    }
};

struct ViewPort
{
    VkImage         image           = VK_NULL_HANDLE;
    VmaAllocation   imageAllocation = VK_NULL_HANDLE;
    VkImageView     imageView       = VK_NULL_HANDLE;
    VkDescriptorSet descriptorSet   = VK_NULL_HANDLE;
};

#endif /* VULKAN_CONFIG_HPP */