#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glm/glm.hpp"

#include <GLFW/glfw3.h>
#include "src/physics/PhysicsEngine.h"

class ImGuiManager {
public:
  bool initialize(GLFWwindow *window);

  void renderGui(PhysicsEngine &physicsEngine);

  void showPhysicsEngineData(PhysicsEngine &physicsEngine);

private:
  void shutdown();
};


#endif // IMGUIMANAGER_H
