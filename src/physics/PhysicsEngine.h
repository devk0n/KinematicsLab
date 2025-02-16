#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>
#include <Eigen/Dense>

#include "GroundPoint.h"
#include "Body.h"

class PhysicsEngine {
public:
  explicit PhysicsEngine(Eigen::Vector3d gravity);

  void initialize();

  void addGroundPoint(const GroundPoint &groundPoint);

  void addBody(const Body &body);

  void addConstraint(int bodyID, int vectorID);

  Eigen::Matrix2d rotationMatrixB(double theta);

  std::vector<GroundPoint> getGroundPoints() const;

  std::vector<Body> getBodies() const;

  Eigen::Vector3d getGravity();

  Eigen::MatrixXd getMassInertiaMatrix();

  Eigen::VectorXd getRightHandVector();

  Eigen::VectorXd getSolution();

  Eigen::MatrixXd getJacobian();

  Eigen::MatrixXd getSystemMatrix();

private:
  std::vector<GroundPoint> m_groundPoints;
  std::vector<Body> m_bodies;

  Eigen::Vector3d m_gravity;

  bool m_initialized;

  Eigen::MatrixXd m_systemMatrix;

  Eigen::MatrixXd m_massInertiaMatrix;
  Eigen::VectorXd m_rightHandVector;
  Eigen::VectorXd m_solution;

  Eigen::MatrixXd m_jacobian;
};


#endif // PHYSICSENGINE_H
