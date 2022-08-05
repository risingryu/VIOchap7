//
// Created by hyj on 18-11-11.
//
#include <iostream>
#include<fstream>
#include <vector>
#include <random>  
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Eigenvalues>
using std::cout;
using std::endl;
struct Pose
{
    Pose(Eigen::Matrix3d R, Eigen::Vector3d t):Rwc(R),qwc(R),twc(t) {};
    Eigen::Matrix3d Rwc;
    Eigen::Quaterniond qwc;
    Eigen::Vector3d twc;

    Eigen::Vector2d uv;    // 这帧图像观测到的特征坐标
};
int main()
{
    double w_sigma;                 // 噪声Sigma值
    cout<<"enter noise varience (unit pixel)"<<endl;
    std::cin>>w_sigma;




    int poseNums = 10;
    double radius = 8;
    double fx = 1.;
    double fy = 1.;
    std::vector<Pose> camera_pose;
    for(int n = 0; n < poseNums; ++n ) {
        double theta = n * 2 * M_PI / ( poseNums * 4); // 1/4 圆弧
        // 绕 z轴 旋转
        Eigen::Matrix3d R;
        R = Eigen::AngleAxisd(theta, Eigen::Vector3d::UnitZ());
        Eigen::Vector3d t = Eigen::Vector3d(radius * cos(theta) - radius, radius * sin(theta), 1 * sin(2 * theta));
        camera_pose.push_back(Pose(R,t));
    }

    // 随机数生成 1 个 三维特征点
    std::default_random_engine generator;
    std::uniform_real_distribution<double> xy_rand(-4, 4.0);
    std::uniform_real_distribution<double> z_rand(8., 10.);
    std::normal_distribution<double> noise(0.,w_sigma/2000);
    double tx = xy_rand(generator);
    double ty = xy_rand(generator);
    double tz = z_rand(generator);

    Eigen::Vector3d Pw(tx, ty, tz);
    // 这个特征从第三帧相机开始被观测，i=3
    int start_frame_id = 3;
    cout<<"observe frame num:"<<endl;
    std::cin>>start_frame_id;
    int end_frame_id = poseNums;
    for (int i = start_frame_id; i < end_frame_id; ++i) {
        Eigen::Matrix3d Rcw = camera_pose[i].Rwc.transpose();
        Eigen::Vector3d Pc = Rcw * (Pw - camera_pose[i].twc);
                
                double n = noise(generator);

        double x = Pc.x()+n;
        double y = Pc.y()+n;
        double z = Pc.z()+n;

        camera_pose[i].uv = Eigen::Vector2d(x/z,y/z);
    }
    
    /// TODO::homework; 请完成三角化估计深度的代码
    // 遍历所有的观测数据，并三角化
    Eigen::Vector3d P_est;           // 结果保存到这个变量
    P_est.setZero();
    /* your code begin */

    //首先构造D矩阵的结构：

    Eigen::MatrixXd D((poseNums-start_frame_id) * 2, 4);


       for (int i = start_frame_id; i < end_frame_id; i++) 
       {
               Eigen::MatrixXd P = Eigen::MatrixXd::Zero(3,4);
               Eigen::Matrix3d Rcw= camera_pose[i].Rwc.transpose();
                Eigen::Vector3d tcw =  -Rcw * camera_pose[i].twc;
           P.block<3, 3>(0, 0) = Rcw;
           P.block<3, 1>(0, 3) = tcw;
            double u=camera_pose[i].uv[0];
            double v=camera_pose[i].uv[1];
           D.row((i-start_frame_id)*2) =  u*P.row(2)-P.row(0);
           D.row((i-start_frame_id)*2+1) =  v*P.row(2)-P.row(1);
       }
        Eigen::MatrixXd DTD = D.transpose()*D;
        //Eigen::MatrixXd DTD =D;
           Eigen::JacobiSVD<Eigen::MatrixXd> svd(DTD, Eigen::ComputeThinU | Eigen::ComputeThinV);
           auto res_U = svd.matrixU();
           auto res_V = svd.matrixV();
           cout<<" U  IS    :"<<endl<<res_U<<endl;
           auto sigema = svd.singularValues();
           cout<<"singula _value is "<<sigema<<endl;
            auto result = res_U.rightCols(1);
            result=result / result(3);
            P_est<<result(0),result(1),result(2);
            std::cout << "res=" << P_est << std::endl;

    


 
    /* your code end */
    
    std::cout <<"ground truth: \n"<< Pw.transpose() <<std::endl;
    std::cout <<"your result: \n"<< P_est.transpose() <<std::endl;
    // TODO:: 请如课程讲解中提到的判断三角化结果好坏的方式，绘制奇异值比值变化曲线
    if(sigema(2)/sigema(3)>100)
    {
        cout<<sigema(2)/sigema(3)<<"good result";

    }
    std::ofstream outFile;
    outFile.open("1.txt",std::ios::app);
    outFile<<"像素误差为: "<<w_sigma<<"             "<<"sigema 3 =  "<<sigema(2)<<"              "<<"sigema 4 = "<<sigema(3)
                <<" ,比值为3/4： "<<sigema(2)/sigema(3)<<endl;
    

outFile.close();
outFile.open("2.txt",std::ios::app);
    outFile<<"像素误差为: "<<w_sigma<<"        观测帧数     "<<poseNums-start_frame_id<<" sigema 3 =  "<<sigema(2)<<"              "<<"sigema 4 = "<<sigema(3)
                <<" ,比值为3/4： "<<sigema(2)/sigema(3)<<endl;
    return 0;
}
