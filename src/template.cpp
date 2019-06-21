#include <Setpoint.h>
#include <Template.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "template");
    ros::NodeHandle nh;
    ros::NodeHandle nh_private("~");

    // Load frequency from parameter file
    double frequency;
    nh_private.param<double>("frequency", frequency, 20.0);
    ros::Rate rate(frequency);

    // Create instance of Controller
    Template controller(nh, nh_private, frequency);
    AttitudeSetpoint sp;

    // Initialize offboard mode
    controller.waitForConnection();
    controller.offboardAndArm();

    // actual control in offboard mode
    while(ros::ok()){
        sp = controller.generateSetpoint();
        controller.publishSetpoint(sp);
        ros::spinOnce();
        rate.sleep();
    }
    return 0;
}


//Generate the setpoint to publish
AttitudeSetpoint Template::generateSetpoint(){
    return sp;
}
