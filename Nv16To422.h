//
//  Nv16To422.h
//  Nv16To422
//
//  Created by Hank Lee on 9/30/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#ifndef ___Nv16To422___
#define ___Nv16To422___

/**
 *
 * u: dst address of u
 * v: dst address of v
 * uv: uv interleaved input buffer
 *
 */
int interleave_to_planar
(
 uint32_t wxh,
 uint8_t *u,
 uint8_t *v,
 const uint8_t *uv
);


#endif
