#ifndef BODY_H
#define BODY_H
#include <Eigen/Dense>


class Body {
public:
  Body(const Eigen::Vector2d &initialPosition, double initialAngle, double mass, double inertia);

  void addVector(const Eigen::Vector2d &vector);

  std::vector<Eigen::Vector2d> getVectors();

  double getMass() const;

  Eigen::Matrix<double, 1, 1> getInertia() const;

  Eigen::Vector2d getPosition() const;

  double getAngle() const;

private:
  Eigen::Vector2d m_position;
  Eigen::Vector2d m_velocity;
  Eigen::Vector2d m_acceleration;

  double m_angle;
  double m_angularVelocity;
  double m_angularAcceleration;

  double m_mass;
  Eigen::Matrix<double, 1, 1> m_inertia;

  std::vector<Eigen::Vector2d> m_vectors;

  const Eigen::Vector2d m_initialPosition;
  const Eigen::Vector2d m_initialVelocity;
  const Eigen::Vector2d m_initialAcceleration;

  const double m_initialAngle;
  const double m_initialAngularVelocity;
  const double m_initialAngularAcceleration;
};


#endif // BODY_H
