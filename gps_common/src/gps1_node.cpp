#include <ros/ros.h>
#include <iostream>
#include <stdio.h>
#include "conversions.h"
#include <sensor_msgs/NavSatFix.h>
#include <std_msgs/Float64.h>
//#include <std_msgs/Float64MultiArray.h>

double latitude = 0.0;
double longitude = 0.0;
bool button = false;

using namespace std;

void PositionCallBack(const sensor_msgs::NavSatFix& msg){

    button = true;

    latitude = msg.latitude;
    longitude = msg.longitude;
    cout<<fixed;
    cout.precision(10);

}

/*void HeadingCallBack(const sensor_msgs::NavSatFix& msg){

  heading = msg.heading;
}*/

int main(int argc, char **argv) 
{
    ros::init(argc, argv, "gps1_node");
    ros::NodeHandle nh;
    ros::Rate loop_rate(10);

    ros::Subscriber pose_sub = nh.subscribe("fix",10,PositionCallBack);
    //ros::Subscriber heading_sub = nh.subscribe("heading",10,HeadingCallBack);
    ros::Publisher gpsposex_pub = nh.advertise<std_msgs::Float64>("gpsposex", 1000);
    ros::Publisher gpsposey_pub = nh.advertise<std_msgs::Float64>("gpsposey", 1000);
    //ros::Publisher gpspose_pub = nh.advertise<std_msgs::Float64MultiArray>("gpspose", 1000);

    double utm_x;
    double utm_y;
    double pre_xy[2] = {0};
    double cur_xy[2] = {0};

    while ( ros::ok() ) {

        cout<<fixed;
        cout.precision(10);


      if (latitude != 0 && button == true) {
          gps_common::UTM(latitude,longitude,&utm_x,&utm_y);
          //gps_common::UTM(35.1752281,126.899521,&utm_x,&utm_y);
          printf("%f, %f\n", utm_x,utm_y);
          //cout<<utm_y<<endl;
      }


      //std_msgs::Float64MultiArray gpspose;
      std_msgs::Float64 gpsposex;
      std_msgs::Float64 gpsposey;


      gpsposex.data= utm_x;
      gpsposey.data= utm_y;

      //gpspose_pub.publish(gpspose);
      gpsposex_pub.publish(gpsposex);
      gpsposey_pub.publish(gpsposey);

      button = false;

      ros::spinOnce();
      loop_rate.sleep();
    }
    return 0;

}
