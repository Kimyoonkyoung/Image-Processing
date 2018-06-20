/**
 * Created by Rachel.minii 
 * Date : 2018. 6. 20.
 * Project : ImageProcessing
 */

#include <iostream>
#include <highgui.h>

#include "Color.h"

int main(int argc, char const* argv[])
{
    std::string const srcPathRGBA = "/Users/rachel/Kimyoonkyoung/3.Project/Image-Processing/testimage/Color/input/rgba.png";
    std::string const srcPathRGB = "/Users/rachel/Kimyoonkyoung/3.Project/Image-Processing/testimage/Color/input/rgb.jpg";
    std::string const srcPathRGB1 = "/Users/rachel/Kimyoonkyoung/3.Project/Image-Processing/testimage/Color/input/rgb.jpg";
    std::string const srcPathGRAY = "/Users/rachel/Kimyoonkyoung/3.Project/Image-Processing/testimage/Color/input/gray.jpg";

    std::string saveDir = "/Users/rachel/Kimyoonkyoung/3.Project/Image-Processing/testimage/Color/output";
    char savePath[100];

    Color _color;

#ifdef RGB2RGB565
    cv::Mat pBitmapRGB = cv::imread(srcPathRGB, cv::IMREAD_UNCHANGED);
    cv::Mat pBitmapRGB565(pBitmapRGB.rows, pBitmapRGB.cols, CV_16UC1);

    if (!_color.ConvRgbToRgb565(pBitmapRGB565, pBitmapRGB))
        printf("[FALSE] rgb to rgb565\n");

    cv::Mat pResult(pBitmapRGB.rows, pBitmapRGB.cols, CV_8UC3);
    if (!_color.ConvRgb565ToRgb(pResult, pBitmapRGB565))
        printf("[FALSE] rgb565 to rgb\n");

    sprintf(savePath, "%s/%s", saveDir.c_str(), "rgb565.png");
    cv::imwrite(savePath, pResult);
#endif


// TODO : error
#ifdef RGBA2RGB565
    cv::Mat pBitmapRGBA = cv::imread(srcPathRGBA, cv::IMREAD_UNCHANGED);
    cv::Mat pBitmapRGB565(pBitmapRGBA.rows, pBitmapRGBA.cols, CV_16UC1);

    if (!_color.ConvRgbaToRgb565(pBitmapRGB565, pBitmapRGBA, false))
        printf("[FALSE] rgba to rgb565\n");

    cv::Mat pResult(pBitmapRGBA.rows, pBitmapRGBA.cols, CV_8UC4);
    if (!_color.ConvRgb565ToRgba(pResult, pBitmapRGB565))
        printf("[FALSE] rgb565 to rgba\n");

    sprintf(savePath, "%s/%s", saveDir.c_str(), "rgb565.png");
    cv::imwrite(savePath, pResult);
#endif


#ifdef RGB2RGBA4444
    cv::Mat pBitmapRGB = cv::imread(srcPathRGB, cv::IMREAD_UNCHANGED);
    cv::Mat pBitmapRGBA4444(pBitmapRGB.rows, pBitmapRGB.cols, CV_16UC1);

    if (!_color.ConvRgbToRgba4444(pBitmapRGBA4444, pBitmapRGB))
        printf("[FALSE] rgb to rgba4444\n");

    cv::Mat pResult(pBitmapRGB.rows, pBitmapRGB.cols, CV_8UC3);
    if (!_color.ConvRgba4444ToRgb(pResult, pBitmapRGBA4444, false))
        printf("[FALSE] rgba4444 to rgb\n");

    sprintf(savePath, "%s/%s", saveDir.c_str(), "rgb565.png");
    cv::imwrite(savePath, pResult);
#endif

// TODO : error
#ifdef RGBA2RGBA4444
    cv::Mat pBitmapRGBA = cv::imread(srcPathRGBA, cv::IMREAD_UNCHANGED);
    cv::Mat pBitmapRGBA4444(pBitmapRGBA.rows, pBitmapRGBA.cols, CV_16UC1);

    if (!_color.ConvRgbaToRgba4444(pBitmapRGBA4444, pBitmapRGBA))
        printf("[FALSE] rgba to rgb4444\n");

    cv::Mat pResult(pBitmapRGBA.rows, pBitmapRGBA.cols, CV_8UC4);
    if (!_color.ConvRgba4444ToRgba(pResult, pBitmapRGBA4444))
        printf("[FALSE] rgb4444 to rgba\n");

    sprintf(savePath, "%s/%s", saveDir.c_str(), "rgb565.png");
    cv::imwrite(savePath, pResult);
#endif


#ifdef RGB2RGBA5551
    cv::Mat pBitmapRGB = cv::imread(srcPathRGB, cv::IMREAD_UNCHANGED);
    cv::Mat pBitmapRGBA5551(pBitmapRGB.rows, pBitmapRGB.cols, CV_16UC1);

    if (!_color.ConvRgbToRgba5551(pBitmapRGBA5551, pBitmapRGB))
        printf("[FALSE] rgb to rgba5551\n");

    cv::Mat pResult(pBitmapRGB.rows, pBitmapRGB.cols, CV_8UC3);
    if (!_color.ConvRgba5551ToRgb(pResult, pBitmapRGBA5551, false))
        printf("[FALSE] rgba5551 to rgb\n");

    sprintf(savePath, "%s/%s", saveDir.c_str(), "rgb565.png");
    cv::imwrite(savePath, pResult);
#endif


#ifdef RGBA2RGBA5551
    cv::Mat pBitmapRGBA = cv::imread(srcPathRGBA, cv::IMREAD_UNCHANGED);
    cv::Mat pBitmapRGBA5551(pBitmapRGBA.rows, pBitmapRGBA.cols, CV_16UC1);

    if (!_color.ConvRgbaToRgba5551(pBitmapRGBA5551, pBitmapRGBA))
        printf("[FALSE] rgba to rgba5551\n");

    cv::Mat pResult(pBitmapRGBA.rows, pBitmapRGBA.cols, CV_8UC4);
    if (!_color.ConvRgba5551ToRgba(pResult, pBitmapRGBA5551))
        printf("[FALSE] rgba5551 to rgba\n");

    sprintf(savePath, "%s/%s", saveDir.c_str(), "rgb565.png");
    cv::imwrite(savePath, pResult);
#endif


#ifdef RGB2GRAY
    cv::Mat pBitmapRGB = cv::imread(srcPathRGB, cv::IMREAD_UNCHANGED);
    cv::Mat pBitmapGRAY(pBitmapRGB.rows, pBitmapRGB.cols, CV_8UC1);

    if (!_color.ConvRGBToGray(pBitmapGRAY, pBitmapRGB))
        printf("[FALSE] rgb to gray\n");

    cv::Mat pResult(pBitmapRGB.rows, pBitmapRGB.cols, CV_8UC3);
    if (!_color.ConvGrayToRGB(pResult, pBitmapGRAY))
        printf("[FALSE] gray to rgb\n");

    sprintf(savePath, "%s/%s", saveDir.c_str(), "rgb565.png");
    cv::imwrite(savePath, pResult);
#endif


// TODO : error
#ifdef RGBA2GRAY
    cv::Mat pBitmapRGBA = cv::imread(srcPathRGBA, cv::IMREAD_UNCHANGED);
    cv::Mat pBitmapGRAY(pBitmapRGBA.rows, pBitmapRGBA.cols, CV_8UC1);

    if (!_color.ConvRGBAToGray(pBitmapGRAY, pBitmapRGBA, false))
        printf("[FALSE] rgba to gray\n");

    cv::Mat pResult(pBitmapRGBA.rows, pBitmapRGBA.cols, CV_8UC4);
    if (!_color.ConvGrayToRGBA(pResult, pBitmapGRAY))
        printf("[FALSE] gray to rgba\n");

    sprintf(savePath, "%s/%s", saveDir.c_str(), "rgb565.png");
    cv::imwrite(savePath, pResult);
#endif


#ifdef ARGB
    cv::Mat pBitmapRGBA = cv::imread(srcPathRGBA, cv::IMREAD_UNCHANGED);
    cv::Mat pBitmapARGB(pBitmapRGBA.rows, pBitmapRGBA.cols, CV_8UC4);

    if (!_color.ConvRGBAToARGB(pBitmapARGB, pBitmapRGBA))
        printf("[FALSE] rgba to argb\n");

    cv::Mat pResult(pBitmapRGBA.rows, pBitmapRGBA.cols, CV_8UC4);
    if (!_color.ConvARGBToRGBA(pResult, pBitmapARGB))
        printf("[FALSE] argb to rgba\n");

    sprintf(savePath, "%s/%s", saveDir.c_str(), "rgb565.png");
    cv::imwrite(savePath, pResult);
#endif


// TODO : 마지막에할래
#ifdef YUV444
    cv::Mat pBitmapRGBA = cv::imread(srcPathRGBA, cv::IMREAD_UNCHANGED);
    cv::Mat pBitmapYUV444(pBitmapRGBA.rows, pBitmapRGBA.cols, CV_4UC1);

    auto pBitmapRGB = lte::Image::FromFile(srcPathRGB);
    auto pBitmapYUV444 = lte::Image::Create(pBitmapRGB->width(), pBitmapRGB->height(), lte::PIXEL_FORMAT_YUV444);

    // rgb to yuv444
    ConvRGBToYUV444(pBitmapYUV444, pBitmapRGB);

    // yuv444 to rgb
    ConvYUV444ToRGB(pBitmapRGB, pBitmapYUV444);
#endif


// TODO : 마지막에할래
#ifdef YUV422
    auto pBitmapRGB = lte::Image::FromFile(srcPathRGB);
    auto pBitmapYUV422 = lte::Image::Create(pBitmapRGB->width(), pBitmapRGB->height(), lte::PIXEL_FORMAT_YUV422);

     // rgb to yuv422
    ConvRGBToYUV422(pBitmapYUV422, pBitmapRGB);

    // yuv422 to rgb
    ConvYUV422ToRGB(pBitmapRGB, pBitmapYUV422);
#endif


// TODO : 마지막에할래
#ifdef YUV420
    auto pBitmapRGB = lte::Image::FromFile(srcPathRGB);
    auto pBitmapYUV422 = lte::Image::Create(pBitmapRGB->width(), pBitmapRGB->height(), lte::PIXEL_FORMAT_YUV422);

     // rgb to yuv422
    ConvRGBToYUV422(pBitmapYUV422, pBitmapRGB);

    // yuv422 to rgb
    ConvYUV422ToRGB(pBitmapRGB, pBitmapYUV422);
#endif


#ifdef HSV
    cv::Mat pBitmapRGB = cv::imread(srcPathRGB, cv::IMREAD_UNCHANGED);

    uchar* buffer = pBitmapRGB.data;
    int width = pBitmapRGB.cols;
    int height = pBitmapRGB.rows;
    int channel = pBitmapRGB.channels();
    int stride = channel * width;

    for (int i = 0; i < height; ++i)
    {
        int yIdx = i * stride;

        for (int j = 0; j < width; ++j)
        {
            int idx = yIdx + (j * channel);

            double h, s, v;

            _color.ConvRGBToHSV(buffer[idx+0], buffer[idx+1], buffer[idx+2], h, s, v);
            _color.ConvHSVToRGB(h, s, v , buffer[idx+0], buffer[idx+1], buffer[idx+2]);
        }
    }
#endif


#ifdef RGB2YCBCR
    cv::Mat pBitmapRGB = cv::imread(srcPathRGB, cv::IMREAD_UNCHANGED);
    cv::Mat pBitmapYCbCr(pBitmapRGB.rows, pBitmapRGB.cols, CV_8UC3);

    if (!_color.ConvRGBToYCbCr(pBitmapYCbCr, pBitmapRGB))
        printf("[FALSE] rgb to ycbcr\n");

    cv::Mat pResult(pBitmapRGB.rows, pBitmapRGB.cols, CV_8UC3);
    if (!_color.ConvYCbCrToRGB(pResult, pBitmapYCbCr))
        printf("[FALSE] ycbcr to rgb\n");

    sprintf(savePath, "%s/%s", saveDir.c_str(), "rgb565.png");
    cv::imwrite(savePath, pResult);
#endif


#ifdef RGB2Lab
    cv::Mat pBitmapRGB = cv::imread(srcPathRGB, cv::IMREAD_UNCHANGED);
    cv::Mat pBitmapLab(pBitmapRGB.rows, pBitmapRGB.cols, CV_8UC3);

    if (!_color.ConvRGBToLab(pBitmapLab, pBitmapRGB))
        printf("[FALSE] rgb to lab\n");

    cv::Mat pResult(pBitmapRGB.rows, pBitmapRGB.cols, CV_8UC3);
    if (!_color.ConvLabToRGB(pResult, pBitmapLab))
        printf("[FALSE] lab to rgb\n");

    sprintf(savePath, "%s/%s", saveDir.c_str(), "rgb565.png");
    cv::imwrite(savePath, pResult);
#endif


    return 0;
}