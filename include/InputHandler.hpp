#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <iostream>
#include <GLFW/glfw3.h>
#include <Handler.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Hardy Har those fucking Callback function are the biggest thorn in my ass and this is the only solution i can even begin to implement and its honestly kind of annoying
static glm::vec2 mMousePos, mInitScenePos, mInitSelectPos;
static glm::vec2 mPanDelta;
static glm::mat4 *mView, *mProj;
static bool mPanning, mSelecting;

class InputHandler {

public:
    // Psuedo object esque thing
    InputHandler(GLFWwindow* window, glm::mat4* proj, glm::mat4* view);

    //Getters and Setters
    bool isPanning();
    void setPanning(bool panning);
    bool isSelecting();
    void setSelecting(bool selecting);
    glm::vec4 getSelectedArea();
    glm::vec2 getMousePos();
    void setMousePos(glm::vec2 mousePos);
    glm::vec2 getInitScenePos();
    void setInitScenePos(glm::vec2 scenePos);
    glm::vec2 getInitSelectPos();
    void setInitSelectPos(glm::vec2 selectPos);
    glm::vec2 getPanDelta();
    void setPanDelta(glm::vec2 panDelta);
    glm::mat4* getView();
    glm::mat4* getProj();

    // Input Callback Functions
    static void mousePosition(GLFWwindow* window, double xPos, double yPos);
    static void mousePressed(GLFWwindow* window, int button, int action, int mods);
    static void mouseScrolled(GLFWwindow * window, double xoffset, double yoffset);
    static void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);

};

#endif
