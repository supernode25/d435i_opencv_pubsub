#include "d435_class.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "d435_img_node");
    D435Image d435;
    ros::spin();
     
    return 0;
}