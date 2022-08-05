#include<iostream>
#include<cmath>
#include<Eigen/Core>
#include<Eigen/Dense>
#include "sophus/so3.h"
#include "sophus/se3.h"
using namespace std;
using namespace Eigen;
int main()
{
Eigen::Vector3d w(0.01, 0.02, 0.03);
cout << "w is "<<w<<endl;

Eigen::Matrix3d Rotation = Eigen::Matrix3d::Identity();   //设置原来的旋转矩阵为单位帧

cout << "set original rotation matrix is \n" << Rotation << endl;
Eigen::Quaterniond q(Rotation);    //原来的四元数为1，0，0，0

cout << " set the Original Quaternion is \n" << q.coeffs().transpose() << endl;


Sophus::SO3 SO3_R(Rotation);


Sophus::SO3 SO3_update_R = SO3_R * Sophus::SO3::exp(w);  //在李群上的更新
cout << "exp result  is \n" << SO3_update_R.matrix() << endl;


// double theta = sqrt(w.transpose()*w);   //这个为四元数的右乘模型的更新结果是一样的
// Vector3d uw = w/theta; 
// AngleAxisd axis_u(theta, uw);
// Eigen::Quaterniond dq(axis_u);
Quaterniond dq(1, w(0) / 2, w(1) / 2, w(2) / 2);   //按照第二种方式更新，第二种方式实际是四元数的一种积分方式。
Eigen::Quaterniond q_update = q * dq;
cout << "result rotation matrix in quaterniond  is \n" << q_update.matrix() << endl;

cout<<"difference is "<<(SO3_R.matrix() -  q_update.matrix())<<endl;

}
