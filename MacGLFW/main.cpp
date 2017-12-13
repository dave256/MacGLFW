//
//  main.cpp
//  MacGLFW
//
//  Created by David M Reed on 12/12/17.
//  Copyright © 2017 David M Reed. All rights reserved.
//

#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLFWDemo.h"

using std::cerr;
using std::endl;

//----------------------------------------------------------------------

static void errorCallback(int error, const char* description)
{
    cerr << description << endl;
    //fputs(description, stderr);
}

//----------------------------------------------------------------------

int main(int argc, const char * argv[]) {

    GLFWwindow* window;
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // try to get a fairly recent version of OpenGL
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //  create the GLFW window
    window = glfwCreateWindow(640, 480, "OpenGL Demo", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // set it to be the current OpenGL context
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    // global variable declared in GLEW files
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        cerr << "failed to initialize GLEW\n";
        exit(EXIT_FAILURE);
    }

    // specify refresh rate (normally 1)
    glfwSwapInterval(1);

    // output some information about OpenGL version
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    fprintf(stderr, "OpenGL version received: %d.%d.%d\n", major, minor, rev);
    fprintf(stderr, "%s", glfwGetVersionString());
    cerr << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    cerr << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cerr << "Vendor: " << glGetString(GL_VENDOR) << endl;
    cerr << "Renderer: " << glGetString(GL_RENDERER) << endl;
    GLint textureUnits;
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &textureUnits);
    cerr << "Num texture units: " << textureUnits << endl;

    // create the class
    GLFWDemo *glBase = new GLFWDemo(window);
    // do an setup
    glBase->setup();
    // and enter the run loop
    glBase->runLoop();
}
