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

#include "SampleRenderer.h"

// our helper library for window handling
#include "glfWindow/GLFWindow.h"
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <string>


#include "Scene.h"
#include "Parser.h"

/*! \namespace osc - Optix Siggraph Course */
namespace osc {

  struct SampleWindow : public GLFCameraWindow
  {
    SampleWindow(const std::string &title,
                 const Model *model,
                 const Camera &camera,
                 const QuadLight &light,
                 const float worldScale)
      : GLFCameraWindow(title,camera.from,camera.at,camera.up,worldScale),
        sample(model,light)
    {
      sample.setCamera(camera);
    }
    
    virtual void render() override
    {
      if (cameraFrame.modified) {
        sample.setCamera(Camera{ cameraFrame.get_from(),
                                 cameraFrame.get_at(),
                                 cameraFrame.get_up() });
        cameraFrame.modified = false;
      }
      sample.render();
    }
    
    virtual void draw() override
    {
      sample.downloadPixels(pixels.data());
      if (fbTexture == 0)
        glGenTextures(1, &fbTexture);
      
      glBindTexture(GL_TEXTURE_2D, fbTexture);
      GLenum texFormat = GL_RGBA;
      GLenum texelType = GL_FLOAT;//GL_UNSIGNED_BYTE;
      glTexImage2D(GL_TEXTURE_2D, 0, texFormat, fbSize.x, fbSize.y, 0, GL_RGBA,
                   texelType, pixels.data());

      glDisable(GL_LIGHTING);
      glColor3f(1, 1, 1);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, fbTexture);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      
      glDisable(GL_DEPTH_TEST);

      glViewport(0, 0, fbSize.x, fbSize.y);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0.f, (float)fbSize.x, 0.f, (float)fbSize.y, -1.f, 1.f);

      glBegin(GL_QUADS);
      {
        glTexCoord2f(0.f, 0.f);
        glVertex3f(0.f, 0.f, 0.f);
      
        glTexCoord2f(0.f, 1.f);
        glVertex3f(0.f, (float)fbSize.y, 0.f);
      
        glTexCoord2f(1.f, 1.f);
        glVertex3f((float)fbSize.x, (float)fbSize.y, 0.f);
      
        glTexCoord2f(1.f, 0.f);
        glVertex3f((float)fbSize.x, 0.f, 0.f);
      }
      glEnd();
    }
    
    virtual void resize(const vec2i &newSize) 
    {
      fbSize = newSize;
      sample.resize(newSize);
      pixels.resize(newSize.x*newSize.y);
    }

    //virtual void key(int key, int mods)
    //{
    //  if (key == 'D' || key == ' ' || key == 'd') {
    //    sample.denoiserOn = !sample.denoiserOn;
    //    std::cout << "denoising now " << (sample.denoiserOn?"ON":"OFF") << std::endl;
    //  }
    //  if (key == 'A' || key == 'a') {
    //    sample.accumulate = !sample.accumulate;
    //    std::cout << "accumulation/progressive refinement now " << (sample.accumulate?"ON":"OFF") << std::endl;
    //  }
    //  if (key == ',') {
    //    sample.launchParams.numPixelSamples
    //      = std::max(1,sample.launchParams.numPixelSamples-1);
    //    std::cout << "num samples/pixel now "
    //              << sample.launchParams.numPixelSamples << std::endl;
    //  }
    //  if (key == '.') {
    //    sample.launchParams.numPixelSamples
    //      = std::max(1,sample.launchParams.numPixelSamples+1);
    //    std::cout << "num samples/pixel now "
    //              << sample.launchParams.numPixelSamples << std::endl;
    //  }
    //}
    

    vec2i                 fbSize;
    GLuint                fbTexture {0};
    SampleRenderer        sample;
    std::vector<vec4f> pixels;
  };
  

  /*! main entry point to this example - initially optix, print hello
    world, then exit */
  extern "C" int main(int ac, char** av)
  {

      // parsing povray file
      std::ifstream inFile;
      Scene scene;

      if (ac > 1) {
          inFile.open(av[1]);

          if (inFile.is_open()) {
              std::cout << "opened: " << av[1] << std::endl;
          }
          else {
              std::cout << "cannot open file" << av[1] << std::endl;
              exit(1);
          }
      }
     
      Parser p(inFile, scene);

      Model* model = new Model;


    try {
        loadOBJ(av[2], model);
     //   loadOBJ("../models/icoNoNormals.obj", model);
      //  Camera camera = {vec3f(0.0f, 0.0f, 5.0f), model->bounds.center()-vec3f(0,0,0), vec3f(0.f,1.f,0.f) };


         loadSpheres(scene.spheres, model);
    //     loadPlanes(scene.planes, model);
         loadPlanes2(scene.planes, model);
      //   loadPlanes3(scene.planes, model);
         loadAreaLights(scene.lights, model);
         Camera camera = { scene.cameras[0]->getFrom(), scene.cameras[0]->getAt(), scene.cameras[0]->getUp() };


      const float light_size = 200.f;
      QuadLight light = { /* origin */ vec3f(-1000-light_size,800,-light_size),
                          /* edge 1 */ vec3f(2.f*light_size,0,0),
                          /* edge 2 */ vec3f(0,0,2.f*light_size),
                          /* power */  vec3f(3000000.f) };
                      
      // something approximating the scale of the world, so the
      // camera knows how much to move for any given user interaction:
      const float worldScale = length(model->bounds.span());

      SampleWindow *window = new SampleWindow("Ray tracing in Optix 7",
                                              model,camera,light,worldScale);

      window->enableFlyMode();
      
      //std::cout << "Press 'a' to enable/disable accumulation/progressive refinement" << std::endl;
      //std::cout << "Press ' ' to enable/disable denoising" << std::endl;
      //std::cout << "Press ',' to reduce the number of paths/pixel" << std::endl;
      //std::cout << "Press '.' to increase the number of paths/pixel" << std::endl;
      window->run();
      
    } catch (std::runtime_error& e) {
      std::cout << GDT_TERMINAL_RED << "FATAL ERROR: " << e.what()
                << GDT_TERMINAL_DEFAULT << std::endl;
	  exit(1);
    }
    return 0;
  }
  
} // ::osc
