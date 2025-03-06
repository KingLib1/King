#include "ksizef.h"

KSizeF::KSizeF() : width_(0), height_(0)
{

}

KSizeF::KSizeF(double width, double height) :
    width_(width), height_(height)
{

}

KSizeF::KSizeF(const KSizeF &size) :
    width_(size.width_), height_(size.height_)
{

}

void KSizeF::scale(double width, double height, King::AspectRatioMode mode)
{
    if (mode == King::IgnoreAspectRatio) {
        width_ = width;
        height_ = height;
    } else if (mode == King::KeepAspectRatio) {
        if (width_ * height > width * height_) {
            height_ *= width / width_;
            width_ = width;
        } else {
            width_ *= height / height_;
            height_ = height;
        }
    } else {
        if (width_ * height > width * height_) {
            width_ *= height / height_;
            height_ = height;
        } else {
            height_ *= width / width_;
            width_ = width;
        }
    }
}
