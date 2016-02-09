//
//  GLFWDemo.cpp
//  
//
//  Created by David M. Reed on 2/18/15.
//  Copyright (c) 2015 David Reed. All rights reserved.
//

#include <string>

#include "Utils.h"
#include "GLFWDemo.h"

#include "Angel.h"

using std::string;

//----------------------------------------------------------------------

// must initlaize GLFWBase with window parameter
GLFWDemo::GLFWDemo(GLFWwindow* window) : GLFWBase(window)
{

}

//----------------------------------------------------------------------

void GLFWDemo::setup()
{
    // black background
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // default draw as filled triangles
    _drawType = GL_TRIANGLES;

    // set point size to 5 so easy to see
    glPointSize(5);

    size_t pos;

    // initialize points for triangle 0
    pos = 0;

    // specify x, y
    // point 0
    _points[pos++] = 0.0;
    _points[pos++] = 0.5;

    // point 1
    _points[pos++] = 0.5;
    _points[pos++] = 0.0;

    // point 2
    _points[pos++] = 0.0;
    _points[pos++] = -0.5;

    // point 3
    _points[pos++] = -0.5;
    _points[pos++] = 0.0;


    pos = 0;
    _indices[pos++] = 0;
    _indices[pos++] = 3;
    _indices[pos++] = 1;

    _indices[pos++] = 1;
    _indices[pos++] = 3;
    _indices[pos++] = 2;



    // Create and initialize a buffer object
    // (cache data in graphics card memory)
    glGenBuffers(1, &_buffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), _points, GL_STATIC_DRAW);

    // Create and initialize a buffer object
    // (cache data in graphics card memory)
    glGenBuffers(1, &_buffers[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), _indices, GL_STATIC_DRAW);

    // read and compile shaders
    string vshaderPath = "vshader.txt";
    string fshaderPath = "fshader.txt";
    vshaderPath = pathUsingEnvironmentVariable(vshaderPath, "GL_SHADER_DIR");
    fshaderPath = pathUsingEnvironmentVariable(fshaderPath, "GL_SHADER_DIR");
    _shaderProgram.makeProgramFromShaderFiles(vshaderPath, fshaderPath);
    _shaderProgram.useProgram();
}

//----------------------------------------------------------------------

void GLFWDemo::render()
{
    // clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // layout value for vPosition
    glEnableVertexAttribArray(0);


    // buffer for first triangle
    glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[1]);

    // specify the actual vertex data from the buffer
    // first parameter is 0 because the layout value for vPosition in the vertex shader is 0
    // second and third parameters are 2 and GL_FLOAT because there are two values (x, y) per pixel that are floats
    // fourth parameter is GL_FALSE since the values are not normalized
    // fifth parameter is the number of bytes (stride) to get to the next vertex
    //   it is 2 * sizeof(GLfloat) since there are 2 (x, y) float values per pixel
    // sixth parameter is 0 bytes since since first value in array is the x coordinate
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));

    GLint polyColorLocation;

    // get location for communicating polyColor
    polyColorLocation = glGetUniformLocation(_shaderProgram.program(), "polyColor");
    // draw polygon red
    glUniform3f(polyColorLocation, 1.0, 0.0, 0.0);

    // draw the buffer for the two triangles
    glDrawElements(_drawType, 6, GL_UNSIGNED_INT, NULL);
}

//----------------------------------------------------------------------

void GLFWDemo::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        _drawType = GL_TRIANGLES;
    }
    else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        _drawType = GL_POINTS;
    }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS) {
        _drawType = GL_LINES;
    }
}

//----------------------------------------------------------------------

