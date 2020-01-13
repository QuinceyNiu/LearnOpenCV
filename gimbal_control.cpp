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
#include <cmath>
#include <stdio.h>

#include "gimbal_control.h"

namespace roborts_detection {

void GimbalContrl::Init(float x,float y,float z,float pitch,float yaw, float init_v, float init_k) {
  offset_.x = x;          //x坐标
  offset_.y = y;          //y坐标
  offset_.z = z;          //z坐标
  offset_pitch_ = pitch;  //俯仰角
  offset_yaw_ = yaw;      //航向角
  init_v_ = init_v;       //初始速度    
}

//air friction is considered
float GimbalContrl::BulletModel(float x, float v, float angle) { //x:m,v:m/s,angle:rad
  float y;
  y = (float)(x * tan(angle) - (GRAVITY * x * x) / ( 2 * v * v * cos(angle) * cos(angle)));  //xtan0 - (gx^2)/(2v^2cos0^2)
  return y;
}

//x:distance , y: height
float GimbalContrl::GetPitch(float x, float y, float v) {
  float y_temp, y_actual, dy;
  float a;
  y_temp = y;
  // by iteration
  for (int i = 0; i < 20; i++) { // 在20次循环之内使误差值稳定
    a = (float) atan2(y_temp, x); //求y_temp/x的反正切（atan2函数返回的是原点至点(x,y)的方位角，即与 x 轴的夹角）
    y_actual = BulletModel(x, v, a);  //求y的实际坐标
    dy = y - y_actual; //计算y的偏差值
    y_temp = y_temp + dy; 
    if (fabsf(dy) < 0.001) { //如果y的偏差值过小，就忽略不计，跳出循环
      break;
    }
    //printf("iteration num %d: angle %f,temp target y:%f,err of y:%f\n",i+1,a*180/3.1415926535,yTemp,dy);
  }
  return a; //返回经过for循环后的方位角

}

void GimbalContrl::Transform(cv::Point3f &postion, float &pitch, float &yaw) {
  pitch =
      -GetPitch((postion.z + offset_.z) / 100, -(postion.y + offset_.y) / 100, 15) + (float)(offset_pitch_ * 3.1415926535 / 180); //计算俯仰角
  //yaw positive direction :anticlockwise
  yaw = -(float) (atan2(postion.x + offset_.x, postion.z + offset_.z)) + (float)(offset_yaw_ * 3.1415926535 / 180); //计算航向角
}

} // roborts_detection