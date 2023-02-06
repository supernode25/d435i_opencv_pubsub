#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <opencv2/highgui/highgui.hpp>


class D435Image
{
    int  esc_Waitkey;
    ros::NodeHandle node;
    ros::Subscriber image_sub;   
    ros::Subscriber test_image_sub; 
    ros::Publisher image_pub;   
public:
    D435Image()
    {          
      image_sub = node.subscribe("/camera/color/image_raw",10,&D435Image::ImageCallback,this);
      // d435i의 토픽으로부터 이미지를 받는 subscribe
      image_pub = node.advertise<sensor_msgs::Image>("/ByoungJin_image",10);
      // d435i 이미지 토픽을 subscribe한 것을 publish
      test_image_sub = node.subscribe("/ByoungJin_image",10,&D435Image::TestImageCallback,this);
      // 다른사람의 카메라의 토픽으로부터 이미지를 받는 subscribe

    }

    ~D435Image()   { }


void Gaussian_Blur(cv::Mat image)
{
  cv::Mat cv_output;                                 
  // cv_output 이름의 Mat 객체 선언
  GaussianBlur(image,cv_output,cv::Size(),5);
  // GaussianBlur(입력영상, 출력영상, 커널 사이즈,표준편차(sigma) 
  cv::imshow("d435_output_img",cv_output);
  // 가우시안 필터링 처리된 cv_output 이미지 출력
}

void ImageCallback(const sensor_msgs::Image::ConstPtr& test_img_sub)
{
  image_pub.publish(test_img_sub);
  // image_pub 퍼블리셔로 test_img_sub 이미지 넣음
}

void TestImageCallback(const sensor_msgs::Image::ConstPtr& img_sub)
{
  cv_bridge::CvImagePtr cv_d435;
  // toCvCopy함수를 사용하기 위해 CvImagePtr 객체 생성 

  cv_d435 = cv_bridge::toCvCopy(img_sub, sensor_msgs::image_encodings::BGR8);
  // toCvCopy함수로 Opencv와 호환이 되는 CvImage로 변환 및 복사

  cv::Mat img_raw = cv_d435->image;
  // 가우시안필터 함수에 Mat 형식으로 받기 위한 raw image 선언

  cv::imshow("d435_input_img", img_raw);
  // 필터 전 이미지 출력

  Gaussian_Blur(img_raw);
  // 가우시안 필터링

  esc_Waitkey = cv::waitKey(1);
  if(esc_Waitkey == 27){
        cv::destroyAllWindows();
      }
  }
};




  