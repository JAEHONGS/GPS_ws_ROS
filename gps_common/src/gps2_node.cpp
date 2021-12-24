#include <ros/ros.h>
#include <iostream>
#include <stdio.h>
#include "conversions.h"

int main(int argc, char **argv) 
	{
		ros::init(argc, argv, "gps2_node");
 		ros::NodeHandle nh;
	 	ros::Rate loop_rate(10);
         

                double test = 0.0; 
         	
		test = gps_common::WGS84_A;
		printf("%f\n", test);

	return 0;

}

