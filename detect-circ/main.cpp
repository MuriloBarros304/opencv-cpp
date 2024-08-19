#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

#include "detectcirc.h"

int main(void) {
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Erro: Não foi possível abrir a webcam." << std::endl;
        return -1;
    }

    cv::Mat frame;
    cv::Mat imagemCinza;
    cv::Mat imagemSuavizada;
    cv::Mat bordas;
    int frame_count = 0;
    int fps = 0;
    bool start_timing = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Erro: Frame vazio capturado." << std::endl;
            break;
        }
            detect(frame);
        
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
