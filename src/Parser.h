#pragma once

#include <regex>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <istream>
#include <memory>


#include "Camera.h"
#include "Sphere.h"
#include "Scene.h"


#define CAMERA "camera"
#define SPHERE "sphere"
#define LIGHTSOURCE "light_source"
#define PLANE "plane"
#define OBJ "obj"
#define START "{"
#define END "}"

using namespace std;

class Parser {
 
    public:
        Parser(istream& input, Scene& scene) : input(input), scene(scene) { parse(); }


        void parse() {
            string w;

          
            while (input >> w) {
                if (w.compare(CAMERA) == 0) {
                    parseCamera();
                }
                if (w.compare(SPHERE) == 0) {
                    parseSphere();
                }
                if (w.compare(LIGHTSOURCE) == 0) {
                    parseLight();
                }
                if (w.compare(PLANE) == 0) {
                    parsePlane();
                }
                if (w.compare(OBJ) == 0) {
                    parseObj();
                }
            }
        }

    private:
        istream& input;
        Scene& scene;

        

        // parse camera data and add to list of cameras in the scene
        void parseCamera() {
            string w;
            vec3 tmp;

         //   auto camera = make_shared<Camera>();
            Camera *camera = new Camera;

            while (input >> w) {
                if (w.compare(END) == 0) {
                    break;
                }

                if (w.compare("location") == 0) {
                    tmp.setX(extractDouble(w));
                    tmp.setY(extractDouble(w));
                    tmp.setZ(extractDouble(w));

                    camera->setEye(tmp);
                }
                
                if (w.compare("up") == 0) {
                    tmp.setX(extractDouble(w));
                    tmp.setY(extractDouble(w));
                    tmp.setZ(extractDouble(w));

                    camera->setUp(tmp);
                }

                if (w.compare("right") == 0) {
                    tmp.setX(extractDouble(w));
                    tmp.setY(extractDouble(w));
                    tmp.setZ(extractDouble(w));

                    camera->setRight(tmp);
                }

                if (w.compare("look_at") == 0) {
                    tmp.setX(extractDouble(w));
                    tmp.setY(extractDouble(w));
                    tmp.setZ(extractDouble(w));

                    camera->setLookAt(tmp);
                }
            }
            scene.addCamera(camera);
        }

        // parse sphere data and add it to the list of geometries in the scene
        void parseSphere() {
            string w;
            char c;
            vec3 tmp;
         //   auto sphere = make_shared<Sphere>();
            Sphere *sphere = new Sphere;

            input >> w;
            tmp.setX(extractDouble(w));
            tmp.setY(extractDouble(w));
            tmp.setZ(extractDouble(w));

            sphere->setCenter(tmp);
            sphere->setRadius(extractDouble(w));

            while (input >> w && w.compare(END) != 0) {
                if (w.compare("pigment") == 0) {
                    input >> w;
                    input >> w;
                    if (w.compare("color") == 0) {
                        input >> w;  
                        if (w.compare("rgb") == 0) {
                            tmp.setX(extractDouble(w));
                            tmp.setY(extractDouble(w));
                            tmp.setZ(extractDouble(w));

                            sphere->setPigment(tmp);
                        }
                    }
                    else if (w.compare("image_map") == 0) {
                        input >> c;
                        input >> w;

                        string img = extractImg(w);
                        img.erase(remove(img.begin(), img.end(), '\"'), img.end());
                        sphere->setTextureImg(img);
                        
                        input >> w;
                    }
                }
                else if (w.compare("finish") == 0) {
                    input >> c;
                    input >> w;
                    if (w.compare("reflection") == 0) {
                        sphere->setFuzzy(extractDouble(w));
                    }
                    else if (w.compare("ior") == 0) {
                        sphere->setIor(extractDouble(w));
                    }
                    
                }
                else if (w.compare("scale") == 0) {
                    tmp.setX(extractDouble(w));
                    tmp.setY(extractDouble(w));
                    tmp.setZ(extractDouble(w));
                    sphere->setScale(tmp);
                }
                else if (w.compare("rotate") == 0) {
                    tmp.setX(extractDouble(w));
                    tmp.setY(extractDouble(w));
                    tmp.setZ(extractDouble(w));
                    sphere->setRotate(tmp);
                }
                else if (w.compare("translate") == 0) {
                    tmp.setX(extractDouble(w));
                    tmp.setY(extractDouble(w));
                    tmp.setZ(extractDouble(w));
                    sphere->setTranslate(tmp);
                }
                
            }
            sphere->transCTM();
            scene.addSphere(sphere);
        }

        // parse the light source data and add to list of lights in scene
        void parseLight() {
            char c;
            string w;
            vec3 tmp;
         //   auto light = make_shared<Light>();
            Light *light = new Light;

            while (input >> c && c != '}') {
                if (c == '{') {
                    tmp.setX(extractDouble(w));
                    tmp.setY(extractDouble(w));
                    tmp.setZ(extractDouble(w));

                    light->setPosition(tmp);
                }

                input >> w;
                if (w.compare("color") == 0) {
                    input >> w;
                    if (w.compare("rgb") == 0) {
                        tmp.setX(extractDouble(w));
                        tmp.setY(extractDouble(w));
                        while (input >> c && c != '>') {
                            w += c;
                        }
                        tmp.setZ(stod(w));
                        light->setPigment(tmp);
                    }
                }

                input >> c;
                if (c != '}') {
                    input >> w;
                    w = c + w;
                    if (w.compare("area_light") == 0) {
                        tmp.setX(extractDouble(w));
                        tmp.setY(extractDouble(w));
                        tmp.setZ(extractDouble(w));
                        light->setV1(tmp);

                        tmp.setX(extractDouble(w));
                        tmp.setY(extractDouble(w));
                        tmp.setZ(extractDouble(w));
                        light->setV2(tmp);
                        
                    }
                }
                else {
                    break;
                }
            }

            scene.addLight(light);
        }

        // parse plane data and add it to the list of geometries in the scene
        void parsePlane() {
            char c;
            string w;
            vec3 tmp;
         //   auto plane = make_shared<Plane>();
            Plane *plane = new Plane;

            input >> c;
            tmp.setX(extractDouble(w));
            tmp.setY(extractDouble(w));
            tmp.setZ(extractDouble(w));

            plane->setNormal(tmp);
            plane->setDistance(extractDouble(w));

            while (input >> w && w.compare(END) != 0) {
                if (w.compare("pigment") == 0) {
                    input >> c;
                    input >> w;
                    if (w.compare("color") == 0) {
                        input >> w;
                        if (w.compare("rgb") == 0) {
                            tmp.setX(extractDouble(w));
                            tmp.setY(extractDouble(w));
                            tmp.setZ(extractDouble(w));

                            plane->setPigment(tmp);
                        }
                    }
                    else if (w.compare("image_map") == 0) {
                        input >> c;
                        input >> w;

                        string img = extractImg(w);
                        img.erase(remove(img.begin(), img.end(), '\"'), img.end());
                    //    plane->setTextureImg(img);

                        input >> w;
                    }
                    
                }
                else if (w.compare("finish") == 0) {
                    input >> c;
                    input >> w;
                    if (w.compare("reflection") == 0) {
                        plane->setFuzzy(extractDouble(w));
                    }
                    else if (w.compare("ior") == 0) {
                        plane->setIor(extractDouble(w));
                    }
                }
            }
            scene.addPlane(plane);
        }

        void parseObj() {}

   /*     void parseObj() {
            string w;
            char c;
            vec3 tmp;

            while (input >> w && w.compare(END) != 0) {
                if (w.compare("pigment") == 0) {
                    input >> c;
                    input >> w;
                    if (w.compare("color") == 0) {
                        input >> w;
                        if (w.compare("rgb") == 0) {
                            tmp.setX(extractDouble(w));
                            tmp.setY(extractDouble(w));
                            tmp.setZ(extractDouble(w));
                        }

                        scene.shapes[0]->setColor(tmp);
                    }
                }
                else if (w.compare("scale") == 0) {
                    tmp.setX(extractDouble(w));
                    tmp.setY(extractDouble(w));
                    tmp.setZ(extractDouble(w));
                    scene.shapes[0]->setScale(tmp);
                }
                else if (w.compare("rotate") == 0) {
                    tmp.setX(extractDouble(w));
                    tmp.setY(extractDouble(w));
                    tmp.setZ(extractDouble(w));
                    scene.shapes[0]->setRotate(tmp);
                }
                else if (w.compare("translate") == 0) {
                    tmp.setX(extractDouble(w));
                    tmp.setY(extractDouble(w));
                    tmp.setZ(extractDouble(w));
                    scene.shapes[0]->setTranslate(tmp);
                }
            }
            scene.shapes[0]->transCTM();
        } */

        // extracting integers of decimals from a srting
        double extractDouble(string& w) {
            regex target("([-]*[0-9]+[.]*[0-9]*[e]*[-]*[0-9]*)");
            smatch match;

            input >> w;
            if (regex_search(w, match, target)) {
                return stod(match.str());
            }

            return -1;
        }

        string extractImg(string& w) {
            regex target("\"(.)*\"");
            string res = "";
            smatch match;
            input >> w;
            if (regex_search(w, match, target)) {
                res = match.str();
            }
            return res;
        }

};