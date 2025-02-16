#include "ImGuiManager.h"

#include <src/physics/Body.h>
#include <src/physics/PhysicsEngine.h>

bool ImGuiManager::initialize(GLFWwindow *window) {
    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    // Initialize ImGui for GLFW and OpenGL
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) { return false; }
    if (!ImGui_ImplOpenGL3_Init("#version 460")) { return false; }

    return true;
}

void ImGuiManager::renderGui(PhysicsEngine &physicsEngine) {
    // Start a new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Show custom UI elements
    ImGui::ShowDemoWindow();
    showPhysicsEngineData(physicsEngine);

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

// Helper function to display a matrix in a table
void displayMatrixTable(const std::string &title, const Eigen::MatrixXd &matrix) {
    if (ImGui::CollapsingHeader(title.c_str())) {
        if (matrix.size() == 0) {
            ImGui::Text("%s is empty.", title.c_str());
        } else {
            std::string sizeLabel = "Size: " + std::to_string(matrix.rows()) + "x" + std::to_string(matrix.cols());
            ImGui::Text("%s", sizeLabel.c_str());

            if (ImGui::BeginTable((title + "Table").c_str(), matrix.cols(), ImGuiTableFlags_Borders)) {
                for (int row = 0; row < matrix.rows(); ++row) {
                    ImGui::TableNextRow();
                    for (int col = 0; col < matrix.cols(); ++col) {
                        ImGui::TableSetColumnIndex(col);
                        ImGui::Text("%.3f", matrix(row, col));
                    }
                }
                ImGui::EndTable();
            }
        }
    }
}

// Helper function to display a vector in a table
void displayVectorTable(const std::string &title, const Eigen::VectorXd &vector) {
    if (ImGui::CollapsingHeader(title.c_str())) {
        if (vector.size() == 0) {
            ImGui::Text("%s is empty.", title.c_str());
        } else {
            std::string sizeLabel = "Size: " + std::to_string(vector.rows());
            ImGui::Text("%s", sizeLabel.c_str());

            if (ImGui::BeginTable((title + "Table").c_str(), 1, ImGuiTableFlags_Borders)) {
                for (int row = 0; row < vector.rows(); ++row) {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%.3f", vector[row]);
                }
                ImGui::EndTable();
            }
        }
    }
}

// Function to render PhysicsEngine data in ImGui
void ImGuiManager::showPhysicsEngineData(PhysicsEngine &physicsEngine) {
    ImGui::SetNextItemOpen(true);

    // Show gravity
    Eigen::Vector3d gravity = physicsEngine.getGravity();
    if (ImGui::CollapsingHeader("Gravity")) {
        ImGui::Text("Gravity:");
        ImGui::Text("X: %.3f, Y: %.3f, Z: %.3f", gravity[0], gravity[1], gravity[2]);
    }
    ImGui::SetNextItemOpen(true);

    // Show ground points
    const auto groundPoints = physicsEngine.getGroundPoints();
    if (ImGui::CollapsingHeader("Ground Points")) {
        if (groundPoints.empty()) {
            ImGui::Text("No ground points added.");
        } else {
            if (ImGui::BeginTable("GroundPointsTable", 3, ImGuiTableFlags_Borders)) {
                ImGui::TableSetupColumn("ID");
                ImGui::TableSetupColumn("Position X (m)");
                ImGui::TableSetupColumn("Position Y (m)");
                ImGui::TableHeadersRow();

                for (size_t i = 0; i < groundPoints.size(); ++i) {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%zu", i);
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%.3f", groundPoints[i].getPosition().x()); // Assuming getPosition() exists
                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("%.3f", groundPoints[i].getPosition().y());
                }
                ImGui::EndTable();
            }
        }
    }
    ImGui::SetNextItemOpen(true);

    // Show bodies
    auto bodies = physicsEngine.getBodies();
    if (ImGui::CollapsingHeader("Bodies")) {
        if (bodies.empty()) {
            ImGui::Text("No bodies added.");
        } else {
            if (ImGui::BeginTable("BodiesTable", 3, ImGuiTableFlags_Borders)) {
                ImGui::TableSetupColumn("ID");
                ImGui::TableSetupColumn("Mass (kg)");
                ImGui::TableSetupColumn("Inertia (kgm^2)");
                ImGui::TableHeadersRow();

                for (size_t i = 0; i < bodies.size(); ++i) {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%zu", i);
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%.3f", bodies[i].getMass()); // Assuming getMass() exists
                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("%.3f", bodies[i].getInertia().value()); // Assuming getInertia() exists
                }
                ImGui::EndTable();
            }
        }
    }

    // Show mass inertia matrix
    ImGui::SetNextItemOpen(true);
    displayMatrixTable("Mass Inertia Matrix", physicsEngine.getMassInertiaMatrix());

    // Show right-hand vector
    ImGui::SetNextItemOpen(true);
    displayVectorTable("Right Hand Vector", physicsEngine.getRightHandVector());

    // Show solution vector
    ImGui::SetNextItemOpen(true);
    displayVectorTable("Solution Vector", physicsEngine.getSolution());

    // Show Jacobian matrix with size in the title
    ImGui::SetNextItemOpen(true);
    Eigen::MatrixXd jacobian = physicsEngine.getJacobian();
    std::string jacobianTitle = "Jacobian Matrix (Size: " + std::to_string(jacobian.rows()) + "x" +
                                std::to_string(jacobian.cols()) + ")";
    displayMatrixTable(jacobianTitle, jacobian);

    // Show system matrix
    ImGui::SetNextItemOpen(true);
    displayMatrixTable("System Matrix", physicsEngine.getSystemMatrix());
}
