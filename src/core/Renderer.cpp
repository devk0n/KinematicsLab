#include "Renderer.h"
#include <iostream>
#include <src/physics/PhysicsEngine.h>
#include "glad/glad.h"

bool Renderer::initialize() {
    // Load shaders
    m_shader = new Shader("C:/Users/devkon/CLionProjects/KinematicsLab/assets/shaders/axes.vert.glsl",
                          "C:/Users/devkon/CLionProjects/KinematicsLab/assets/shaders/axes.frag.glsl");
    if (!m_shader) {
        std::cerr << "Failed to load shaders" << std::endl;
        return false;
    }

    m_initialized = true;
    return true;
}

void Renderer::beginFrame() const {
    glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const PhysicsEngine &physicsEngine) {
    if (!m_initialized) return;
}
