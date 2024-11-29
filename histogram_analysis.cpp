#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void calculateAndPlotHistograms(const Mat& image1, const Mat& image2) {
    vector<Mat> bgr_planes1, bgr_planes2;
    split(image1, bgr_planes1);
    split(image2, bgr_planes2);

    int histSize = 256;  
    float range[] = { 0, 256 };  
    const float* histRange = { range };

    Mat b_hist1, g_hist1, r_hist1;
    Mat b_hist2, g_hist2, r_hist2;

    calcHist(&bgr_planes1[0], 1, 0, Mat(), b_hist1, 1, &histSize, &histRange);
    calcHist(&bgr_planes1[1], 1, 0, Mat(), g_hist1, 1, &histSize, &histRange);
    calcHist(&bgr_planes1[2], 1, 0, Mat(), r_hist1, 1, &histSize, &histRange);

    calcHist(&bgr_planes2[0], 1, 0, Mat(), b_hist2, 1, &histSize, &histRange);
    calcHist(&bgr_planes2[1], 1, 0, Mat(), g_hist2, 1, &histSize, &histRange);
    calcHist(&bgr_planes2[2], 1, 0, Mat(), r_hist2, 1, &histSize, &histRange);

    normalize(b_hist1, b_hist1, 0, 255, NORM_MINMAX, -1, Mat());
    normalize(g_hist1, g_hist1, 0, 255, NORM_MINMAX, -1, Mat());
    normalize(r_hist1, r_hist1, 0, 255, NORM_MINMAX, -1, Mat());

    normalize(b_hist2, b_hist2, 0, 255, NORM_MINMAX, -1, Mat());
    normalize(g_hist2, g_hist2, 0, 255, NORM_MINMAX, -1, Mat());
    normalize(r_hist2, r_hist2, 0, 255, NORM_MINMAX, -1, Mat());

    Mat b_diff = abs(b_hist1 - b_hist2);
    Mat g_diff = abs(g_hist1 - g_hist2);
    Mat r_diff = abs(r_hist1 - r_hist2);

    normalize(b_diff, b_diff, 0, 255, NORM_MINMAX, -1, Mat());
    normalize(g_diff, g_diff, 0, 255, NORM_MINMAX, -1, Mat());
    normalize(r_diff, r_diff, 0, 255, NORM_MINMAX, -1, Mat());

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);

    Mat histImage1(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
    Mat histImage2(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
    Mat histDiff(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    for (int i = 1; i < histSize; i++) {
        // Drawing thinner lines (thickness set to 1)
        line(histImage1, Point(bin_w * (i - 1), hist_h - cvRound(b_hist1.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(b_hist1.at<float>(i))),
             Scalar(255, 0, 0), 1); // Blue channel for original image
        line(histImage1, Point(bin_w * (i - 1), hist_h - cvRound(g_hist1.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(g_hist1.at<float>(i))),
             Scalar(0, 255, 0), 1); // Green channel for original image
        line(histImage1, Point(bin_w * (i - 1), hist_h - cvRound(r_hist1.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(r_hist1.at<float>(i))),
             Scalar(0, 0, 255), 1); // Red channel for original image

        line(histImage2, Point(bin_w * (i - 1), hist_h - cvRound(b_hist2.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(b_hist2.at<float>(i))),
             Scalar(255, 0, 0), 1); // Blue channel for modified image
        line(histImage2, Point(bin_w * (i - 1), hist_h - cvRound(g_hist2.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(g_hist2.at<float>(i))),
             Scalar(0, 255, 0), 1); // Green channel for modified image
        line(histImage2, Point(bin_w * (i - 1), hist_h - cvRound(r_hist2.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(r_hist2.at<float>(i))),
             Scalar(0, 0, 255), 1); // Red channel for modified image

        line(histDiff, Point(bin_w * (i - 1), hist_h - cvRound(b_diff.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(b_diff.at<float>(i))),
             Scalar(255, 0, 0), 1); // Blue channel for differences
        line(histDiff, Point(bin_w * (i - 1), hist_h - cvRound(g_diff.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(g_diff.at<float>(i))),
             Scalar(0, 255, 0), 1); // Green channel for differences
        line(histDiff, Point(bin_w * (i - 1), hist_h - cvRound(r_diff.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(r_diff.at<float>(i))),
             Scalar(0, 0, 255), 1); // Red channel for differences
    }

    imshow("Original Image Histogram", histImage1);
    imshow("Modified Image Histogram", histImage2);
    imshow("Histogram Differences", histDiff);
}

int main() {
    string inputFilePath = "/Users/rakshit/Desktop/SteganographyProject/11.png";
    string outputFilePath = "/Users/rakshit/Desktop/SteganographyProject/output_image.png";

    Mat image1 = imread(inputFilePath);
    Mat image2 = imread(outputFilePath);

    if (image1.empty() || image2.empty()) {
        cout << "Error loading images!" << endl;
        return -1;
    }

    calculateAndPlotHistograms(image1, image2);

    waitKey(0);
    return 0;
}
