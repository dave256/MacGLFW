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

    // specify x, y, r, g, b for each point
    // point 0
    _poly0[pos++] = -0.75;
    _poly0[pos++] = -0.75;
    _poly0[pos++] = 1.0;
    _poly0[pos++] = 0.0;
    _poly0[pos++] = 0.0;

    // point 1
    _poly0[pos++] = -0.25;
    _poly0[pos++] = -0.75;
    _poly0[pos++] = 1.0;
    _poly0[pos++] = 0.0;
    _poly0[pos++] = 0.0;

    // point 2
    _poly0[pos++] = -0.25;
    _poly0[pos++] = 0.5;
    _poly0[pos++] = 1.0;
    _poly0[pos++] = 0.0;
    _poly0[pos++] = 0.0;

    // initialize points for triangle 1
    pos = 0;

    // specify x, y, r, g, b for each point
    // point 0
    _poly1[pos++] = 0.0;
    _poly1[pos++] = -0.75;
    _poly1[pos++] = 0.0;
    _poly1[pos++] = 0.0;
    _poly1[pos++] = 1.0;

    // point 1
    _poly1[pos++] = 0.5;
    _poly1[pos++] = -0.75;
    _poly1[pos++] = 0.0;
    _poly1[pos++] = 0.0;
    _poly1[pos++] = 1.0;

    // point 2
    _poly1[pos++] = 0.5;
    _poly1[pos++] = 0.5;
    _poly1[pos++] = 0.0;
    _poly1[pos++] = 1.0;
    _poly1[pos++] = 1.0;

    // Create and initialize a buffer object
    // (cache data in graphics card memory)
    glGenBuffers(1, &_buffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), _poly0, GL_STATIC_DRAW);

    // Create and initialize a buffer object
    // (cache data in graphics card memory)
    glGenBuffers(1, &_buffers[1]);
    glBindBuffer(GL_ARRAY_BUFFER, _buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), _poly1, GL_STATIC_DRAW);

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
    // layout value for vColor
    glEnableVertexAttribArray(1);

    // buffer for first triangle
    glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);

    // specify the actual vertex data from the buffer
    // first parameter is 0 because the layout value for vPosition in the vertex shader is 0
    // second and third parameters are 2 and GL_FLOAT because there are two values (x, y) per pixel that are floats
    // fourth parameter is GL_FALSE since the values are not normalized
    // fifth parameter is the number of bytes (stride) to get to the next vertex
    //   it is 5 * sizeof(GLfloat) since there are 5 (x, y, r, g, b) float values per pixel
    // sixth parameter is 0 bytes since since first value in array is the x coordinate
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(0));

    // note: the shader does not actually use this data but just showing how to pass additional information

    // specify the actual vertex data from the buffer
    // first parameter is 1 because the layout value for vColor in the vertex shader is 1
    // second and third parameters are 3 and GL_FLOAT because there are three values (r, g, b) per pixel that are floats
    // fourth parameter is GL_FALSE since the values are not normalized
    // fifth parameter is the number of bytes (stride) to get to the next vertex
    //   it is 5 * sizeof(GLfloat) since there are 5 (x, y, r, g, b) float values per pixel
    // sixth parameter is 2 * sizeof(GLfloat) bytes since since need to move past x, y values to get to r, g, b value
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(2 * sizeof(GLfloat)));

    GLint polyColorLocation;

    // get location for communicating polyColor
    polyColorLocation = glGetUniformLocation(_shaderProgram.program(), "polyColor");
    // draw polygon red
    glUniform3f(polyColorLocation, 1.0, 0.0, 0.0);

    // draw the buffer for the first triangle
    glDrawArrays(_drawType, 0, 3);

    // draw the second triangle
    // switch to buffer for second triangle
    glBindBuffer(GL_ARRAY_BUFFER, _buffers[1]);

    // after glBindBuffer, must call glVertexAttribPointer again
    // see comments for above calls for meaning of parameters
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(2 * sizeof(GLfloat)));

    //polyColorLocation = glGetUniformLocation(_shaderProgram.program(), "polyColor");
    // draw polygon blue
    glUniform3f(polyColorLocation, 0.0, 0.0, 1.0);

    // draw using the buffer for the second triangle
    glDrawArrays(_drawType, 0, 3);
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
        _drawType = GL_LINE_LOOP;
    }
}

//----------------------------------------------------------------------

