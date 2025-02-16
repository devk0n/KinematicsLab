#include "Application.h"

#include <src/physics/GroundPoint.h>
#include <src/physics/PhysicsEngine.h>

Application::Application() : m_physicsEngine(Eigen::Vector3d(0.0, -9.81, 0.0)), m_lastFrameTime(0.0f) {
}

bool Application::initialize() {
  if (!m_windowManager.initialize()) return false;
  if (!m_imGuiManager.initialize(m_windowManager.getWindow())) return false;
  if (!m_renderer.initialize()) {
    std::cerr << "Failed to initialize renderer" << std::endl;
    return false;
  }

  // System setup
  const GroundPoint groundPoint(Eigen::Vector2d(0.0, 0.0)); // s1Am

  Body body(Eigen::Vector2d(0.5, 0.0), 0.0, 7.0, 1.4);
  body.addVector(Eigen::Vector2d(-0.5, 0.0)); // s1Am

  Body body1(Eigen::Vector2d(1.5, 0.0), 0.0, 14.0, 2.8);

  m_physicsEngine.addGroundPoint(groundPoint);
  m_physicsEngine.addBody(body);

  m_physicsEngine.initialize();

  m_physicsEngine.addConstraint(0, 0);


  return true;
}

void Application::run() {
  while (!m_windowManager.shouldClose()) {
    WindowManager::pollEvents();

    m_renderer.beginFrame();
    m_imGuiManager.renderGui(m_physicsEngine);

    m_windowManager.swapBuffers();
  }
}
