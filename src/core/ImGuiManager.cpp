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

// Function to render PhysicsEngine data in ImGui
void ImGuiManager::showPhysicsEngineData(PhysicsEngine &physicsEngine) {
    // Show gravity
    Eigen::Vector3d gravity = physicsEngine.getGravity();
    if (ImGui::CollapsingHeader("Gravity")) {
        ImGui::Text("Gravity:");
        ImGui::Text("X: %.3f, Y: %.3f, T: %.3f", gravity[0], gravity[1], gravity[2]);
    }

    // Show ground points
    const auto groundPoints = physicsEngine.getGroundPoints();
    if (ImGui::CollapsingHeader("Ground Points")) {
        if (groundPoints.empty()) {
            ImGui::Text("No ground points added.");
        } else {
            if (ImGui::BeginTable("GroundPointsTable", 3, ImGuiTableFlags_Borders)) {
                ImGui::TableSetupColumn("ID");
                ImGui::TableSetupColumn("Position X");
                ImGui::TableSetupColumn("Position Y");
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

    // Show bodies
    auto bodies = physicsEngine.getBodies();
    if (ImGui::CollapsingHeader("Bodies")) {
        if (bodies.empty()) {
            ImGui::Text("No bodies added.");
        } else {
            if (ImGui::BeginTable("BodiesTable", 3, ImGuiTableFlags_Borders)) {
                ImGui::TableSetupColumn("ID");
                ImGui::TableSetupColumn("Mass");
                ImGui::TableSetupColumn("Inertia");
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
    Eigen::MatrixXd massInertiaMatrix = physicsEngine.getMassInertiaMatrix();
    if (ImGui::CollapsingHeader("Mass Inertia Matrix")) {
        if (massInertiaMatrix.size() == 0) {
            ImGui::Text("Mass inertia matrix is empty.");
        } else {
            if (ImGui::BeginTable("MassInertiaMatrixTable", massInertiaMatrix.cols(),
                                  ImGuiTableFlags_Borders)) {
                for (int row = 0; row < massInertiaMatrix.rows(); ++row) {
                    ImGui::TableNextRow();
                    for (int col = 0; col < massInertiaMatrix.cols(); ++col) {
                        ImGui::TableSetColumnIndex(col);
                        ImGui::Text("%.3f", massInertiaMatrix(row, col));
                    }
                }
                ImGui::EndTable();
            }
        }
    }

    // Show right-hand vector
    Eigen::VectorXd rightHandVector = physicsEngine.getRightHandVector();
    if (ImGui::CollapsingHeader("Right Hand Vector")) {
        if (rightHandVector.size() == 0) {
            ImGui::Text("Right-hand vector is empty.");
        } else {
            if (ImGui::BeginTable("RightHandVectorTable", 1, ImGuiTableFlags_Borders)) {
                for (int row = 0; row < rightHandVector.rows(); ++row) {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%.3f", rightHandVector[row]);
                }
                ImGui::EndTable();
            }
        }
    }

    // Show solution
    Eigen::VectorXd solution = physicsEngine.getSolution();
    if (ImGui::CollapsingHeader("Solution Vector")) {
        if (solution.size() == 0) {
            ImGui::Text("Solution vector is empty.");
        } else {
            if (ImGui::BeginTable("SolutionVectorTable", 1, ImGuiTableFlags_Borders)) {
                for (int row = 0; row < solution.rows(); ++row) {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%.3f", solution[row]);
                }
                ImGui::EndTable();
            }
        }
    }

    Eigen::MatrixXd jacobian = physicsEngine.getJacobian();
    if (ImGui::CollapsingHeader("Jacobian")) {
        if (jacobian.size() == 0) {
            ImGui::Text("Jacobian matrix is empty.");
        } else {
            if (ImGui::BeginTable("JacobianTable", jacobian.cols(),
                                  ImGuiTableFlags_Borders)) {
                for (int row = 0; row < jacobian.rows(); ++row) {
                    ImGui::TableNextRow();
                    for (int col = 0; col < jacobian.cols(); ++col) {
                        ImGui::TableSetColumnIndex(col);
                        ImGui::Text("%.3f", jacobian(row, col));
                    }
                }
                ImGui::EndTable();
            }
        }
    }

    Eigen::MatrixXd systemMatrix = physicsEngine.getSystemMatrix();
    if (ImGui::CollapsingHeader("System Matrix")) {
        if (systemMatrix.size() == 0) {
            ImGui::Text("System matrix is empty.");
        } else {
            if (ImGui::BeginTable("SystemMatrixTable", systemMatrix.cols(),
                                  ImGuiTableFlags_Borders)) {
                for (int row = 0; row < systemMatrix.rows(); ++row) {
                    ImGui::TableNextRow();
                    for (int col = 0; col < systemMatrix.cols(); ++col) {
                        ImGui::TableSetColumnIndex(col);
                        ImGui::Text("%.3f", systemMatrix(row, col));
                    }
                }
                ImGui::EndTable();
            }
        }
    }
}

