//
//  UtilAllocator.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/4/25.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef UtilAllocator_hpp
#define UtilAllocator_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Typedef/MyTypedef.h"
namespace zkzszd {
    class UtilAllocator
    {
    private:
        UtilAllocator();   //防止工具类被实例化
    public:
        /**
         Description
         请保证length能被item_length整除
         @param length length description
         @param pixel pixel description
         @param item_length 每一个元素长度
         @return return value description
         */
        static int8* alloc_malloc(uint32 length,uint32 pixel = 0,uint8 item_length = 0);
        /**
         通过拷贝内存方式申请内存

         @param alloc_length <#alloc_length description#>
         @param copy_addr <#copy_from description#>
         @return <#return value description#>
         */
        static int8* alloc_malloc(uint32 alloc_length,void *copy_addr);
    };
}

#endif /* UtilAllocator_hpp */
