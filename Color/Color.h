/**
 * Created by Rachel.minii 
 * Date : 2018. 6. 20.
 * Project : ImageProcessing
 */

#include <highgui.h>

template <typename Ty>
inline Ty Clamp(Ty const& a, Ty const& minValue, Ty const& maxValue)
{
    return a < minValue ? minValue : (maxValue < a ? maxValue : a);
}

class Color {

public:

    bool ConvRgbToRgb565(
            cv::Mat const& pBitmapRGB565,
            cv::Mat const& pBitmapRGB);

    bool ConvRgb565ToRgb(
            cv::Mat const& pBitmapRGB,
            cv::Mat const& pBitmapRGB565);

    bool ConvRgbaToRgb565(
            cv::Mat const& pBitmapRGB565,
            cv::Mat const& pBitmapRGBA,
            bool enablealpha = false);

    bool ConvRgb565ToRgba(
            cv::Mat const& pBitmapRGBA,
            cv::Mat const& pBitmapRGB565);

    bool ConvRgbToRgba4444(
            cv::Mat const& pBitmapRGBA4444,
            cv::Mat const& pBitmapRGB);

    bool ConvRgba4444ToRgb(
            cv::Mat const& pBitmapRGB,
            cv::Mat const& pBitmapRGBA4444,
            bool enablealpha = false);

    bool ConvRgbaToRgba4444(
            cv::Mat const& pBitmapRGBA4444,
            cv::Mat const& pBitmapRGBA);

    bool ConvRgba4444ToRgba(
            cv::Mat const& pBitmapRGBA,
            cv::Mat const& pBitmapRGBA4444);

    bool ConvRgbToRgba5551(
            cv::Mat const& pBitmapRGBA5551,
            cv::Mat const& pBitmapRGB);

    bool ConvRgba5551ToRgb(
            cv::Mat const& pBitmapRGB,
            cv::Mat const& pBitmapRGBA5551,
            bool enablealpha = false);

    bool ConvRgbaToRgba5551(
            cv::Mat const& pBitmapRGBA5551,
            cv::Mat const& pBitmapRGBA);

    bool ConvRgba5551ToRgba(
            cv::Mat const& pBitmapRGBA,
            cv::Mat const& pBitmapRGBA5551);

    bool ConvRGBToGray(
            cv::Mat const& pBitmapGRAY,
            cv::Mat const& pBitmapRGB);

    bool ConvGrayToRGB(
            cv::Mat const& pBitmapRGB,
            cv::Mat const& pBitmapGray);

    bool ConvRGBAToGray(
            cv::Mat const& pBitmapGRAY,
            cv::Mat const& pBitmapRGB,
            bool enablealpha = false);

    bool ConvGrayToRGBA(
            cv::Mat const& pBitmapRGBA,
            cv::Mat const& pBitmapGray);

    bool ConvRGBToHSV(
            uchar r, uchar g, uchar b,
            double& h, double& s, double& v);

    bool ConvHSVToRGB(
            double h, double s, double v,
            uchar& r, uchar& g, uchar& b);

    bool ConvRGBToYCbCr(
            cv::Mat const& pBitmapYCbCr,
            cv::Mat const& pBitmapRGB);

    bool ConvYCbCrToRGB(
            cv::Mat const& pBitmapRGB,
            cv::Mat const& pBitmapYCbCr);

    bool ConvRGBToLab(
            cv::Mat const& pBitmapLab,
            cv::Mat const& pBitmapRGB);

    bool ConvLabToRGB(
            cv::Mat const& pBitmapRGB,
            cv::Mat const& pBitmapLab);

    bool ConvRGBAToARGB(
            cv::Mat const& pBitmapARGB,
            cv::Mat const& pBitmapRGBA);

    bool ConvARGBToRGBA(
            cv::Mat const& pBitmapRGBA,
            cv::Mat const& pBitmapARGB);


#ifdef YUV
bool ConvRGBToYUV444(
    std::shared_ptr<lte::Image> const& pBitmapYUV444,
    std::shared_ptr<lte::Image> const& pBitmapRGB);

bool ConvYUV444ToRGB(
    std::shared_ptr<lte::Image> const& pBitmapRGB,
    std::shared_ptr<lte::Image> const& pBitmapYUV444);

bool ConvRGBToYUV422(
    std::shared_ptr<lte::Image> const& pBitmapYUV422,
    std::shared_ptr<lte::Image> const& pBitmapRGB);

bool ConvYUV422ToRGB(
    std::shared_ptr<lte::Image> const& pBitmapRGB,
    std::shared_ptr<lte::Image> const& pBitmapYUV422);
#endif // YUV
};



