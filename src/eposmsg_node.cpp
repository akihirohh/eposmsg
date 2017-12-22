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
    std_msgs::MultiArrayDimension msg_dim;
    msg.data.push_back(0);
    msg.data.push_back(0);
    msg.data.push_back(0);
    msg.data.push_back(0);
    msg_dim.label = "Propulsion ENABLE";
    msg.layout.dim.push_back(msg_dim);
    msg_dim.label = "Propulsion DIRECTION";
    msg.layout.dim.push_back(msg_dim);
    msg_dim.label = "Propulsion PWM";
    msg.layout.dim.push_back(msg_dim);
    msg_dim.label = "Steering ANGLE";
    msg.layout.dim.push_back(msg_dim);


    while (ros::ok())
    {
        /**
         * This is a message object. You stuff it with data, and then publish it.
         */
        if(count < 10)
        {
            msg.data[0] = 1;
            msg.data[1] = 0;
            msg.data[2] = 20;
            msg.data[3] = 1500;
        }
        else if (count >= 10 && count < 15 )
        {
            msg.data[0] = 0;
        }
        else if (count >= 15 && count < 25 )
        {
            msg.data[0] = 1;
            msg.data[1] = 1;
            msg.data[2] = 40;
            msg.data[3] = -1500;
        }
        else if (count >= 25 && count < 35 )
        {
            msg.data[0] = 0;
            msg.data[1] = 0;
            msg.data[2] = 10;
            msg.data[3] = 0;
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