//
//  UyvyToNv16.c
//  UyvyToNv16
//
//  Created by Hank Lee on 7/14/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <stdint.h>

#include "Nv16To422.h"

typedef uint8_t byte;

typedef struct
{
    byte u0;
    byte y0;
    byte v0;
    byte y1;
    
    byte u1;
    byte y2;
    byte v1;
    byte y3;
} quatre_pixel;

int unpack
(
        uint32_t wxh,
        uint32_t y[],
        uint32_t u_et_v[],
  const void    *src
)
{
    int i;
    quatre_pixel *pix = (quatre_pixel *) src;
    
    for (i = 0; i < wxh / 4; i++)
    {
        y[i] = (pix->y0) | (pix->y1 << 8) | (pix->y2 << 16) | (pix->y3 << 24);
        u_et_v[i] = pix->u0 | (pix->v0 << 8) | (pix->u1 << 16) | (pix->v1 << 24);
        
        pix++;
    }

    return 0;
}
