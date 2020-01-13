/****************************************************************************
 *  Copyright (C) 2019 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
#ifndef ROBORTS_DETECTION_GIMBAL_CONTROL_H
#define ROBORTS_DETECTION_GIMBAL_CONTROL_H
#include <iostream>
#include <opencv2/opencv.hpp>

namespace roborts_detection{

const double PI = 3.1415926535; //圆周率
const float GRAVITY = 9.78;     //重力加速度


/*
 * @brief The class can make a transformation: the 3D position of enemy -->  pitch,yaw angle of gimbal.
 * 该类进行了一个转换：敌人的3D坐标————> 云台的俯仰，航向角
 */

class GimbalContrl
{
 private:
  /*
   * @brief Calculate the actual y value with air resistance 计算在空气阻力下y的实际值
   * @param x the distance 距离
   * @param v Projectile velocity 弹丸速度
   * @param angle Pitch angle 俯仰角
   * @return The actual y value in the gimbal coordinate 在云台坐标内y的实际值
   */
  float BulletModel(float x,float v,float angle);
  /**
   * @brief Get the gimbal control angle 得到云台的控制角
   * @param x Distance from enemy(the armor selected to shoot) to gimbal 敌人与云台之间的距离
   * @param y Value of y in gimbal coordinate. 在云台坐标内y的值
   * @param v Projectile velocity 弹丸速度
   * @return Gimbal pitch angle 云台的俯仰角 
   */
  float GetPitch(float x,float y,float v);

 public:
  /**
   * @brief Init the Transformation matrix from camera to gimbal //TODO: write in ros tf
   * @param x Translate x
   * @param y Translate y
   * @param z Translate z
   * @param pitch Rotate pitch 旋转螺距
   * @param yaw Rotate yaw 旋转航向
   */
  void Init(float x,float y,float z,float pitch,float yaw, float init_v, float init_k);
  /**
   * @brief Get the gimbal control info.
   * @param postion Enemy position(actually it should be the target armor).
   * @param pitch Input and output actual pitch angle
   * @param yaw Input and output actual yaw angle
   */
  void Transform(cv::Point3f &postion,float &pitch,float &yaw);

 private:
  //! Transformation matrix between camera coordinate system and gimbal coordinate system.
  //相机坐标系和云台架坐标系之间的转换矩阵。
  //! Translation unit: cm 单位：厘米
  cv::Point3f offset_;
  //! Rotation matrix unit: degree 旋转矩阵单位：矩阵
  float offset_pitch_;
  float offset_yaw_;

  //! Initial value
  float init_v_;
  float init_k_;

};

} //namespace roborts_detection

#endif //ROBORTS_DETECTION_GIMBAL_CONTROL_H