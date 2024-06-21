#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat imagemCinza;
cv::Mat imagemSuavizada;
cv::Mat bordas;
void detect(cv::Mat frame) {
    // Escala de cinza
    cv::cvtColor(frame, imagemCinza, cv::COLOR_BGR2GRAY);

    // Gaussian Blur
    cv::GaussianBlur(imagemCinza, imagemSuavizada, cv::Size(5, 5), 1.5);

    // Canny
    cv::Canny(imagemSuavizada, bordas, 50, 150);

    // Encontrar contornos na imagem
    std::vector<std::vector<cv::Point>> contornos;
    cv::findContours(bordas, contornos, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    double maiorArea = 0;
    std::vector<cv::Point> maiorPoligono;

    // Filtrar contornos que são retangulares e encontrar o maior
    for (size_t i = 0; i < contornos.size(); i++) {
        // Aproximar o contorno a um polígono
        std::vector<cv::Point> poligono;
        cv::approxPolyDP(contornos[i], poligono,
                         0.02 * cv::arcLength(contornos[i], true), true);

        // Verificar se o polígono tem 4 lados e é convexo
        if (poligono.size() == 4 && cv::isContourConvex(poligono)) {
            double area = cv::contourArea(poligono);
            if (area > maiorArea) {
                maiorArea = area;
                maiorPoligono = poligono;
            }
        }
    }

    // Desenhar o maior retângulo encontrado
    if (!maiorPoligono.empty()) {
        for (size_t j = 0; j < 4; j++) {
            cv::line(frame, maiorPoligono[j], maiorPoligono[(j + 1) % 4],
                     cv::Scalar(0, 255, 0), 3);
        }

        // Adicionar o texto "base" no centro do retângulo
        cv::Rect retangulo = cv::boundingRect(maiorPoligono);
        cv::putText(frame, "base", cv::Point(retangulo.x, retangulo.y - 3),
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
    }

    // Exibir a imagem resultante
    cv::namedWindow("Detect", cv::WINDOW_AUTOSIZE);
    cv::imshow("Detect", frame);
}
