#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // 打开默认摄像头（索引 0）
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cerr << "无法打开摄像头" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;

        cv::imshow("Camera", frame);

        // 按 q 退出
        if (cv::waitKey(1) == 'q')
            break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}