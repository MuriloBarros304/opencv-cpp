#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

cv::Mat imagemCinza;
cv::Mat imagemSuavizada;
cv::Mat bordas;

void detect(cv::Mat frame) {
    cv::cvtColor(frame, imagemCinza, cv::COLOR_BGR2GRAY);

    cv::GaussianBlur(imagemCinza, imagemSuavizada, cv::Size(9, 9), 2, 2);

    // ajustar parâmetros
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(imagemSuavizada, circles, cv::HOUGH_GRADIENT, 1, imagemSuavizada.rows / 16, 100, 30, 60, 100);

    for (size_t i = 0; i < circles.size(); i++) {
        cv::Vec3i c = circles[i];
        cv::Point center(c[0], c[1]);
        int radius = c[2];

        cv::circle(frame, center, radius, cv::Scalar(0, 255, 0), 3);

        // centro do círculo
        cv::circle(frame, center, 2, cv::Scalar(0, 0, 255), 3);
    }

    cv::namedWindow("Detect", cv::WINDOW_AUTOSIZE);
    cv::imshow("Detect", frame);
}
