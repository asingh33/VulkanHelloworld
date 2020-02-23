//
//  main.cpp
//  VulkanHelloWorld
//
//  Created by ABHISHEK SINGH on 22/02/20.
//  Copyright © 2020 Abhishek Singh. All rights reserved.
//

//#include <iostream>
//#include <vulkan/vulkan.h>
#include "Renderer.h"



int main(int argc, const char * argv[]) {
    
    //Renderer r;
    
    std::unique_ptr<Renderer> vrenderer = std::make_unique<Renderer>();
    
    
    
    return 0;
}



