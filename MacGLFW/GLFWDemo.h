//
//  GLFWDemo.hpp
//  MacGLFW
//
//  Created by David M Reed on 12/12/17.
//  Copyright © 2017 David M Reed. All rights reserved.
//

#ifndef GLFWDemo_hpp
#define GLFWDemo_hpp

#include "ShaderProgram.h"
#include "GLFWBase.h"

class GLFWDemo : public GLFWBase {

public:
    GLFWDemo(GLFWwindow* window);

    // override the render method
    virtual void render();

    // override the keyboard callback
    virtual void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    // new method to initalize the data
    void setup();

private:
    ShaderProgram _shaderProgram;

    // type for how to draw the data
    GLenum _drawType;

    // buffer IDs
    GLuint _buffers[2];

    // data for polygon 0
    GLfloat _poly0[15];

    // data for polygon 1
    GLfloat _poly1[15];
};

#endif /* GLFWDemo_hpp */
