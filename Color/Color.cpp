/**
 * Created by Rachel.minii 
 * Date : 2018. 6. 20.
 * Project : ImageProcessing
 */

#include "Color.h"

#define mul5bitTo8bit 8.25
#define mul8bitTo5bit (1/8.25f)
#define mul6bitTo8bit 4.0625
#define mul8bitTo6bit (1/4.0625f)
#define mul4bitTo8bit 17
#define mul8bitTo4bit (1/17.0f)
#define divideBy255 (1/255.0f)
#define divideBy15 (1/15.0f)

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

bool Color::ConvRgbToRgb565(
        cv::Mat const& pBitmapRGB565,
        cv::Mat const& pBitmapRGB)
{
    if (pBitmapRGB.type() != CV_8UC3|| pBitmapRGB565.type() != CV_16UC1)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar * pSrcBuffer = pBitmapRGB.data;
    uchar * pDstBuffer = pBitmapRGB565.data;

    int length = pBitmapRGB.rows * pBitmapRGB.cols;
    int srcBypp = 3; // rgb
    int dstBypp = 2; // rgb565

    for (int i = 0; i < length; ++i)
    {
        int srcIdx = i * srcBypp;
        int dstIdx = i * dstBypp;

        uchar r = static_cast<uchar>(
                Clamp(round(pSrcBuffer[srcIdx + 0] * mul8bitTo5bit), 0.f, 255.f));
        uchar g = static_cast<uchar>(
                Clamp(round(pSrcBuffer[srcIdx + 1] * mul8bitTo6bit), 0.f, 255.f));
        uchar b = static_cast<uchar>(
                Clamp(round(pSrcBuffer[srcIdx + 2] * mul8bitTo5bit), 0.f, 255.f));

        pDstBuffer[dstIdx + 0] = (g << 5) | b;
        pDstBuffer[dstIdx + 1] = (r << 3) | (g >> 3);
    }

    return true;
}


bool Color::ConvRgb565ToRgb(
        cv::Mat const& pBitmapRGB,
        cv::Mat const& pBitmapRGB565)
{
    if (pBitmapRGB565.type() != CV_16UC1 || pBitmapRGB.type() != CV_8UC3)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGB565.data;
    uchar* pDstBuffer = pBitmapRGB.data;

    int length = pBitmapRGB565.rows * pBitmapRGB565.cols;
    int srcBypp = 2; // rgb565
    int dstBypp = 3; // rgb

    for (int i = 0; i < length; ++i)
    {
        int srcIdx = i * srcBypp;
        int dstIdx = i * dstBypp;

        pDstBuffer[dstIdx + 0] = static_cast<uchar>(
                Clamp(((pSrcBuffer[srcIdx + 1] >> 3) & 0x1F) * mul5bitTo8bit, 0.0, 255.0));

        uchar tmp = static_cast<uchar>(
                ((pSrcBuffer[srcIdx + 1] & 0x07) << 3) |
                (pSrcBuffer[srcIdx + 0] >> 5));

        pDstBuffer[dstIdx + 1] = static_cast<uchar>(
                Clamp(tmp * mul6bitTo8bit, 0.0, 255.0));

        pDstBuffer[dstIdx + 2] = static_cast<uchar>(
                Clamp((pSrcBuffer[srcIdx + 0] & 0x1F) * mul5bitTo8bit, 0.0, 255.0));
    }

    return true;
}


bool Color::ConvRgbaToRgb565(
        cv::Mat const& pBitmapRGB565,
        cv::Mat const& pBitmapRGBA,
        bool enablealpha)
{
    if (pBitmapRGBA.type() != CV_8UC4 || pBitmapRGB565.type() != CV_16UC1)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGBA.data;
    uchar* pDstBuffer = pBitmapRGB565.data;

    int length = pBitmapRGBA.rows * pBitmapRGBA.cols;
    int srcBypp = 4; // rgba
    int dstBypp = 2; // rgb565

    if (!enablealpha)
    {
        for (int i = 0; i < length; ++i)
        {
            int srcIdx = i * srcBypp;
            int dstIdx = i * dstBypp;

            uchar r = static_cast<uchar>(Clamp(round(pSrcBuffer[srcIdx + 0] * mul8bitTo5bit), 0.f, 255.f));
            uchar g = static_cast<uchar>(Clamp(round(pSrcBuffer[srcIdx + 1] * mul8bitTo6bit), 0.f, 255.f));
            uchar b = static_cast<uchar>(Clamp(round(pSrcBuffer[srcIdx + 2] * mul8bitTo5bit), 0.f, 255.f));

            pDstBuffer[dstIdx + 0] = (g << 5) | b;
            pDstBuffer[dstIdx + 1] = (r << 3) | (g >> 3);
        }
    }
    else
    {
        for (int i = 0; i < length; ++i)
        {
            int srcIdx = i * srcBypp;
            int dstIdx = i * dstBypp;

            uchar r = static_cast<uchar>(
                    Clamp(round((pSrcBuffer[srcIdx + 0] * (pSrcBuffer[srcIdx + 3] / 255)) * mul8bitTo5bit), 0.f, 255.f));

            uchar g = static_cast<uchar>(
                    Clamp(round((pSrcBuffer[srcIdx + 1] * (pSrcBuffer[srcIdx + 3] / 255)) * mul8bitTo6bit), 0.f, 255.f));

            uchar b = static_cast<uchar>(
                    Clamp(round((pSrcBuffer[srcIdx + 2] * (pSrcBuffer[srcIdx + 3] / 255)) * mul8bitTo5bit), 0.f, 255.f));

            pDstBuffer[dstIdx + 0] = (g << 5) | b;
            pDstBuffer[dstIdx + 1] = (r << 3) | (g >> 3);
        }
    }

    return true;
}


bool Color::ConvRgb565ToRgba(
        cv::Mat const& pBitmapRGBA,
        cv::Mat const& pBitmapRGB565)
{
    if (pBitmapRGB565.type() != CV_16UC1 || pBitmapRGBA.type() != CV_8UC4)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGB565.data;
    uchar* pDstBuffer = pBitmapRGBA.data;

    int length = pBitmapRGB565.cols * pBitmapRGB565.rows;
    int srcBypp = 2; // rgb565
    int dstBypp = 4; // rgba

    for (int i = 0; i < length; ++i)
    {
        int srcIdx = i * srcBypp;
        int dstIdx = i * dstBypp;

        pDstBuffer[dstIdx + 0] = static_cast<uchar>(
                Clamp((((pSrcBuffer[srcIdx + 1] >> 3) & 0x1F) * mul5bitTo8bit), 0.0, 255.0));

        uchar tmp = static_cast<uchar>(
                ((pSrcBuffer[srcIdx + 1] & 0x07) << 3) |
                (pSrcBuffer[srcIdx + 0] >> 5));

        pDstBuffer[dstIdx + 1] = static_cast<uchar>(Clamp(tmp * mul6bitTo8bit, 0.0, 255.0));

        pDstBuffer[dstIdx + 2] = static_cast<uchar>(Clamp((pSrcBuffer[srcIdx + 0] & 0x1F) * mul5bitTo8bit, 0.0, 255.0));

        pDstBuffer[dstIdx + 3] = 255;
    }

    return true;
}


bool Color::ConvRgbToRgba4444(cv::Mat const& pBitmapRGBA4444, cv::Mat const& pBitmapRGB)
{
    if (pBitmapRGB.type() != CV_8UC3 || pBitmapRGBA4444.type() != CV_16UC1)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGB.data;
    uchar* pDstBuffer = pBitmapRGBA4444.data;

    int length = pBitmapRGB.cols * pBitmapRGB.rows;
    int srcBypp = 3; // rgb
    int dstBypp = 2; // rgba4444

    for (int i = 0; i < length; ++i)
    {
        int srcIdx = i * srcBypp;
        int dstIdx = i * dstBypp;

        uchar r = static_cast<uchar>(
                Clamp(pSrcBuffer[srcIdx + 0] * mul8bitTo4bit, 0.f, 255.f));
        uchar g = static_cast<uchar>(
                Clamp(pSrcBuffer[srcIdx + 1] * mul8bitTo4bit, 0.f, 255.f));
        uchar b = static_cast<uchar>(
                Clamp(pSrcBuffer[srcIdx + 2] * mul8bitTo4bit, 0.f, 255.f));
        uchar a = 0x0F;

        pDstBuffer[dstIdx + 1] = (r << 4) | g;
        pDstBuffer[dstIdx + 0] = (b << 4) | a;
    }

    return true;
}


bool Color::ConvRgba4444ToRgb(cv::Mat const& pBitmapRGB, cv::Mat const& pBitmapRGBA4444, bool enablealpha)
{
    if (pBitmapRGBA4444.type() != CV_16UC1 || pBitmapRGB.type() != CV_8UC3)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGBA4444.data;
    uchar* pDstBuffer = pBitmapRGB.data;

    int length = pBitmapRGBA4444.cols * pBitmapRGBA4444.rows;
    int srcBypp = 2; // rgba4444
    int dstBypp = 3; // rgb

    if(!enablealpha)
    {
        for (int i = 0; i < length; ++i)
        {
            int srcIdx = i * srcBypp;
            int dstIdx = i * dstBypp;

            pDstBuffer[dstIdx + 0] = static_cast<uchar>(
                    Clamp((pSrcBuffer[srcIdx + 1] >> 4) * mul4bitTo8bit, 0, 255));
            pDstBuffer[dstIdx + 1] = static_cast<uchar>(
                    Clamp((pSrcBuffer[srcIdx + 1] & 0x0F) * mul4bitTo8bit, 0, 255));
            pDstBuffer[dstIdx + 2] = static_cast<uchar>(
                    Clamp((pSrcBuffer[srcIdx + 0] >> 4) * mul4bitTo8bit, 0, 255));
        }
    }
    else
    {
        for (int i = 0; i < length; ++i)
        {
            int srcIdx = i * srcBypp;
            int dstIdx = i * dstBypp;

            pDstBuffer[dstIdx + 0] = static_cast<uchar>(Clamp(
                    (pSrcBuffer[srcIdx + 1] >> 4) * 17 * ((pSrcBuffer[srcIdx + 0] & 0x0F) * divideBy15), 0.f, 255.f));

            pDstBuffer[dstIdx + 1] = static_cast<uchar>(Clamp(
                    (pSrcBuffer[srcIdx + 1] & 0x0F) * 17 * ((pSrcBuffer[srcIdx + 0] & 0x0F) * divideBy15), 0.f, 255.f));

            pDstBuffer[dstIdx + 2] = static_cast<uchar>(Clamp(
                    (pSrcBuffer[srcIdx + 0] >> 4) * 17 * ((pSrcBuffer[srcIdx + 0] & 0x0F) * divideBy15), 0.f, 255.f));
        }
    }

    return true;
}


bool Color::ConvRgba4444ToRgba(
        cv::Mat const& pBitmapRGBA,
        cv::Mat const& pBitmapRGBA4444)
{
    if (pBitmapRGBA4444.type() != CV_16UC1 || pBitmapRGBA.type() != CV_8UC4)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGBA4444.data;
    uchar* pDstBuffer = pBitmapRGBA.data;

    int length = pBitmapRGBA4444.cols * pBitmapRGBA4444.rows;
    int srcBypp = 2; // rgba4444
    int dstBypp = 4; // rgba

    for (int i = 0; i < length; ++i)
    {
        int srcIdx = i * srcBypp;
        int dstIdx = i * dstBypp;

        pDstBuffer[i * 4 + 0] = static_cast<uchar>(
                Clamp((pSrcBuffer[i * 2 + 1] >> 4) * mul4bitTo8bit, 0, 255));
        pDstBuffer[i * 4 + 1] = static_cast<uchar>(
                Clamp((pSrcBuffer[i * 2 + 1] & 0x0F) * mul4bitTo8bit, 0, 255));
        pDstBuffer[i * 4 + 2] = static_cast<uchar>(
                Clamp((pSrcBuffer[i * 2 + 0] >> 4) * mul4bitTo8bit, 0, 255));
        pDstBuffer[i * 4 + 3] = static_cast<uchar>(
                Clamp((pSrcBuffer[i * 2 + 0] & 0x0F) * mul4bitTo8bit, 0, 255));
    }

    return true;
}


bool Color::ConvRgbaToRgba4444(
        cv::Mat const& pBitmapRGBA4444,
        cv::Mat const& pBitmapRGBA)
{
    if (pBitmapRGBA.type() != CV_8UC4 || pBitmapRGBA4444.type() != CV_16UC1)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGBA.data;
    uchar* pDstBuffer = pBitmapRGBA4444.data;

    int length = pBitmapRGBA.cols * pBitmapRGBA.rows;
    int srcBypp = 4; // rgba
    int dstBypp = 2; // rgba4444

    for (int i = 0; i < length; ++i)
    {
        int srcIdx = i * srcBypp;
        int dstIdx = i * dstBypp;

        uchar r = static_cast<uchar>(Clamp(pSrcBuffer[srcIdx + 0] * mul8bitTo4bit, 0.f, 255.f));
        uchar g = static_cast<uchar>(Clamp(pSrcBuffer[srcIdx + 1] * mul8bitTo4bit, 0.f, 255.f));
        uchar b = static_cast<uchar>(Clamp(pSrcBuffer[srcIdx + 2] * mul8bitTo4bit, 0.f, 255.f));
        uchar a = 0x0F;

        pDstBuffer[dstIdx + 1] = (r << 4) | g;
        pDstBuffer[dstIdx + 0] = (b << 4) | a;
    }

    return true;
}


bool Color::ConvRgbToRgba5551(
        cv::Mat const& pBitmapRGBA5551,
        cv::Mat const& pBitmapRGB)
{
    if (pBitmapRGB.type() != CV_8UC3 || pBitmapRGBA5551.type() != CV_16UC1)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGB.data;
    uchar* pDstBuffer = pBitmapRGBA5551.data;

    int length = pBitmapRGB.cols * pBitmapRGB.rows;
    int srcBypp = 3; // rgb
    int dstBypp = 2; // rgba5551

    for (int i = 0; i < length; ++i)
    {
        int srcIdx = i * srcBypp;
        int dstIdx = i * dstBypp;

        uchar r = static_cast<uchar>(
                Clamp(round(pSrcBuffer[srcIdx + 0] * mul8bitTo5bit), 0.f, 255.f));
        uchar g = static_cast<uchar>(
                Clamp(round(pSrcBuffer[srcIdx + 1] * mul8bitTo5bit), 0.f, 255.f));
        uchar b = static_cast<uchar>(
                Clamp(round(pSrcBuffer[srcIdx + 2] * mul8bitTo5bit), 0.f, 255.f));
        uchar a = 0x01;

        pDstBuffer[dstIdx + 1] = (r << 3) | (g >> 2);
        pDstBuffer[dstIdx + 0] = (g << 6) | (b << 1) | a;
    }

    return true;
}


bool Color::ConvRgba5551ToRgb(
        cv::Mat const& pBitmapRGB,
        cv::Mat const& pBitmapRGBA5551,
        bool enablealpha)
{
    if (pBitmapRGBA5551.type() != CV_16UC1 || pBitmapRGB.type() != CV_8UC3)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGBA5551.data;
    uchar* pDstBuffer = pBitmapRGB.data;

    int length = pBitmapRGBA5551.cols * pBitmapRGBA5551.rows;
    int srcBypp = 2; // rgba5551
    int dstBypp = 3; // rgb

    if(!enablealpha)
    {
        for (int i = 0; i < length; ++i)
        {
            int srcIdx = i * srcBypp;
            int dstIdx = i * dstBypp;

            pDstBuffer[dstIdx + 0] = static_cast<uchar>(
                    Clamp((pSrcBuffer[srcIdx + 1] >> 3) * mul5bitTo8bit, 0.0, 255.0));

            uchar tmp = static_cast<uchar>(
                    ((pSrcBuffer[srcIdx + 1] & 0x07) << 2) |
                    (pSrcBuffer[srcIdx + 0] >> 6));

            pDstBuffer[dstIdx + 1] = static_cast<uchar>(
                    Clamp(tmp * mul5bitTo8bit, 0.0, 255.0));

            pDstBuffer[dstIdx + 2] = static_cast<uchar>(
                    Clamp(((pSrcBuffer[srcIdx + 0] & 0x3E) >> 1) * mul5bitTo8bit, 0.0, 255.0));
        }
    }
    else
    {
        for (int i = 0; i < length; ++i)
        {
            int srcIdx = i * srcBypp;
            int dstIdx = i * dstBypp;

            pDstBuffer[dstIdx + 0] = static_cast<uchar>(Clamp(
                    (pSrcBuffer[srcIdx + 1] >> 3) * mul5bitTo8bit * (pSrcBuffer[srcIdx + 1] & 0x01), 0.0, 255.0));

            uchar tmp = static_cast<uchar>(
                    ((pSrcBuffer[srcIdx + 1] & 0x07) << 2) | (pSrcBuffer[srcIdx + 0] >> 6));

            pDstBuffer[dstIdx + 1] = static_cast<uchar>(Clamp(
                    tmp * mul5bitTo8bit * (pSrcBuffer[srcIdx + 1] & 0x01), 0.0, 255.0));

            pDstBuffer[dstIdx + 2] = static_cast<uchar>(Clamp(
                    ((pSrcBuffer[srcIdx + 0] & 0x3E) >> 1) * mul5bitTo8bit
                    * (pSrcBuffer[srcIdx + 1] & 0x01), 0.0, 255.0));
        }
    }

    return true;
}



bool Color::ConvRgbaToRgba5551(
        cv::Mat const& pBitmapRGBA5551,
        cv::Mat const& pBitmapRGBA)
{
    if (pBitmapRGBA.type() != CV_8UC4 || pBitmapRGBA5551.type() != CV_16UC1)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGBA.data;
    uchar* pDstBuffer = pBitmapRGBA5551.data;

    int length = pBitmapRGBA.cols * pBitmapRGBA.rows;
    int srcBypp = 4; // rgba
    int dstBypp = 2; // rgba5551

    for (int i = 0; i < length; ++i)
    {
        int srcIdx = i * srcBypp;
        int dstIdx = i * dstBypp;

        uchar r = static_cast<uchar>(
                Clamp(round(pSrcBuffer[srcIdx + 0] * mul8bitTo5bit), 0.f, 255.f));
        uchar g = static_cast<uchar>(
                Clamp(round(pSrcBuffer[srcIdx + 1] * mul8bitTo5bit), 0.f, 255.f));
        uchar b = static_cast<uchar>(
                Clamp(round(pSrcBuffer[srcIdx + 2] * mul8bitTo5bit), 0.f, 255.f));
        uchar a = static_cast<uchar>(
                Clamp(round(pSrcBuffer[srcIdx + 3] * divideBy255), 0.f, 255.f));

        pDstBuffer[dstIdx + 1] = (r << 3) | (g >> 2);
        pDstBuffer[dstIdx + 0] = (g << 6) | (b << 1) | a;
    }

    return true;
}


bool Color::ConvRgba5551ToRgba(
        cv::Mat const& pBitmapRGBA,
        cv::Mat const& pBitmapRGBA5551)
{
    if (pBitmapRGBA5551.type() != CV_16UC1 || pBitmapRGBA.type() != CV_8UC4)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGBA5551.data;
    uchar* pDstBuffer = pBitmapRGBA.data;

    int length = pBitmapRGBA5551.cols * pBitmapRGBA5551.rows;
    int srcBypp = 2; // rgba5551
    int dstBypp = 4; // rgba

    for (int i = 0; i < length; ++i)
    {
        int srcIdx = i * srcBypp;
        int dstIdx = i * dstBypp;

        pDstBuffer[dstIdx + 0] = static_cast<uchar>(
                Clamp((pSrcBuffer[srcIdx + 1] >> 3) * mul5bitTo8bit, 0.0, 255.0));

        uchar tmp = static_cast<uchar>(
                ((pSrcBuffer[srcIdx + 1] & 0x07) << 2) |
                (pSrcBuffer[srcIdx + 0] >> 6));

        pDstBuffer[dstIdx + 1] = static_cast<uchar>(tmp * mul5bitTo8bit);

        pDstBuffer[dstIdx + 2] = static_cast<uchar>(
                Clamp(((pSrcBuffer[srcIdx + 0] & 0x3E) >> 1) * mul5bitTo8bit, 0.0, 255.0));

        pDstBuffer[dstIdx + 3] = static_cast<uchar>(
                Clamp((pSrcBuffer[srcIdx + 0] & 0x01) * 255, 0, 255));
    }

    return true;
}


bool Color::ConvRGBToGray(
        cv::Mat const& pBitmapGRAY,
        cv::Mat const& pBitmapRGB)
{
    if (pBitmapRGB.type() != CV_8UC3 || pBitmapGRAY.type() != CV_8UC1)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGB.data;
    uchar* pDstBuffer = pBitmapGRAY.data;

    int length = pBitmapRGB.cols * pBitmapRGB.rows;
    int channel = pBitmapRGB.channels();

    for (int i = 0; i < length; ++i)
    {
        int idx = i * channel;

        pDstBuffer[i] = static_cast<uchar>(
                Clamp((static_cast<int>(pSrcBuffer[idx + 0] * 4897)
                         + static_cast<int>(pSrcBuffer[idx + 1] * 9617)
                         + static_cast<int>(pSrcBuffer[idx + 2] * 1868)) >> 14, 0, 255));
    }

    return true;
}


bool Color::ConvGrayToRGB(
        cv::Mat const& pBitmapRGB,
        cv::Mat const& pBitmapGray)
{
    if (pBitmapGray.type() != CV_8UC1 || pBitmapRGB.type() != CV_8UC3)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapGray.data;
    uchar* pDstBuffer = pBitmapRGB.data;

    int length = pBitmapGray.cols * pBitmapGray.rows;
    int channel = pBitmapRGB.channels();

    for (int i = 0; i < length; ++i)
    {
        int idx = i * channel;

        pDstBuffer[idx + 0] = pSrcBuffer[i];
        pDstBuffer[idx + 1] = pSrcBuffer[i];
        pDstBuffer[idx + 2] = pSrcBuffer[i];
    }

    return true;
}


bool Color::ConvRGBAToGray(
        cv::Mat const& pBitmapGRAY,
        cv::Mat const& pBitmapRGBA,
        bool enableAlpha)
{
    if (pBitmapRGBA.type() != CV_8UC4 || pBitmapGRAY.type() != CV_8UC1)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGBA.data;
    uchar* pDstBuffer = pBitmapGRAY.data;

    int length = pBitmapRGBA.cols * pBitmapRGBA.rows;
    int channel = pBitmapRGBA.channels();

    if (!enableAlpha)
    {
        for (int i = 0; i < length; ++i)
        {
            int idx = i * channel;

            pDstBuffer[i] = static_cast<uchar>(
                    Clamp((((static_cast<int>(pSrcBuffer[idx + 0] * 4897))
                              + (static_cast<int>(pSrcBuffer[idx + 1] * 9617))
                              + (static_cast<int>(pSrcBuffer[idx + 2] * 1868))) >> 14), 0, 255));
        }
    }
    else
    {
        for (int i = 0; i < length; ++i)
        {
            int idx = i * channel;

            pDstBuffer[i] = static_cast<uchar>(
                    Clamp((((static_cast<int>(pSrcBuffer[idx + 0] * 4897))
                              + (static_cast<int>(pSrcBuffer[idx + 1] * 9617))
                              + (static_cast<int>(pSrcBuffer[idx + 2] * 1868))) >> 14)
                            * (static_cast<int>(pSrcBuffer[idx + 3] * divideBy255)), 0, 255));
        }
    }

    return true;
}


bool Color::ConvGrayToRGBA(
        cv::Mat const& pBitmapRGBA,
        cv::Mat const& pBitmapGray)
{
    if (pBitmapGray.type() != CV_8UC1 || pBitmapRGBA.type() != CV_8UC4)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapGray.data;
    uchar* pDstBuffer = pBitmapRGBA.data;

    int length = pBitmapGray.cols * pBitmapGray.rows;
    int channel = pBitmapRGBA.channels();

    for (int i = 0; i < length; ++i)
    {
        int idx = i * channel;

        pDstBuffer[idx + 0] = pSrcBuffer[i];
        pDstBuffer[idx + 1] = pSrcBuffer[i];
        pDstBuffer[idx + 2] = pSrcBuffer[i];
        pDstBuffer[idx + 3] = 255;
    }

    return true;
}



bool Color::ConvRGBToHSV(
        uchar r, uchar g, uchar b,
        double& h, double& s, double& v)
{
    float divide255 = 1 / 255.0f;

    float tmpR = r * divide255; //normalize
    float tmpG = g * divide255;
    float tmpB = b * divide255;

    double maxValue = max ( max(tmpR, tmpG), tmpB);
    double minValue = min ( min(tmpR, tmpG), tmpB);

    v = maxValue;
    s = (maxValue > 0) ? ((maxValue - minValue) / maxValue) : 0.f;

    if (s == 0.0) // (if s == 0 : r=g=b=0)
    {
        h = 0.0;
    }
    else
    {
        double delta = 1 / (maxValue - minValue);

        if (tmpR == maxValue)
            h = (tmpG - tmpB) * delta; // magenta & yellow
        else if (tmpG == maxValue)
            h = 2.0 + (tmpB - tmpR) * delta; // cyan & yellow
        else if (tmpB == maxValue)
            h = 4.0 + (tmpR - tmpG) * delta; // magenta & cyan

        h *= 60.0;

        if (h < 0.0)
            h += 360.0;
    }

    return true;
}

bool Color::ConvHSVToRGB(
        double h, double s, double v,
        uchar& r, uchar& g, uchar& b)
{
    double tmpR, tmpG, tmpB;

    if (s == 0.0)
    {
        if (h == 0)
            r = g = b = v;
        else
            r = g = b = 0;

        return true;
    }
    else
    {
        double v1, v2, v3, v4;
        long i;

        if (h == 360.0)
            h = 0;

        h /= 60.0;
        i = static_cast<long>(h);

        v1 = h - i;
        v2 = v * (1.0 - s);
        v3 = v * (1.0 - (s * v1));
        v4 = v * (1.0 - (s * (1.0 - v1)));

        switch (i)
        {
            case 0:
                tmpR = v; tmpG = v4; tmpB = v2;
                break;
            case 1:
                tmpR = v3; tmpG = v; tmpB = v2;
                break;
            case 2:
                tmpR = v2; tmpG = v; tmpB = v4;
                break;
            case 3:
                tmpR = v2; tmpG = v3; tmpB = v;
                break;
            case 4:
                tmpR = v4; tmpG = v2; tmpB = v;
                break;
            case 5:
                tmpR = v; tmpG = v2; tmpB = v3;
                break;
            default:
                return false;
        }

        r = static_cast<uchar>(tmpR * 255);
        g = static_cast<uchar>(tmpG * 255);
        b = static_cast<uchar>(tmpB * 255);
    }

    return true;
}



bool Color::ConvRGBToYCbCr(
        cv::Mat const& pBitmapYCbCr,
        cv::Mat const& pBitmapRGB)
{
    if (pBitmapRGB.type() != CV_8UC3 || pBitmapYCbCr.type() != CV_8UC3)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGB.data;
    uchar* pDstBuffer = pBitmapYCbCr.data;

    int width = pBitmapRGB.cols;
    int height = pBitmapRGB.rows;
    int channel = pBitmapRGB.channels();
    int stride = channel * width;

    for (int i = 0; i < height; ++i)
    {
        int yIdx = i * stride;

        for (int j = 0; j < width; ++j)
        {
            int idx = yIdx + j * channel;
            pDstBuffer[idx + 0]
                    = static_cast<uchar>(
                    Clamp(
                            0.257f * pSrcBuffer[idx + 0] + 0.504f * pSrcBuffer[idx + 1] + 0.098f * pSrcBuffer[idx + 2] + 16, 16.f, 235.f));
            pDstBuffer[idx + 1]
                    = static_cast<uchar>(
                    Clamp(
                            -0.148f * pSrcBuffer[idx + 0] - 0.291f * pSrcBuffer[idx + 1] + 0.439f * pSrcBuffer[idx + 2] + 128, 16.f, 240.f));
            pDstBuffer[idx + 2]
                    = static_cast<uchar>(
                    Clamp(
                            0.439f * pSrcBuffer[idx + 0] - 0.368f * pSrcBuffer[idx + 1] - 0.071f * pSrcBuffer[idx + 2] + 128, 16.f, 240.f));
        }
    }


    return true;
}

bool Color::ConvYCbCrToRGB(
        cv::Mat const& pBitmapRGB,
        cv::Mat const& pBitmapYCbCr)
{
    if (pBitmapRGB.type() != CV_8UC3 || pBitmapYCbCr.type() != CV_8UC3)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapYCbCr.data;
    uchar* pDstBuffer = pBitmapRGB.data;

    int width = pBitmapYCbCr.cols;
    int height = pBitmapYCbCr.rows;
    int channel = pBitmapYCbCr.channels();
    int stride = channel * width;

    for (int i = 0; i < height; ++i)
    {
        int yIdx = i * stride;

        for (int j = 0; j < width; ++j)
        {
            int idx = yIdx + j * channel;
            pDstBuffer[idx + 0]
                    = static_cast<uchar>(
                    Clamp(
                            1.164f * (pSrcBuffer[idx + 0] - 16)
                            + 0.000f * (pSrcBuffer[idx + 1] - 128)
                            + 1.596f * (pSrcBuffer[idx + 2] - 128), 0.f, 255.f));

            pDstBuffer[idx + 1]
                    = static_cast<uchar>(
                    Clamp(
                            1.164f * (pSrcBuffer[idx + 0] - 16)
                            - 0.392f * (pSrcBuffer[idx + 1] - 128)
                            - 0.813f * (pSrcBuffer[idx + 2] - 128), 0.f, 255.f));

            pDstBuffer[idx + 2]
                    = static_cast<uchar>(
                    Clamp(
                            1.164f * (pSrcBuffer[idx + 0] - 16)
                            + 2.017f * (pSrcBuffer[idx + 1] - 128)
                            + 0.000f * (pSrcBuffer[idx + 2] - 128), 0.f, 255.f));
        }
    }


    return true;
}



bool Color::ConvRGBToLab(
        cv::Mat const& pBitmapLab,
        cv::Mat const& pBitmapRGB)
{
    if (pBitmapRGB.type() != CV_8UC3 || pBitmapLab.type() != CV_8UC3)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGB.data;
    uchar* pDstBuffer = pBitmapLab.data;

    int width = pBitmapRGB.cols;
    int height = pBitmapRGB.rows;
    int channel = pBitmapRGB.channels();
    int stride = channel * width;

    double div255 = 1 / 255.0;
    double div1055 = 1 / 1.055;
    double div1292 = 1 / 12.92;
    double div3 = 1 / 3.0;
    double div116 = 16 / 116.0;
    double div95047 = 1 / 95.047;
    double div100 = 1 / 100.0;
    double div108883 = 1 / 108.883;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // rgb to xyz
            double r, g, b;

            int idx = (i * stride) + (channel * j);
            r = pSrcBuffer[idx + 0] * div255;
            g = pSrcBuffer[idx + 1] * div255;
            b = pSrcBuffer[idx + 2] * div255;

            if (r > 0.04045)
                r = pow(((r + 0.055) * div1055), 2.4);
            else
                r = r * div1292;

            if (g > 0.04045)
                g = pow(((g + 0.055) * div1055), 2.4);
            else
                g = g * div1292;

            if (b > 0.04045)
                b = pow(((b + 0.055) * div1055), 2.4);
            else
                b = b * div1292;

            r *= 100; g *= 100; b *= 100;

            double x, y, z;
            x = r * 0.4124 + g * 0.3576 + b * 0.1805;
            y = r * 0.2126 + g * 0.7152 + b * 0.0722;
            z = r * 0.0193 + g * 0.1192 + b * 0.9505;

            // xyz to lab
            x *= div95047;
            y *= div100;
            z *= div108883;

            if (x > 0.008856)
                x = pow(x, div3);
            else
                x = (7.787 * x) + div116;

            if (y > 0.008856)
                y = pow(y, div3);
            else
                y = (7.787 * y) + div116;

            if (z > 0.008856)
                z = pow(z, div3);
            else
                z = (7.787 * z) + div116;

            pDstBuffer[idx + 0]
                    = static_cast<uchar>(Clamp(round(((116 * y) - 16) * 2.55), 0.0, 255.0));
            pDstBuffer[idx + 1]
                    = static_cast<uchar>(Clamp(round(500 * (x - y) + 128), 0.0, 255.0));
            pDstBuffer[idx + 2]
                    = static_cast<uchar>(Clamp(round(200 * (y - z) + 128), 0.0, 255.0));
        }
    }

    return true;
}

bool Color::ConvLabToRGB(
        cv::Mat const& pBitmapRGB,
        cv::Mat const& pBitmapLab)
{
    if (pBitmapRGB.type() != CV_8UC3 || pBitmapLab.type() != CV_8UC3)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapLab.data;
    uchar* pDstBuffer = pBitmapRGB.data;

    int width = pBitmapLab.cols;
    int height = pBitmapLab.rows;
    int channel = pBitmapLab.channels();
    int stride = channel * width;

    double div255 = 1 / 2.55;
    double div116 = 1 / 116.0;
    double div500 = 1 / 500.0;
    double div200 = 1 / 200.0;
    double div16116 = 16 / 116.0;
    double div7787 = 1 / 7.787;
    double div100 = 1 / 100.0;
    double div24 = 1 / 2.4;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            double x, y, z;
            int idx = (i * stride) + (j * channel);

            y = ((pSrcBuffer[idx + 0] * div255) + 16) * div116;
            x = ((pSrcBuffer[idx + 1] - 128) * div500) + y;
            z = y - ((pSrcBuffer[idx + 2] - 128) * div200);

            if (pow(y, 3.0) > 0.008856)
                y = pow(y, 3.0);
            else
                y = (y - div16116) * div7787;

            if (pow(x, 3.0) > 0.008856)
                x = pow(x, 3.0);
            else
                x = (x - div16116) * div7787;

            if (pow(z, 3.0) > 0.008856)
                z = pow(z, 3.0);
            else
                z = (z - div16116) * div7787;

            x *= 95.047;
            y *= 100.0;
            z *= 108.883;

            //xyz to rgb
            double tmpr, tmpg, tmpb;
            tmpr = x * div100;
            tmpg = y * div100;
            tmpb = z * div100;

            double r, g, b;
            r = tmpr * 3.2406 + tmpg * (-1.5372) + tmpb * (-0.4986);
            g = tmpr * (-0.9689) + tmpg * 1.8758 + tmpb * 0.0415;
            b = tmpr * 0.0557 + tmpg * (-0.2040) + tmpb * 1.0570;

            if (r > 0.0031308)
                r = 1.055 * pow(r, div24) - 0.055;
            else
                r = 12.92 * r;

            if (g > 0.0031308)
                g = 1.055 * pow(g, div24) - 0.055;
            else
                g = 12.92 * g;

            if (b > 0.0031308)
                b = 1.055 * pow(b, div24) - 0.055;
            else
                b = 12.92 * b;

            pDstBuffer[idx + 0]
                    = static_cast<uchar>(Clamp(round(r * 255), 0.0, 255.0));
            pDstBuffer[idx + 1]
                    = static_cast<uchar>(Clamp(round(g * 255), 0.0, 255.0));
            pDstBuffer[idx + 2]
                    = static_cast<uchar>(Clamp(round(b * 255), 0.0, 255.0));
        }
    }


    return true;
}



bool Color::ConvRGBAToARGB(
        cv::Mat const& pBitmapARGB,
        cv::Mat const& pBitmapRGBA)
{
    if (pBitmapRGBA.type() != CV_8UC4 || pBitmapARGB.type() != CV_8UC4)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapRGBA.data;
    uchar* pDstBuffer = pBitmapARGB.data;

    int length = pBitmapRGBA.cols * pBitmapRGBA.rows;
    int channel = pBitmapRGBA.channels();

    for (int i = 0; i < length; ++i)
    {
        int idx = i * channel;

        int idx0 = idx + 0;
        int idx1 = idx + 1;
        int idx2 = idx + 2;
        int idx3 = idx + 3;

        pDstBuffer[idx0] = pSrcBuffer[idx3];
        pDstBuffer[idx1] = pSrcBuffer[idx0];
        pDstBuffer[idx2] = pSrcBuffer[idx1];
        pDstBuffer[idx3] = pSrcBuffer[idx2];
    }

    return true;
}


bool Color::ConvARGBToRGBA(
        cv::Mat const& pBitmapRGBA,
        cv::Mat const& pBitmapARGB)
{
    if (pBitmapARGB.type() != CV_8UC4 || pBitmapRGBA.type() != CV_8UC4)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    uchar* pSrcBuffer = pBitmapARGB.data;
    uchar* pDstBuffer = pBitmapRGBA.data;

    int length = pBitmapARGB.cols * pBitmapARGB.rows;
    int channel = pBitmapARGB.channels();

    for (int i = 0; i < length; ++i)
    {
        int idx = i * channel;

        int idx0 = idx + 0;
        int idx1 = idx + 1;
        int idx2 = idx + 2;
        int idx3 = idx + 3;

        pDstBuffer[idx0] = pSrcBuffer[idx1];
        pDstBuffer[idx1] = pSrcBuffer[idx2];
        pDstBuffer[idx2] = pSrcBuffer[idx3];
        pDstBuffer[idx3] = pSrcBuffer[idx0];
    }

    return true;
}


#ifdef YUV
bool ConvRGBToYUV444(
    std::shared_ptr<lte::Image> const& pBitmapYUV444,
    std::shared_ptr<lte::Image> const& pBitmapRGB)
{
    if (pBitmapRGB->pixelFormat() != lte::PIXEL_FORMAT_RGB || pBitmapYUV444->pixelFormat() != lte::PIXEL_FORMAT_YUV444)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    lte::uint8* pSrcBuffer = pBitmapRGB->data();
    lte::uint8* pDstBuffer = pBitmapYUV444->data();

    lte::int32 width = pBitmapRGB->width();
    lte::int32 height = pBitmapRGB->height();
    lte::int32 channel = pBitmapRGB->channel();
    lte::int32 stride = pBitmapRGB->stride();

    for (lte::int32 i = 0; i < height; ++i)
    {
        lte::int32 yIdx = i * stride;

        for (lte::int32 j = 0; j < width; ++j)
        {
            lte::int32 idx = yIdx + (j * channel);

            pDstBuffer[idx + 0] = static_cast<lte::uint8>(
                lte::Math::Clamp(
                    ((((pSrcBuffer[idx + 0] * 66)
                        + (pSrcBuffer[idx + 1] * 129)
                        + (pSrcBuffer[idx + 2] * 25) + 128) >> 8) + 16), 0, 255) );

            pDstBuffer[idx + 1] = static_cast<lte::uint8>(
                lte::Math::Clamp(
                    ((((pSrcBuffer[idx + 0] * (-38))
                        + (pSrcBuffer[idx + 1] * (-74))
                        + (pSrcBuffer[idx + 2] * 112) + 128) >> 8) + 128), 0, 255) );

            pDstBuffer[idx + 2] = static_cast<lte::uint8>(
                lte::Math::Clamp(
                    ((((pSrcBuffer[idx + 0] * 112)
                        + (pSrcBuffer[idx + 1] * (-94))
                        + (pSrcBuffer[idx + 2] * (-18)) + 128) >> 8) + 128), 0, 255) );
        }
    }

    return true;
}


bool ConvYUV444ToRGB(
    std::shared_ptr<lte::Image> const& pBitmapRGB,
    std::shared_ptr<lte::Image> const& pBitmapYUV444)
{
    if (pBitmapYUV444->pixelFormat() != lte::PIXEL_FORMAT_YUV444 || pBitmapRGB->pixelFormat() != lte::PIXEL_FORMAT_RGB)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    lte::uint8* pSrcBuffer = pBitmapYUV444->data();
    lte::uint8* pDstBuffer = pBitmapRGB->data();

    lte::int32 width = pBitmapYUV444->width();
    lte::int32 height = pBitmapYUV444->height();
    lte::int32 channel = pBitmapYUV444->channel();
    lte::int32 stride = pBitmapYUV444->stride();

    for (lte::int32 i = 0 ; i < height; ++i)
    {
        lte::int32 yIdx = i * stride;

        for (lte::int32 j = 0; j < width; ++j)
        {
            lte::int32 idx = yIdx + (j * channel);

            lte::int32 tmpY = pSrcBuffer[idx + 0] - 16;
            lte::int32 tmpU = pSrcBuffer[idx + 1] - 128;
            lte::int32 tmpV = pSrcBuffer[idx + 2] - 128;

            pDstBuffer[idx + 0] = static_cast<lte::uint8>(
                lte::Math::Clamp(((tmpY * 298) + (tmpV * 409) + 128) >> 8, 0, 255));

            pDstBuffer[idx + 1] = static_cast<lte::uint8>(
                lte::Math::Clamp(((tmpY * 298) - (tmpU * 100) - (tmpV * 208) + 128) >> 8, 0, 255));

            pDstBuffer[idx + 2] = static_cast<lte::uint8>(
                lte::Math::Clamp(((tmpY * 298) + (tmpU * 516) + 128) >> 8, 0, 255));
        }
    }

    return true;
}


bool ConvRGBToYUV422(
    std::shared_ptr<lte::Image> const& pBitmapYUV422,
    std::shared_ptr<lte::Image> const& pBitmapRGB)
{
    if (pBitmapRGB->pixelFormat() != lte::PIXEL_FORMAT_RGB || pBitmapYUV422->pixelFormat() != lte::PIXEL_FORMAT_YUV422)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    lte::uint8* pSrcBuffer = pBitmapRGB->data();
    lte::uint8* pDstBuffer = pBitmapYUV422->data();

    lte::int32 width = pBitmapRGB->width();
    lte::int32 height = pBitmapRGB->height();

    lte::int32 srcStride = pBitmapRGB->stride();
    lte::int32 dstStride = pBitmapYUV422->stride();

    lte::int32 srcBypp = pBitmapRGB->bypp(); // 3
    lte::int32 dstBypp = pBitmapYUV422->bypp(); // 2  ( |y u| |y v| ---)

    for (lte::int32 i = 0; i < height; ++i)
    {
        lte::int32 srcYIdx = i * srcStride;
        lte::int32 dstYIdx = i * dstStride;

        for (lte::int32 j = 0; j < width; ++j)
        {
            lte::int32 srcIdx = srcYIdx + (j * srcBypp);
            lte::int32 dstIdx = dstYIdx + (j * dstBypp);

            pDstBuffer[dstIdx + 0] = static_cast<lte::uint8>( // y
                lte::Math::Clamp(
                    ((((pSrcBuffer[srcIdx + 0] * 66)
                     + (pSrcBuffer[srcIdx + 1] * 129)
                     + (pSrcBuffer[srcIdx + 2] * 25) + 128) >> 8) + 16), 0, 255) );

            if (j % 2 == 0)
            {
                pDstBuffer[dstIdx + 1] = static_cast<lte::uint8>( // u
                    lte::Math::Clamp(
                        ((((pSrcBuffer[srcIdx + 0] * (-38))
                            + (pSrcBuffer[srcIdx + 1] * (-74))
                            + (pSrcBuffer[srcIdx + 2] * 112) + 128) >> 8) + 128), 0, 255) );

                pDstBuffer[(dstIdx + dstBypp) + 1] = static_cast<lte::uint8>( //v
                    lte::Math::Clamp(
                        ((((pSrcBuffer[srcIdx + 0] * 112)
                            + (pSrcBuffer[srcIdx + 1] * (-94))
                            + (pSrcBuffer[srcIdx + 2] * (-18)) + 128) >> 8) + 128), 0, 255) );
            }
        }
    }

    return true;
}


bool ConvYUV422ToRGB(
    std::shared_ptr<lte::Image> const& pBitmapRGB,
    std::shared_ptr<lte::Image> const& pBitmapYUV422)
{
    if (pBitmapYUV422->pixelFormat() != lte::PIXEL_FORMAT_YUV422 || pBitmapRGB->pixelFormat() != lte::PIXEL_FORMAT_RGB)
    {
        fprintf(stderr, "unsupported format\n");
        return false;
    }

    lte::uint8* pSrcBuffer = pBitmapYUV422->data();
    lte::uint8* pDstBuffer = pBitmapRGB->data();

    lte::int32 width = pBitmapYUV422->width();
    lte::int32 height = pBitmapYUV422->height();

    lte::int32 srcStride = pBitmapYUV422->stride();
    lte::int32 dstStride = pBitmapRGB->stride();

    lte::int32 srcBypp = pBitmapYUV422->bypp(); // 2
    lte::int32 dstBypp = pBitmapRGB->bypp(); // 3

    for (lte::int32 i = 0; i < height; ++i)
    {
        lte::int32 srcYIdx = i * srcStride;
        lte::int32 dstYIdx = i * dstStride;

        for (lte::int32 j = 0; j < width; ++j)
        {
            lte::int32 srcIdx = srcYIdx + (j * srcBypp);
            lte::int32 dstIdx = dstYIdx + (j * dstBypp);

            lte::int32 tmpY, tmpU, tmpV;

            if (j % 2 == 0)
            {
                tmpY = pSrcBuffer[srcIdx + 0] - 16;
                tmpU = pSrcBuffer[srcIdx + 1] - 128;
                tmpV = pSrcBuffer[(srcIdx + srcBypp) + 1] - 128;
            }
            else
            {
                tmpY = pSrcBuffer[srcIdx + 0] - 16;
                tmpU = pSrcBuffer[(srcIdx - srcBypp) + 1] - 128;
                tmpV = pSrcBuffer[srcIdx + 1] - 128;
            }

            pDstBuffer[dstIdx + 0] = static_cast<lte::uint8>(
                lte::Math::Clamp(((tmpY * 298) + (tmpV * 409) + 128) >> 8, 0, 255));

            pDstBuffer[dstIdx + 1] = static_cast<lte::uint8>(
                lte::Math::Clamp(((tmpY * 298) - (tmpU * 100) - (tmpV * 208) + 128) >> 8, 0, 255));

            pDstBuffer[dstIdx + 2] = static_cast<lte::uint8>(
                lte::Math::Clamp(((tmpY * 298) + (tmpU * 516) + 128) >> 8, 0, 255));
        }
    }

    return true;
}
#endif // YUV