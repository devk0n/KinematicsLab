#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>

#include "WindowManager.h"
#include "Renderer.h"
#include "ImGuiManager.h"

class Application {
public:
  Application();

  bool initialize();

  void run() const;

private:
  WindowManager m_windowManager;
  Renderer m_renderer;
  ImGuiManager m_imGuiManager;

  float m_lastFrameTime = 0.0f;

  void update(float deltaTime);
};

#endif // APPLICATION_H
