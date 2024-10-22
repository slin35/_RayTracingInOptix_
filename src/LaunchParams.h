// ======================================================================== //
// Copyright 2018-2019 Ingo Wald                                            //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include "gdt/math/vec.h"
#include "optix7.h"

namespace osc {
  using namespace gdt;

  // for this simple example, we have a single ray type
  enum { RADIANCE_RAY_TYPE=0, SHADOW_RAY_TYPE, RAY_TYPE_COUNT };

  struct TriangleMeshSBTData {
    vec3f  color;
    vec3f *vertex;
    vec3f *normal;
    vec2f *texcoord;
    vec3i *index;
    bool                hasTexture;
    cudaTextureObject_t texture;
    bool isReflective{ false };
    bool isRefractive{ false };
    bool isEmissive{ false };
    float fuzzy;
    float ior;
  };

  struct PlaneSBTData {
      vec3f color;
      vec3f normal;
      float distance;
      float fuzzy;
      float ior;
      bool isReflective;
      bool isRefractive;
  };
  
  struct LaunchParams
  {
    int numPixelSamples = 1;
    struct {
      int       frameID = 0;
      float4   *colorBuffer;
      
      /*! the size of the frame buffer to render */
      vec2i     size;
    } frame;
    
    struct {
      vec3f position;
      vec3f direction;
      vec3f horizontal;
      vec3f vertical;
    } camera;

    struct {
      vec3f origin, du, dv, power;
    } light;
    
    struct {
       // std::vector<vec3f> a, b, c, power;
        vec3f a[100], b[100], c[100], power[100];
    } lights;

    int numLights;
   

    OptixTraversableHandle traversable;
  };

} // ::osc
