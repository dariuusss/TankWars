﻿#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{
    // TODO(student): Never forget to initialize class variables!
    m1::Lab1::r = 0;
    m1::Lab1::g = 0;
    m1::Lab1::b = 1;
    m1::Lab1::x = 1.0f;
    m1::Lab1::y = 0.5f;
    m1::Lab1::z = 2.0f;
    m1::Lab1::mid_air = 0;
    m1::Lab1::jump = 0;
    m1::Lab1::height = 0.0f;
    m1::Lab1::init_jump = 0;
    strcpy(m1::Lab1::name, "box");

}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;

        Mesh* mesh2 = new Mesh("iepure");
        mesh2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "animals"), "bunny.obj");
        meshes[mesh2->GetMeshID()] = mesh2;
    }

    // TODO(student): Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.

}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).

    glClearColor(m1::Lab1::r, m1::Lab1::g, m1::Lab1::b, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object

    RenderMesh(meshes[m1::Lab1::name], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

    // Render the object again but with different properties
    RenderMesh(meshes[m1::Lab1::name], glm::vec3(-1, 0.5f, 0));

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.


    

    RenderMesh(meshes["iepure"], glm::vec3(m1::Lab1::y, m1::Lab1::x + m1::Lab1::height, m1::Lab1::z), glm::vec3(0.03f)); // factorul 3 e ala de scalare


    if (m1::Lab1::init_jump == 1) {
        m1::Lab1::jump = 1;
        m1::Lab1::init_jump = 0;
        m1::Lab1::mid_air = 1;
    }

    if (m1::Lab1::jump == 1) {

        if (m1::Lab1::mid_air == 1) {
            if (m1::Lab1::height < 3.0f)
                if(m1::Lab1::height < 1.0f)
                    m1::Lab1::height += 0.20f;
                else
                    m1::Lab1::height += 0.10f;
            else {
                m1::Lab1::mid_air = 0;
            }
        } else {
            if (m1::Lab1::height > 0.0f)
                if(m1::Lab1::height >= 1.0f)
                    m1::Lab1::height -= 0.10f;
                else
                    m1::Lab1::height -= 0.20f;
            if (m1::Lab1::height == 0.0f)
                m1::Lab1::jump = 0;
        }

    }
    

}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.

    if (window->KeyHold(GLFW_KEY_W)) {
        m1::Lab1::x += 0.5f * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        m1::Lab1::x -= 0.5f * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        m1::Lab1::y -= 0.5f * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        m1::Lab1::y += 0.5f * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_E)) {
        m1::Lab1::z += 0.5f * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_Q)) {
        m1::Lab1::z -= 0.5f * deltaTime;
    }

}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_F) {
        // TODO(student): Change the values of the color components.
        m1::Lab1::g = 1;
        m1::Lab1::b = 0;
    }

    if (key == GLFW_KEY_J) {
        strcpy(m1::Lab1::name, "iepure");
    }

    if (key == GLFW_KEY_T) {
        m1::Lab1::init_jump = 1;
    }

    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.

}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
