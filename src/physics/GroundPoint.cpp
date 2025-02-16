#include "GroundPoint.h"

GroundPoint::GroundPoint(const Eigen::Vector2d &position) : m_position(position) {
}

const Eigen::Vector2d &GroundPoint::getPosition() const {
  return m_position;
}

