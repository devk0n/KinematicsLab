#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <src/physics/PhysicsEngine.h>

#include "WindowManager.h"
#include "Renderer.h"
#include "ImGuiManager.h"

class Application {
public:
  Application();

  bool initialize();

  void run();

private:
  WindowManager m_windowManager;
  Renderer m_renderer;
  ImGuiManager m_imGuiManager;
  PhysicsEngine m_physicsEngine;

  float m_lastFrameTime;

  void update(float deltaTime);
};

#endif // APPLICATION_H
