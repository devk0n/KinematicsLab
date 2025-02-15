#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glm/glm.hpp"

#include <GLFW/glfw3.h>

class ImGuiManager {
public:
  static bool initialize(GLFWwindow *window);

  static void renderGui();

private:
  static void shutdown();
};


#endif // IMGUIMANAGER_H
