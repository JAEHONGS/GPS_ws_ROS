#include <ros/ros.h>
#include <iostream>
#include <stdio.h>
#include "conversions.h"

int main(int argc, char **argv) 
	{
		ros::init(argc, argv, "gps1_node");
 		ros::NodeHandle nh;
	 	ros::Rate loop_rate(10);
         

                double test = 0.0; 
         	
		double x;
		double y;

		gps_common::UTM(35.180319,126.908465,&x,&y);
		printf("%f, %f\n", x, y);

	return 0;

}

