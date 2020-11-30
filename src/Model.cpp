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

#include "Model.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "3rdParty/tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "3rdParty/stb_image.h"

//std
#include <set>

namespace std {
  inline bool operator<(const tinyobj::index_t &a,
                        const tinyobj::index_t &b)
  {
    if (a.vertex_index < b.vertex_index) return true;
    if (a.vertex_index > b.vertex_index) return false;
    
    if (a.normal_index < b.normal_index) return true;
    if (a.normal_index > b.normal_index) return false;
    
    if (a.texcoord_index < b.texcoord_index) return true;
    if (a.texcoord_index > b.texcoord_index) return false;
    
    return false;
  }
}

/*! \namespace osc - Optix Siggraph Course */
namespace osc {
  
    
    

  /*! find vertex with given position, normal, texcoord, and return
      its vertex ID, or, if it doesn't exit, add it to the mesh, and
      its just-created index */
  int addVertex(TriangleMesh *mesh,
                tinyobj::attrib_t &attributes,
                const tinyobj::index_t &idx,
                std::map<tinyobj::index_t,int> &knownVertices)
  {
    if (knownVertices.find(idx) != knownVertices.end())
      return knownVertices[idx];

    const vec3f *vertex_array   = (const vec3f*)attributes.vertices.data();
    const vec3f *normal_array   = (const vec3f*)attributes.normals.data();
    const vec2f *texcoord_array = (const vec2f*)attributes.texcoords.data();
    
    int newID = (int)mesh->vertex.size();
    knownVertices[idx] = newID;

    mesh->vertex.push_back(vertex_array[idx.vertex_index]);
    if (idx.normal_index >= 0) {
      while (mesh->normal.size() < mesh->vertex.size())
        mesh->normal.push_back(normal_array[idx.normal_index]);
    }
    if (idx.texcoord_index >= 0) {
      while (mesh->texcoord.size() < mesh->vertex.size())
        mesh->texcoord.push_back(texcoord_array[idx.texcoord_index]);
    }

    // just for sanity's sake:
    if (mesh->texcoord.size() > 0)
      mesh->texcoord.resize(mesh->vertex.size());
    // just for sanity's sake:
    if (mesh->normal.size() > 0)
      mesh->normal.resize(mesh->vertex.size());
    
    return newID;
  }

  /*! load a texture (if not already loaded), and return its ID in the
      model's textures[] vector. Textures that could not get loaded
      return -1 */
  int loadTexture(Model *model,
                  std::map<std::string,int> &knownTextures,
                  const std::string &inFileName,
                  const std::string &modelPath)
  {
    if (inFileName == "")
      return -1;
    
    if (knownTextures.find(inFileName) != knownTextures.end())
      return knownTextures[inFileName];

    std::string fileName = inFileName;
    // first, fix backspaces:
    for (auto &c : fileName)
      if (c == '\\') c = '/';
    fileName = modelPath+"/"+fileName;

    vec2i res;
    int   comp;
    unsigned char* image = stbi_load(fileName.c_str(),
                                     &res.x, &res.y, &comp, STBI_rgb_alpha);
    int textureID = -1;
    if (image) {
      textureID = (int)model->textures.size();
      Texture *texture = new Texture;
      texture->resolution = res;
      texture->pixel      = (uint32_t*)image;

      /* iw - actually, it seems that stbi loads the pictures
         mirrored along the y axis - mirror them here */
      for (int y=0;y<res.y/2;y++) {
        uint32_t *line_y = texture->pixel + y * res.x;
        uint32_t *mirrored_y = texture->pixel + (res.y-1-y) * res.x;
        int mirror_y = res.y-1-y;
        for (int x=0;x<res.x;x++) {
          std::swap(line_y[x],mirrored_y[x]);
        }
      }
      
      model->textures.push_back(texture);
    } else {
      std::cout << GDT_TERMINAL_RED
                << "Could not load texture from " << fileName << "!"
                << GDT_TERMINAL_DEFAULT << std::endl;
    }
    
    knownTextures[inFileName] = textureID;
    return textureID;
  }
  


  void loadOBJ(const std::string &objFile, Model* model)
  {

    const std::string modelDir
      = objFile.substr(0,objFile.rfind('/')+1);
    
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err = "";

    bool readOK
      = tinyobj::LoadObj(&attributes,
                         &shapes,
                         &materials,
                         &err,
						 &err,
                         objFile.c_str(),
                         modelDir.c_str(),
                         /* triangulate */true);
    if (!readOK) {
      throw std::runtime_error("Could not read OBJ model from "+objFile+" : "+err);
    }

    if (materials.empty())
      throw std::runtime_error("could not parse materials ...");

    std::cout << "Done loading obj file - found " << shapes.size() << " shapes with " << materials.size() << " materials" << std::endl;
    for (int shapeID=0;shapeID<(int)shapes.size();shapeID++) {
      tinyobj::shape_t &shape = shapes[shapeID];

      std::set<int> materialIDs;
      for (auto faceMatID : shape.mesh.material_ids)
        materialIDs.insert(faceMatID);
      
      std::map<tinyobj::index_t,int> knownVertices;
      std::map<std::string,int>      knownTextures;
      
      for (int materialID : materialIDs) {
        TriangleMesh *mesh = new TriangleMesh;
        
        for (int faceID=0;faceID<shape.mesh.material_ids.size();faceID++) {
          if (shape.mesh.material_ids[faceID] != materialID) continue;
          tinyobj::index_t idx0 = shape.mesh.indices[3*faceID+0];
          tinyobj::index_t idx1 = shape.mesh.indices[3*faceID+1];
          tinyobj::index_t idx2 = shape.mesh.indices[3*faceID+2];
          
          vec3i idx(addVertex(mesh, attributes, idx0, knownVertices),
                    addVertex(mesh, attributes, idx1, knownVertices),
                    addVertex(mesh, attributes, idx2, knownVertices));
          mesh->index.push_back(idx);
          mesh->diffuse = (const vec3f&)materials[materialID].diffuse;
          mesh->diffuseTextureID = loadTexture(model,
                                               knownTextures,
                                               materials[materialID].diffuse_texname,
                                               modelDir);


          if (materials[materialID].emission[0] + materials[materialID].emission[1] + materials[materialID].emission[2] > 0) {
              vec3f a = vec3f(attributes.vertices[3 * idx0.vertex_index + 0],
                  attributes.vertices[3 * idx0.vertex_index + 1],
                  attributes.vertices[3 * idx0.vertex_index + 2]);
              vec3f b = vec3f(attributes.vertices[3 * idx1.vertex_index + 0],
                  attributes.vertices[3 * idx1.vertex_index + 1],
                  attributes.vertices[3 * idx1.vertex_index + 2]);
              vec3f c = vec3f(attributes.vertices[3 * idx2.vertex_index + 0],
                  attributes.vertices[3 * idx2.vertex_index + 1],
                  attributes.vertices[3 * idx2.vertex_index + 2]);
              vec3f power = vec3f(materials[materialID].emission[0], materials[materialID].emission[1], materials[materialID].emission[2]);
          
              model->triangleLights.push_back(TriangleLight{ a, b, c, power });

          }
        }

        if (mesh->vertex.empty())
          delete mesh;
        else
          model->meshes.push_back(mesh);
      }
    }

    // of course, you should be using tbb::parallel_for for stuff
    // like this:
    for (auto mesh : model->meshes)
      for (auto vtx : mesh->vertex)
        model->bounds.extend(vtx);
    
    std::cout << "created a total of " << model->meshes.size() << " meshes" << std::endl;
  }

#define PI 3.14159265358979323846f
  void loadSpheres(std::vector<Sphere*> spheres, Model* model) {
      std::cout << "loading "<< spheres.size() << " spheres" << std::endl;
      
      for (auto sphere : spheres) {
          TriangleMesh* mesh = new TriangleMesh;

          int U = 180, V = 90;
          float phi_step = 2.0f * PI / (float)U;
          float theta_step = PI / (float)(V - 1);

          for (int latitude = 0; latitude < V; latitude++) {
              float theta = (float)latitude * theta_step;
              float sin_theta = sinf(theta);
              float cos_theta = cosf(theta);

              float texv = (float)latitude / (float)(V - 1);

              for (int longitude = 0; longitude <= U; longitude++) {
                  float phi = (float)longitude * phi_step;
                  float sin_phi = sinf(phi);
                  float cos_phi = cosf(phi);

                  float texu = (float)longitude / (float)U;

                  vec3f normal = vec3f(cos_phi * sin_theta, -cos_theta, -sin_phi * sin_theta);

                  vec3f vertex = normal * sphere->getRadius() + sphere->getCenter();

                  

                  vec2f texcord = vec2f(texu, texv);

                  mesh->normal.push_back(normal);
                  mesh->vertex.push_back(vertex);
                  mesh->texcoord.push_back(texcord);
              }
          }

          int columns = U + 1;
          for (int latitude = 0; latitude < V - 1; latitude++) {
              for (int longitude = 0; longitude < U; longitude++) {
                  vec3i idx = vec3i(latitude * columns + longitude, 
                                    latitude * columns + longitude + 1,
                                    (latitude + 1) * columns + longitude + 1);
                  vec3i idx2 = vec3i((latitude + 1) * columns + longitude + 1,
                                     (latitude + 1) * columns + longitude,
                                      latitude * columns + longitude);
                  mesh->index.push_back(idx);
                  mesh->index.push_back(idx2);

                  
              }
          }

          mesh->diffuse = sphere->getDiffuseColor();

          if (sphere->getSurfaceType() == 1) {
              mesh->isReflective = true;
              mesh->fuzzy = sphere->getFuzzy();

          }
          if (sphere->getSurfaceType() == 3) {
              mesh->isRefractive = true;
              mesh->ior = sphere->getIor();
          }

          std::map<std::string, int> knownTextures;
          mesh->diffuseTextureID = loadTexture(model,
              knownTextures,
              sphere->getTexturte(),
              "../textures");

          model->meshes.push_back(mesh);

      }

  
  }


  void loadPlanes(std::vector<Plane*> planes, Model* model) {
      std::cout << "loading " << planes.size() << " planes" << std::endl;
      for (auto plane : planes) {
          PlaneData* planeData = new PlaneData;

          planeData->color = plane->getPlaneColor();
          planeData->normal = plane->getNormal();
          planeData->distance = plane->getDistance();

          if (plane->getSurfaceType() == 1) {
              planeData->isReflective = true;
              planeData->fuzzy = plane->getFuzzy();
          }
          if (plane->getSurfaceType() == 3) {
              planeData->isRefractive = true;
              planeData->ior = plane->getIor();
          }
          
          model->planes.push_back(planeData);

      }
  }


#define D 10000.0f

  void loadPlanes2(std::vector<Plane*> planes, Model* model) {
      std::cout << "loading " << planes.size() << " planes" << std::endl;
      for (auto plane : planes) {
          TriangleMesh* mesh = new TriangleMesh;
          float distance = plane->getDistance();
          vec3f normal = plane->getNormal();

          vec3f mid = normal + gdt::normalize(normal) * distance;
          

          float x, y, z;
          if (normal.x == 0 && normal.y == 0) {     // xy plane
              x = rand() % 10 + 1.0f;
              y = rand() % 10 + 1.0f;
              z = mid.z;
          }
          else if (normal.x == 0 && normal.z == 0) {   // xz plane
              x = rand() % 10 + 1.0f;
              y = mid.y;
              z = rand() % 10 + 1.0f;
          }
          else if (normal.y == 0 && normal.z == 0) {   // yz plane
              x = mid.x;
              y = rand() % 10 + 1.0f;
              z = rand() % 10 + 1.0f;
          }
          else if (normal.x == 0) {
              x = rand() % 10 + 1.0f;
              y = rand() % 10 + 1.0f;
              z = (normal.y * (y - mid.y) - normal.z * mid.z) / -normal.z;
          }
          else if (normal.y == 0) {
              x = rand() % 10 + 1.0f;
              y = rand() % 10 + 1.0f;
              z = (normal.x * (x - mid.x) - normal.z * mid.z) / -normal.z;
          }
          else if (normal.z == 0) {
              x = rand() % 10 + 1.0f;
              y = (normal.x * (x - mid.x) - normal.y * mid.y) / -normal.y;
              z = rand() % 10 + 1.0f;
          }
          else {
              x = rand() % 10 + 1.0f;
              y = rand() % 10 + 1.0f;
              z = (normal.y * (y - mid.y) - normal.z * mid.z) / -normal.z;
          }

          vec3f v = gdt::normalize(vec3f(x, y, z) - mid);
          vec3f v2 = gdt::normalize(gdt::cross(normal, v));
         
          vec3f d1s = mid + (v * D);
          vec3f d1e = mid - (v * D);
          vec3f d2s = mid + (v2 * D);
          vec3f d2e = mid - (v2 * D);

          mesh->vertex.push_back(d1s);
          mesh->vertex.push_back(d1e);
          mesh->vertex.push_back(d2s);
          mesh->vertex.push_back(d2e);

          mesh->index.push_back(vec3i(0, 1, 3));
          mesh->index.push_back(vec3i(0, 2, 1));
          
          

          for (auto i = 0; i < 4; i++) {
              mesh->normal.push_back(normal);
          }


          mesh->diffuse = plane->getPlaneColor();

          if (plane->getSurfaceType() == 1) {
              mesh->isReflective = true;
              mesh->fuzzy = plane->getFuzzy();
          }
          if (plane->getSurfaceType() == 3) {
              mesh->isRefractive = true;
              mesh->ior = plane->getIor();
          }

          model->meshes.push_back(mesh);
      }
  }


  void loadAreaLights(std::vector<Light*> lights, Model* model) {
      std::cout << "loading " << lights.size() << " lights" << std::endl;
      for (auto light : lights) {
          TriangleMesh* mesh = new TriangleMesh;

          vec3f normal = light->getPosition();
          vec3f mid = light->getPosition();

          vec3f v1 = light->getV1();
          vec3f v2 = light->getV2();

          vec3f uprt, uplt, btrt, btlt;

          if (v1.x == 0 && v2.x == 0) {    // yz plane
              float y0 = mid.y + v1.y * 0.5;
              float y1 = mid.y - v1.y * 0.5;
              float z0 = mid.z + v2.z * 0.5;
              float z1 = mid.z - v2.z * 0.5;

              uprt.x = uplt.x = btrt.x = btlt.x = mid.x;

              uprt.z = uplt.z = z0;
              btrt.z = btlt.z = z1;

              uprt.y = btrt.y = y0;
              uplt.y = btlt.y = y1;

          }
          else if (v1.y == 0 && v2.y == 0) {  // xz plane
              float x0 = mid.x + v1.x * 0.5;
              float x1 = mid.x - v1.x * 0.5;
              float z0 = mid.z + v2.z * 0.5;
              float z1 = mid.z - v2.z * 0.5;

              uprt.y = uplt.y = btrt.y = btlt.y = mid.y;

              uprt.x = btrt.x = x0;
              uplt.x = btlt.x = x1;

              uprt.z = uplt.z = z0;
              btrt.z = btlt.z = z1;
          }
          else if (v1.z == 0 && v2.z == 0) {  // xy plane
              float x0 = mid.x + v1.x * 0.5;
              float x1 = mid.x - v1.x * 0.5;
              float y0 = mid.y + v1.y * 0.5;
              float y1 = mid.y - v1.y * 0.5;

              uprt.z = uplt.z = btrt.z = btlt.z = mid.z;

              uprt.y = uplt.y = y0;
              btrt.y = btlt.y = y1;

              uprt.x = btrt.x = x0;
              uplt.x = btlt.x = x1;
          }

          mesh->vertex.push_back(uprt);
          mesh->vertex.push_back(uplt);
          mesh->vertex.push_back(btrt);
          mesh->vertex.push_back(btlt);

          mesh->index.push_back(vec3i(0, 1, 2));
          mesh->index.push_back(vec3i(1, 3, 2));

      /*    mesh->index.push_back(vec3i(2, 1, 0));
          mesh->index.push_back(vec3i(2, 3, 1));*/

          for (auto i = 0; i < 4; i++) {
              mesh->normal.push_back(normal);
          }

          mesh->diffuse = light->getPigment();
          mesh->isEmissive = true;
          model->meshes.push_back(mesh);
      }
  }

}
