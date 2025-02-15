#include "Application.h"

Application::Application() = default;

bool Application::initialize() {
  if (!m_windowManager.initialize()) return false;
  if (!ImGuiManager::initialize(m_windowManager.getWindow())) return false;
  if (!m_renderer.initialize()) {
    std::cerr << "Failed to initialize renderer" << std::endl;
    return false;
  }
  return true;
}

void Application::run() const {
  while (!m_windowManager.shouldClose()) {
    WindowManager::pollEvents();

    m_renderer.beginFrame();

    ImGuiManager::renderGui();

    m_windowManager.swapBuffers();
  }
}
