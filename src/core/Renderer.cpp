#include "Renderer.h"

bool Renderer::initialize() {
  m_initialized = true;
  return true;
}

void Renderer::beginFrame() const {
  // Tell OpenGL what color to clear the screen with
  glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
