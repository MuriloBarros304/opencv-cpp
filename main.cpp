#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

#include "detect.h"

int main(void) {
    // Abrir a webcam
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

        if (!start_timing) {
            // Inicializar a janela e iniciar a contagem de tempo
            cv::namedWindow("Webcam");
            start = std::chrono::high_resolution_clock::now();
            start_timing = true;
        } else {
            frame_count++;
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = now - start;

            if (elapsed.count() >= 1.0) {  // Calcula FPS a cada segundo
                fps = frame_count / elapsed.count();
                frame_count = 0;
                start = std::chrono::high_resolution_clock::now();
            }

            std::string fps_text = "FPS: " + std::to_string(fps);
            cv::putText(frame, fps_text, cv::Point(10, 30),
                        cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
            detect(frame);
        }

        // Sair do loop se a tecla 'q' for pressionada
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    // Liberar a webcam
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
