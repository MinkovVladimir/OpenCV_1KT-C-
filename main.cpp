#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

int main() {
    cv::VideoCapture cam(0);

    if (!cam.isOpened()) {
        std::cerr << "Ошибка: не удалось открыть веб-камеру!" << std::endl;
        return -1;
    }

    std::cout << "Камера запущена!\n"
              << "Нажмите 'y' для включения/выключения логотипа.\n"
              << "Нажмите 'ESC' для выхода." << std::endl;

    cv::Mat frame;
    bool showLogo = false;

    cv::Mat logo = cv::Mat::zeros(60, 180, CV_8UC3);
    logo.setTo(cv::Scalar(0, 0, 255));
    cv::putText(logo, "VORTEX",
                cv::Point(15, 40),
                cv::FONT_HERSHEY_SIMPLEX, 0.8,
                cv::Scalar(255, 255, 255), 2);

    while (true) {
        cam >> frame;
        if (frame.empty()) break;

        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%H:%M:%S");
        std::string timeStr = ss.str();

        cv::Point textPos(30, 50);
        cv::putText(frame, timeStr, textPos + cv::Point(2, 2), cv::FONT_HERSHEY_DUPLEX, 1.0, cv::Scalar(0, 0, 0), 2);
        cv::putText(frame, timeStr, textPos, cv::FONT_HERSHEY_DUPLEX, 1.0, cv::Scalar(255, 255, 0), 2);

        if (showLogo) {
            int x = frame.cols - logo.cols - 20;
            int y = 20;

            if (x >= 0 && y >= 0 && x + logo.cols <= frame.cols && y + logo.rows <= frame.rows) {
                cv::Mat roi = frame(cv::Rect(x, y, logo.cols, logo.rows));
                cv::addWeighted(logo, 0.7, roi, 0.3, 0.0, roi);
            }
        }

        cv::imshow("Video Processing KT1", frame);

        int key = cv::waitKey(30);
        if (key == 27) {
            break;
        } else if (key == 'y' || key == 'Y' || key == 'н' || key == 'Н') {
            showLogo = !showLogo;
            std::cout << "Логотип: " << (showLogo ? "ВКЛ" : "ВЫКЛ") << std::endl;
        }
    }

    cv::destroyAllWindows();
    return 0;
}