#include "PhysicsEngine.h"

#include <iostream>
#include <utility>
#include <glm/detail/type_vec3.hpp>

PhysicsEngine::PhysicsEngine(Eigen::Vector3d gravity)
  : m_gravity(std::move(gravity)),
    m_initialized(false) {
}

void PhysicsEngine::initialize() {
  if (m_bodies.empty()) return;
  constexpr int dof = 3;
  const int numBodies = m_bodies.size();
  constexpr int numConstraints = 2;

  m_systemMatrix.resize(numBodies * dof + numConstraints, numBodies * dof + numConstraints);
  m_systemMatrix.setZero();

  m_massInertiaMatrix.resize(numBodies * dof, numBodies * dof);
  m_massInertiaMatrix.setZero();

  m_jacobian.resize(numConstraints, numBodies * dof);
  m_jacobian.setZero();

  m_rightHandVector.resize(numBodies * dof + numConstraints);
  m_rightHandVector.setZero();

  m_solution.resize(numBodies * dof + numConstraints);
  m_solution.setZero();

  for (int i = 0; i < numBodies; i++) {
    const int n = 3 * i;
    m_massInertiaMatrix.block(n, n, 2, 2) = Eigen::Matrix2d::Identity() * m_bodies[i].getMass();
    m_massInertiaMatrix.block(2 + n, 2 + n, 1, 1) = m_bodies[i].getInertia();

    m_rightHandVector.segment(n, 3) = m_gravity;
  }

  m_systemMatrix.block(0, 0, numBodies * dof, numBodies * dof) = m_massInertiaMatrix;

  m_initialized = true;
}

void PhysicsEngine::addGroundPoint(const GroundPoint &groundPoint) {
  m_groundPoints.push_back(groundPoint);
}

void PhysicsEngine::addBody(const Body &body) {
  m_bodies.push_back(body);
}

Eigen::Matrix2d PhysicsEngine::rotationMatrixB(double theta) {
  Eigen::Matrix2d a;
  a << -std::sin(theta), -std::cos(theta),
      std::cos(theta), -std::sin(theta);
  return a;
}

void PhysicsEngine::addConstraint(const int bodyID, const int vectorID) {
  Body body = m_bodies[bodyID];

  m_jacobian.block(0, 0, 2, 2) = Eigen::Matrix2d::Identity();

  m_jacobian.block(0, 2, 2, 1) = rotationMatrixB(body.getAngle()) * body.getVectors()[vectorID];
}


std::vector<Body> PhysicsEngine::getBodies() const {
  return m_bodies;
}

std::vector<GroundPoint> PhysicsEngine::getGroundPoints() const {
  return m_groundPoints;
}

Eigen::Vector3d PhysicsEngine::getGravity() {
  return m_gravity;
}

Eigen::MatrixXd PhysicsEngine::getMassInertiaMatrix() {
  return m_massInertiaMatrix;
}

Eigen::VectorXd PhysicsEngine::getRightHandVector() {
  return m_rightHandVector;
}

Eigen::VectorXd PhysicsEngine::getSolution() {
  return m_solution;
}

Eigen::MatrixXd PhysicsEngine::getJacobian() {
  return m_jacobian;
}

Eigen::MatrixXd PhysicsEngine::getSystemMatrix() {
  return m_systemMatrix;
}




