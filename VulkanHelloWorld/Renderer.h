//
//  Renderer.h
//  VulkanHelloWorld
//
//  Created by ABHISHEK SINGH on 23/02/20.
//  Copyright © 2020 Abhishek Singh. All rights reserved.
//

#ifndef Renderer_h
#define Renderer_h
#include <iostream>
#include <vulkan/vulkan.h>
#include <vector>
#include <iterator>

class Renderer
{
private:
    VkPhysicalDevice    mGPUDevice = nullptr;
    VkDevice            mDevice = nullptr;

public:
    VkInstance          mInstance = nullptr;
    
    Renderer();
    ~Renderer();
    
};

Renderer::Renderer()
{
    VkResult result ;
    
    // Create Instance
    {
        VkApplicationInfo appinfo = {};
        appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appinfo.applicationVersion = VK_MAKE_VERSION(0,1,0);
        appinfo.pApplicationName = "Vulkan Hello World";
        appinfo.apiVersion = VK_MAKE_VERSION(1,0,3);
        
        VkInstanceCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        info.pApplicationInfo = &appinfo;
        
        result = vkCreateInstance(&info, NULL, &mInstance);
        
        if( result == VK_ERROR_INCOMPATIBLE_DRIVER)
        {
            std::cerr << "Incompatible Vulkan driver!\n" ;
            return;
        }
        else if( result != VK_SUCCESS )
        {
            std::cerr << "Some error :( \n";
            return;
        }
        else{
            std::cout << "Vulkan is supported. Created the instance. \n";
        }
    }
    
    // Enumerate devices and Create device using one
    {
        uint32_t gpucount = 0;
        
        result = vkEnumeratePhysicalDevices(mInstance, &gpucount, NULL);
        std::vector<VkPhysicalDevice> devicelist(gpucount);
        result = vkEnumeratePhysicalDevices(mInstance, &gpucount, devicelist.data());
        
        // Default choosing the first one.
        mGPUDevice = devicelist[0];
        
        // Similarly we can enumerate Instance & Device layer properties
        {
            uint32_t propcount = 0;
            {
                vkEnumerateInstanceLayerProperties(&propcount, nullptr);
                std::vector<VkLayerProperties> layerprop(propcount);
                vkEnumerateInstanceLayerProperties(&propcount, layerprop.data());
                std::cout<< "Instance layers:\n";
                for(auto &i: layerprop)
                {
                    std::cout<< i.layerName << std::endl;
                    std::cout<< i.description << std::endl;
                }
            }
            {
                propcount = 0;
                vkEnumerateDeviceLayerProperties(mGPUDevice, &propcount, nullptr);
                std::vector<VkLayerProperties> layerprop(propcount);
                vkEnumerateDeviceLayerProperties(mGPUDevice, &propcount, layerprop.data());
                std::cout<< "Device layers:\n";
                for(auto &i: layerprop)
                {
                    std::cout<< i.layerName << std::endl;
                    std::cout<< i.description << std::endl;
                }
            }
        }
        
        
        
        float priorities = 1.0f;
        VkDeviceQueueCreateInfo device_queue_info = {};
        device_queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        device_queue_info.queueFamilyIndex = 1;
        device_queue_info.queueCount = 1;
        device_queue_info.pQueuePriorities = &priorities;
        
        
        VkDeviceCreateInfo device_info = {};
        device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        device_info.queueCreateInfoCount = 1;
        device_info.pQueueCreateInfos = &device_queue_info;
        
        
        //const VkAllocationCallbacks allocator = {};
        
        result = vkCreateDevice(mGPUDevice, &device_info, nullptr, &mDevice);
        
        if( result == VK_SUCCESS)
        {
            std::cout << "Created Vulkan device !\n";
        }
        
    }
}

Renderer::~Renderer()
{
    if( mDevice )
    {
        vkDestroyDevice(mDevice, NULL);
        std::cout << "Destroyed the Vulkan device.\n";
    }
    
    if( mInstance )
    {
        vkDestroyInstance(mInstance, NULL);
        std::cout << "Destroyed the Vulkan instance.\n";
    }
}


#endif /* Renderer_h */
