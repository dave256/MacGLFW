//
//  GLFWBase.h
//  GLFWDemo
//
//  Created by David M. Reed on 12/12/17.
//  Copyright (c) 2015 David Reed. All rights reserved.
//

#ifndef __GLFWDemo__GLFWBase__
#define __GLFWDemo__GLFWBase__

#include <GLFW/glfw3.h>

class GLFWBase {

public:

    GLFWBase(GLFWwindow* window);


    /**
     enter the infinite run loop; should not need to override but set virtual in case you want to

     @param waitForEvents if ture, uses glfwWaitEvents() otherwise uses glfwPollEvents
     */
    virtual void runLoop(bool waitForEvents = true);


    /**
     override this method for displaying your scene
     called by the event loop automatically
     */
    virtual void render();

    // input callbacks
    // more details of parameters are here: http://www.glfw.org/docs/latest/input.html

    /**
     called when a key is pressed/released (default implementation quits on pressing Q or Esc)

     @param window the GLFW window
     @param key see http://www.glfw.org/docs/latest/group__keys.html
     @param scancode scancode is unique for every key, regardless of whether it has a key token. Scancodes are platform-specific but consistent over time, so keys will have different scancodes depending on the platform
     @param action one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
     @param mods one of GLFW_MOD_SHIFT GLFW_MOD_CONTROL GLFW_MOD_ALT GLFW_MOD_SUPER
     */
    virtual void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /**
     called when cursor position changes (called even when mouse button is not pressed)

     @param window the GLFW window
     @param xPos x coordinate of cursor (0 is left edge of window)
     @param yPos y coordinate of cursor (0 is top edge of window)
     */
    virtual void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

    /**
     called when cursor enters or exits window

     @param window the GLFW window
     @param entered 1 if entered, 0 if exited
     */
    virtual void cursorEnterCallback(GLFWwindow* window, int entered);

    /**
     called when a mouse button is pressed or released

     @param window the GLFW window
     @param button see: http://www.glfw.org/docs/latest/group__buttons.html
     @param action one of GLFW_PRESS or GLFW_RELEASE
     @param mods one of GLFW_MOD_SHIFT GLFW_MOD_CONTROL GLFW_MOD_ALT GLFW_MOD_SUPER
     @param xPos x coordinate of cursor (0 is left edge of window)
     @param yPos y coordinate of cursor (0 is top edge of window)
     */
    virtual void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, double xPos, double yPos);


    /**
     called when mouse/trackpad is scrolled

     @param window the GLFW window
     @param xOffset x coordinate within the window (0 is left edge of window)
     @param yOffset y coordinate within the window (0 is right edge of window)
     */
    virtual void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    /**
     called when OpenGL window resized

     @param window the GLFW window
     @param width new width of window
     @param height new height of window
     */
    virtual void windowSizeCallback(GLFWwindow *window, int width, int height);

    /**
     return the GLFW window

     @return the GLFW window
     */
    GLFWwindow* window() { return _window; }

protected:
    GLuint _vao;

private:
    GLFWwindow *_window;
    static void staticKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void staticCursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
    static void staticCursorEnterCallback(GLFWwindow* window, int entered);
    static void staticMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void staticScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    static void staticWindowSizeCallback(GLFWwindow *window, int width, int height);
};

#endif /* defined(__GLFWDemo__GLFWBase__) */
