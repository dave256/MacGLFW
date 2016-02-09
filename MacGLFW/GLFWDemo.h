//
//  GLFWDemo.h
//  
//
//  Created by David M. Reed on 2/18/15.
//  Copyright (c) 2015 David Reed. All rights reserved.
//

#ifndef __GLFWDemo__GLFWDemo__
#define __GLFWDemo__GLFWDemo__

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
    GLfloat _points[8];

    GLuint _indices[6];

};

#endif /* defined(__GLFWDemo__GLFWDemo__) */
