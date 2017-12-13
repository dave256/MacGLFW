//
//  ShaderProgram.h
//  
//
//  Created by David Reed on 2/15/15.
//  Copyright (c) 2015 David Reed. All rights reserved.
//

#ifndef __MacGLFW__ShaderProgram__
#define __MacGLFW__ShaderProgram__

#include <string>

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

class ShaderProgram {

public:
    ShaderProgram() { _program = 0; }

    /**
     read vertex and fragment shader files to create the shader program

     @param vertexShaderFilePath path to vertex shader
     @param fragmentShaderFilePath path to fragment shader
     */
    void makeProgramFromShaderFiles(std::string vertexShaderFilePath, std::string fragmentShaderFilePath);

    /**
     create vertex and fragment shaders from strings; called by makeProgramFromShaderFiles

     @param vertexShader string containing the vertex shader
     @param fragmentShader string containing the fragment shader
     */
    void makeProgramFromShaderStrings(std::string vertexShader, std::string fragmentShader);

    /**
     compile the shader; called by makeProgramShaderFromStrings

     @param shaderCode string containing the shader code
     @param shaderType type of shader to create
     */
    void compileShader(std::string shaderCode, GLenum shaderType) const;

    /**
     return the shader program identifier

     @return the shader program identifier
     */
    GLuint program() const { return _program; }

    /**
     uses this shader program
     */
    void useProgram() const { glUseProgram(_program); }

protected:
    GLuint _program;
};

#endif /* defined(__MacGLFW__ShaderProgram__) */
