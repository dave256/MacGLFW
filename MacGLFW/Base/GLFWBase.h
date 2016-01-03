//
//  GLFWBase.h
//  GLFWDemo
//
//  Created by David M. Reed on 2/18/15.
//  Copyright (c) 2015 David Reed. All rights reserved.
//

#ifndef __GLFWDemo__GLFWBase__
#define __GLFWDemo__GLFWBase__

#include <GLFW/glfw3.h>

class GLFWBase {

public:
    //
    GLFWBase(GLFWwindow* window);

    // should not need to overrride, but set virtual in case you do need to
    // if wait for events is true, uses glfwWaitEvents() otherwise uses glfwPollEvents
    virtual void runLoop(bool waitForEvents = true);

    /*! this is the method you generally override for displaying your scene called by event loop to do the rendering
     */
    virtual void render();

    // input callbacks
    // more details of parameters are here: http://www.glfw.org/docs/latest/input.html

    /*! called when a key is pressed/released (default implementation quits on pressing Q or Esc)
     * \param window the GLFW window
     * \param key see http://www.glfw.org/docs/latest/group__keys.html
     * \param scancode scancode is unique for every key, regardless of whether it has a key token. Scancodes are platform-specific but consistent over time, so keys will have different scancodes depending on the platform
     * \param action is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
     * \param mods one of GLFW_MOD_SHIFT GLFW_MOD_CONTROL GLFW_MOD_ALT GLFW_MOD_SUPER
     */
    virtual void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /*! callback when cursor position changes (called even when mouse button is not pressed)
     * \param window the GLFW window
     * \param xOffset position within the window (0 is top left corner of window
     * \param yOffset position within the window (0 is top left corner of window
     */
    virtual void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

    // called whenever cursor enters or leaves window
    virtual void cursorEnterCallback(GLFWwindow* window, int entered);

    /*! callback when a mouse button is pressed or released
     * \param window the GLFW window
     * \param button see: http://www.glfw.org/docs/latest/group__buttons.html
     * \param action one of GLFW_PRESS or GLFW_RELEASE
     * \param mods one of GLFW_MOD_SHIFT GLFW_MOD_CONTROL GLFW_MOD_ALT GLFW_MOD_SUPER
     * \param xPos position within the window (0 is top left corner of window
     * \param yPos position within the window (0 is top left corner of window     */
    virtual void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, double xPos, double yPos);

    /*! callbak when mouse/trackpad is scrolled
     * \param window the GLFW window
     * \param xOffset position within the window (0 is top left corner of window)
     * \param yOffset position within the window (0 is top left corner of window)
     */
    virtual void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    /*! callback when OpenGL window resized
     * \param window the GLFW window
     * \param width new width of OpenGL window
     * \param height new height of OpenGL window
     */
    virtual void windowSizeCallback(GLFWwindow *window, int width, int height);

    // access the GLFWwindow
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
