//
// Created by zq on 17-5-24.
//

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>
#include <opencv2/video.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
using namespace std;
using namespace cv;

void decode(const Mat &srcImg, Mat &waterMakrImg) {
    int x0 = 0;
    int y0 = 0;
    int x = srcImg.rows * 0.5;
    int y = srcImg.cols * 0.5;
    cout << x << ", " << y << endl;
    waterMakrImg = Mat::zeros(x, y, CV_8UC(1));
    for(int i = x0; i < x+x0; ++ i) {
        for(int j = y0; j < y+y0; ++ j) {
            bool intensity = (srcImg.at<uchar>(i, j) & 1);
            waterMakrImg.at<uchar>(i - x0, j - y0) = intensity * UCHAR_MAX;
        }
    }
//    const char *result = "../decode.jpg";
//    cout << imwrite(result, binMark) << endl;
//    imshow("watermark", binMark);
}

int main(int argc, char *argv[]) {
    if(argc < 3) {
        cout << "Usage: decode <picture-file> <waterMark-file>" << endl;
        return -1;
    }
    Mat srcImg;                 // 原始图片
    Mat waterMarkImg;           // 提取的水印；
    srcImg = imread(argv[1], IMREAD_GRAYSCALE);
    decode(srcImg, waterMarkImg);
    imshow("waterMark", waterMarkImg);
    waitKey(0);
    imwrite(argv[2], waterMarkImg);
    return 0;
}

// 以灰度图像模式读入图像
void loadImg(Mat &img, const char *filename) {
    img = imread(filename, IMREAD_GRAYSCALE);
    if(!img.data) {
        perror("load image error!\n");
    }
}

// 转化为二值图像
void toBinImg(Mat &srcImg, Mat &binImg, double thresholdValue){
    threshold(srcImg, binImg, thresholdValue, UCHAR_MAX, THRESH_BINARY);
}

void show(Mat &img, const char* title) {
    namedWindow(title);
    imshow(title, img);
    waitKey(0);
}

int getR(const Mat &a, int x, int y) {
    int ans = 0;
    int r1 = 0, r2 = 0, r3 = 0, r4 = 0;
    for(int i = x; i < x + 3; ++ i) {
        uchar* data = (uchar *) a.ptr<uchar>(i);
        for(int j = y; j < y + 3; ++ j) {
            if(data[j] == 0) {     //黑色像素
                r1 ++;
            }
        }
        for(int j = y+1; j < y + 4; ++ j) {
            if(data[j] == 0) {     //黑色像素
                r2 ++;
            }
        }
    }
    for(int i = x+1; i < x + 4; ++ i) {
        uchar* data = (uchar *) a.ptr<uchar>(i);
        for(int j = y; j < y + 3; ++ j) {
            if(data[j] == 0) {     //黑色像素
                r3 ++;
            }
        }
        for(int j = y+1; j < y + 4; ++ j) {
            if(data[j] == 0) {     //黑色像素
                r4 ++;
            }
        }
    }
    ans += r1 ^ 1;
    ans += r2 ^ 1;
    ans += r3 ^ 1;
    ans += r4 ^ 1;
    return ans;
}

double dist(int x0, int y0, int x, int y) {
    double ans =0.0;
}

