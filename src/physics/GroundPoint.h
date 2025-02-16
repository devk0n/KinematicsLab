#ifndef GROUNDPOINT_H
#define GROUNDPOINT_H

#include <Eigen/Dense>

class GroundPoint {
public:
  explicit GroundPoint(const Eigen::Vector2d &position);

  const Eigen::Vector2d &getPosition() const;

private:
  const Eigen::Vector2d m_position;
};


#endif // GROUNDPOINT_H
