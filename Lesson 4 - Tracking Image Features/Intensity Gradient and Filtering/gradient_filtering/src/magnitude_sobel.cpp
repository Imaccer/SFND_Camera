#include <iostream>
#include <numeric>
#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void magnitudeSobel()
{
    // load image from file
    cv::Mat img;
    img = cv::imread("../images/img1gray.png");

    // convert image to grayscale
    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // apply smoothing using the GaussianBlur() function from the OpenCV
    // ToDo : Add your code here
    cv::Mat gaussBlur;
    cv::Size ksize(3, 3);

    cv::GaussianBlur(imgGray, gaussBlur, ksize, 0, 0, cv::BORDER_DEFAULT);

    // create filter kernels using the cv::Mat datatype both for x and y
    // ToDo : Add your code here
    float sobel_x[9] = {-1, 0, +1,
                        -2, 0, +2, 
                        -1, 0, +1};
    cv::Mat kernel_x = cv::Mat(3, 3, CV_32F, sobel_x);

    float sobel_y[9] = {-1, -2, -1,
                        0, 0, 0, 
                        +1, +2, +1};
    cv::Mat kernel_y = cv::Mat(3, 3, CV_32F, sobel_y);

    // apply filter using the OpenCv function filter2D()
    // ToDo : Add your code here
    cv::Mat result_x;
    // cv::filter2D(gaussBlur, result_x, -1, kernel_x, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::filter2D(gaussBlur, result_x, CV_32F, kernel_x, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    cv::Mat result_y;
    // cv::filter2D(gaussBlur, result_y, -1, kernel_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::filter2D(gaussBlur, result_y, CV_32F, kernel_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    // compute magnitude image based on the equation presented in the lesson 
    // ToDo : Add your code here

    // cv::Mat magnitude;
    // cv::magnitude(result_x, result_y, magnitude);

    // compute magnitude image manually
    cv::Mat magnitude(result_x.rows, result_x.cols, CV_32F);
    for (int i = 0; i < result_x.rows; ++i)
    {
        for (int j = 0; j < result_x.cols; ++j)
        {
            // float gx = result_x.at<float>(i, j);
            // float gy = result_y.at<float>(i, j);
            // magnitude.at<float>(i, j) = std::sqrt(gx * gx + gy * gy);
            float gx = result_x.at<float>(i, j);
            float gy = result_y.at<float>(i, j);
            magnitude.at<float>(i, j) = std::sqrt(gx * gx + gy * gy);
        }
    }

    // // convert magnitude to an 8-bit image for display
    // cv::Mat magnitude_display;
    // magnitude.convertTo(magnitude_display, CV_8U);
    // Normalize the magnitude image to the range [0, 255]
    // cv::Mat magnitude_display;
    // cv::normalize(magnitude, magnitude_display, 0, 255, cv::NORM_MINMAX, CV_8U);
    // show result

    // Print the minimum and maximum values of the magnitude image before normalization
    double minVal, maxVal;
    cv::minMaxLoc(magnitude, &minVal, &maxVal);
    cout << "Magnitude min: " << minVal << ", max: " << maxVal << endl;

// Normalize the magnitude image to the range [0, 255] for display
cv::Mat magnitude_display;
cv::normalize(magnitude, magnitude_display, 0, 255, cv::NORM_MINMAX, CV_8U, cv::Mat());

    string windowName = "Gaussian Blurring";
    cv::namedWindow(windowName, 1); // create window
    //cv::imshow(windowName, magnitude);
    cv::imshow(windowName, magnitude_display);
    cv::waitKey(0); // wait for keyboard input before continuing
}

int main()
{
    magnitudeSobel();
}