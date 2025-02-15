#include "ImGuiManager.h"

bool ImGuiManager::initialize(GLFWwindow *window) {
  // Setup ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  const ImGuiIO &io = ImGui::GetIO();
  (void) io;

  // Initialize ImGui for GLFW and OpenGL
  if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) { return false; }
  if (!ImGui_ImplOpenGL3_Init("#version 460")) { return false; }

  return true;
}

void ImGuiManager::renderGui() {
  // Start a new ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // Show custom UI elements
  ImGui::ShowDemoWindow();

  // Render ImGui
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::shutdown() {
  // Cleanup ImGui
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
