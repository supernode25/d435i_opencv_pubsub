#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <opencv2/highgui/highgui.hpp>


class D435Image
{
    int  esc_Waitkey;
    ros::NodeHandle node;
    image_transport::ImageTransport it;
    image_transport::Subscriber image_sub;
    image_transport::Subscriber test_image_sub;
    image_transport::Publisher image_pub;
    // ROS형태의 이미지 변환 image_transport 사용

public:
    D435Image() : it(node) //리스트로 초기화
        {
            image_sub = it.subscribe("/camera/color/image_raw",10,&D435Image::ImageCallback,this);
            // d435i의 topic으로부터 raw image를 받는 subscriber 
            image_pub = it.advertise("/ByoungJin_image",10);
            // sensor_msgs::Image로 받은 raw_image를 본인 이름의 topic으로 publishing 하는 publisher
            test_image_sub = it.subscribe("/jeonggi_image",10,&D435Image::TestImageCallback,this);
            // 다른 사람이 d435i의 raw image를 publishing하고 있는 publisher의 topic을 subscribe 하는 subscriber
        }

    ~D435Image()   {    }


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



  //sensor_msgs::Image test_image = *test_img_sub;
  // raw이미지의 형태로 받음
  // opencv의 구조체와 연동시킬 것이면 cv_bridge, CvImage를 사용하여 형 변환 
  