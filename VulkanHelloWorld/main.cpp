//
//  main.cpp
//  VulkanHelloWorld
//
//  Created by ABHISHEK SINGH on 22/02/20.
//  Copyright © 2020 Abhishek Singh. All rights reserved.
//

#include <iostream>
#include <vulkan/vulkan.h>

int main(int argc, const char * argv[]) {
    VkInstance instance;
    VkResult result;
    VkInstanceCreateInfo info = {};

    result = vkCreateInstance(&info, NULL, &instance);
    std::cout << "vkCreateInstance result: " << result  << "\n";

    vkDestroyInstance(instance, nullptr);
    return 0;
}
