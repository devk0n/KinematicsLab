#include "Body.h"

Body::Body(const Eigen::Vector2d &initialPosition, const double initialAngle, const double mass, const double inertia)
  : m_position(initialPosition),
    m_velocity(Eigen::Vector2d::Zero()),
    m_acceleration(Eigen::Vector2d::Zero()),
    m_angle(initialAngle),
    m_angularVelocity(0.0),
    m_angularAcceleration(0.0),
    m_mass(mass),
    m_inertia(inertia),
    m_initialPosition(initialPosition),
    m_initialVelocity(Eigen::Vector2d::Zero()),
    m_initialAcceleration(Eigen::Vector2d::Zero()),
    m_initialAngle(initialAngle),
    m_initialAngularVelocity(0.0),
    m_initialAngularAcceleration(0.0) {
}

void Body::addVector(const Eigen::Vector2d &vector) {
  m_vectors.push_back(vector);
}

std::vector<Eigen::Vector2d> Body::getVectors() {
  return m_vectors;
}

Eigen::Vector2d Body::getPosition() const {
  return m_position;
}

double Body::getMass() const {
  return m_mass;
}

Eigen::Matrix<double, 1, 1> Body::getInertia() const {
  return m_inertia;
}

double Body::getAngle() const {
  return m_angle;
}
