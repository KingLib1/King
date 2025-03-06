#ifndef KCAMERA_H
#define KCAMERA_H

#include "kmatrix4x4.h"

enum KProjectionType {
    OrthographicProjection,
    PerspectiveProjection,
};


class KCamera
{
public:
    KCamera();

    inline void setAspectRatio(double ratio);
    inline void setLeft(double left);
    inline void setRight(double right);
    inline void setTop(double top);
    inline void setBottom(double bottom);
    inline void setNearPlane(double near);
    inline void setFarPlane(double far);
    inline void setFieldOfView(double field);
    inline void setExposure(double exposure);
    inline void setPosition(const KVector3D &position);
    inline void setUpVector(const KVector3D &up_vector);
    inline void setViewCenter(const KVector3D &center);
    inline void setProjectionType(KProjectionType type);

    inline double aspectRatio() const;
    inline double left() const;
    inline double right() const;
    inline double top() const;
    inline double bottom() const;
    inline double nearPlane() const;
    inline double farPlane() const;
    inline double fieldOfView() const;
    inline double exposure() const;
    inline const KVector3D &position() const;
    inline const KVector3D &upVector() const;
    inline const KVector3D &viewCenter() const;
    inline KVector3D viewVector() const;
    inline KProjectionType projectionType() const;

private:
    double aspect_ratio_;
    double left_;
    double right_;
    double top_;
    double bottom_;
    double near_plane_;
    double far_plane_;
    double field_of_view_;
    double exposure_;
    KVector3D position_;
    KVector3D up_vector_;
    KVector3D view_center_;
    KProjectionType projection_type_;
};

inline void KCamera::setAspectRatio(double ratio)
{
    aspect_ratio_ = ratio;
}

inline void KCamera::setLeft(double left)
{
    left_ = left;
}

inline void KCamera::setRight(double right)
{
    right_ = right;
}

inline void KCamera::setTop(double top)
{
    top_ = top;
}

inline void KCamera::setBottom(double bottom)
{
    bottom_ = bottom;
}

inline void KCamera::setNearPlane(double near)
{
    near_plane_ = near;
}

inline void KCamera::setFarPlane(double far)
{
    far_plane_ = far;
}

inline void KCamera::setFieldOfView(double field)
{
    field_of_view_ = field;
}

inline void KCamera::setExposure(double exposure)
{
    exposure_ = exposure;
}

inline void KCamera::setPosition(const KVector3D &position)
{
    position_ = position;
}

inline void KCamera::setUpVector(const KVector3D &up_vector)
{
    up_vector_ = up_vector;
}

inline void KCamera::setViewCenter(const KVector3D &center)
{
    view_center_ = center;
}

inline void KCamera::setProjectionType(KProjectionType type)
{
    projection_type_ = type;
}

inline double KCamera::aspectRatio() const
{
    return aspect_ratio_;
}

inline double KCamera::left() const
{
    return left_;
}

inline double KCamera::right() const
{
    return right_;
}

inline double KCamera::top() const
{
    return top_;
}

inline double KCamera::bottom() const
{
    return bottom_;
}

inline double KCamera::nearPlane() const
{
    return near_plane_;
}

inline double KCamera::farPlane() const
{
    return far_plane_;
}

inline double KCamera::fieldOfView() const
{
    return field_of_view_;
}

inline double KCamera::exposure() const
{
    return exposure_;
}

inline const KVector3D &KCamera::position() const
{
    return position_;
}

inline const KVector3D &KCamera::upVector() const
{
    return up_vector_;
}

inline const KVector3D &KCamera::viewCenter() const
{
    return view_center_;
}

inline KVector3D KCamera::viewVector() const
{
    return view_center_ - position_;
}

inline KProjectionType KCamera::projectionType() const
{
    return projection_type_;
}

#endif // KCAMERA_H
