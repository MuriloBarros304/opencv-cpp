#include <opencv2/opencv.hpp>
#include <iostream>

int main(void) {
    cv::VideoCapture cap(0);
    cv::Mat frame;
    cv::namedWindow("canny");
    cv::Mat frameCinza;
    cv::Mat frameBlur;
    cv::Mat frameCanny;
    while (true) {
        cap >> frame;
        cv::cvtColor(frame, frameCinza, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(frameCinza, frameBlur, cv::Size(5, 5), 1.5);
        cv::Canny(frameBlur, frameCanny, 100, 200);
        cv::imshow("canny", frameCanny);
        if (cv::waitKey(30) == 'q'){
            break;
        }
    }
    return 0;
}