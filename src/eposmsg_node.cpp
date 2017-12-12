#include <ros/ros.h>
#include <std_msgs/Int32MultiArray.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

int main(int argc, char* argv[])
{
    ros::init( argc, argv, "eposmsg_node");
    ros::NodeHandle nh;
    ros::Rate loop_rate(1);

    ros::Publisher chatter_pub = nh.advertise<std_msgs::Int32MultiArray>("eposmsg", 1000);
    int count = 0;
    std_msgs::Int32MultiArray msg;
    msg.data.push_back(0);
    msg.data.push_back(0);
    msg.data.push_back(0);
    msg.layout.dim.reserve(1);
    msg.layout.dim[0].label = "Propulsion ENABLE";


    while (ros::ok())
    {
        /**
         * This is a message object. You stuff it with data, and then publish it.
         */
        if(count < 10)
        {
            msg.data[0] = 1;
            msg.data[1] = 0;
            msg.data[2] = 1500;
        }
        else if (count >= 10 && count < 15 )
        {
            msg.data[0] = 0;
        }
        else if (count >= 15 && count < 25 )
        {
            msg.data[0] = 1;
            msg.data[1] = 1;
            msg.data[2] = -1500;
        }
        else if (count >= 25 && count < 35 )
        {
            msg.data[0] = 0;
        }
        else
        {
            count = 0;
        }

        chatter_pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
        count++;
    }


    return 0;

}