#ifndef ROBOT4_H
#define ROBOT4_H

#include <QVector>

#include "kjointcoor4.h"
#include "KDynamicVector.h"
#include "krange.h"
#include "ktoolcoordinatesystem.h"

class Robot4
{
public:
    Robot4();
    ~Robot4();

    inline void setLength1(double length) {len1_ = length;}
    inline void setLength2(double length) {len2_ = length;}
    inline void setAngle1Range(const KRange &range);
    inline void setAngle2Range(const KRange &range);
    inline void setToolCoordinateSystem(const KToolCoordinateSystem &tool);

    inline double length1() const {return len1_;}
    inline double length2() const {return len2_;}
    inline const KRange &angle1Range() const;
    inline const KRange &angle2Range() const;
    inline const KToolCoordinateSystem &toolCoordinateSystem() const;

    inline KPointF jointAngleCoorToFlangePos(const KJointCoor4 &coor) const;
    inline KPointF jointRadianCoorToFlangePos(const KJointCoor4 &coor) const;
    inline KPointF jointAngleCoorToToolPos(const KJointCoor4 &coor) const;
    inline KPointF jointRadianCoorToToolPos(const KJointCoor4 &coor) const;
    KJointCoor4 flangePosToJointCoor(
            const KPointF &pos, const KJointCoor4 &last_joint, bool &success);

    /**
     * @brief 工具坐标系无xy偏移下的20点标定，返回臂1长度误差，臂2长度误差，
     * 关节1零点误差，关节2零点误差所组成的数组
     */
    KDynamicVector<double> calibration20_1(const QVector<KJointCoor4> &coors);
    /**
     * @brief 工具坐标系有偏移下的20点标定，返回臂1长度误差，臂2长度误差，
     * 关节1零点误差，关节2零点误差，工具坐标dx和dy误差所组成的数组
     */
    KDynamicVector<double> calibration20_2(const QVector<KJointCoor4> &coors);

    void test();

private:
    inline bool isAngle1Legal(double angle) const;
    inline bool isAngle2Legal(double angle) const;

    double len1_;
    double len2_;
    KToolCoordinateSystem tool_;
    KRange angle1_range_;
    KRange angle2_range_;
};

inline void Robot4::setAngle1Range(const KRange &range)
{
    angle1_range_ = range;
}

inline void Robot4::setAngle2Range(const KRange &range)
{
    angle2_range_ = range;
}

inline void Robot4::setToolCoordinateSystem(const KToolCoordinateSystem &tool)
{
    tool_ = tool;
}

inline const KRange &Robot4::angle1Range() const
{
    return angle1_range_;
}

inline const KRange &Robot4::angle2Range() const
{
    return angle2_range_;
}

inline const KToolCoordinateSystem &Robot4::toolCoordinateSystem() const
{
    return tool_;
}

inline KPointF Robot4::jointAngleCoorToFlangePos(const KJointCoor4 &coor) const
{
    double r1 = kDegreesToRadians(coor.j1());
    double r2 = kDegreesToRadians(coor.j2());
    double r = r1 + r2;
    return KPointF(len1_ * kCos(r1) + len2_ * kCos(r),
                   len1_ * kSin(r1) + len2_ * kSin(r));
}

inline KPointF Robot4::jointRadianCoorToFlangePos(const KJointCoor4 &coor) const
{
    double r = coor.j1() + coor.j2();
    return KPointF(len1_ * kCos(coor.j1()) + len2_ * kCos(r),
                   len1_ * kSin(coor.j1()) + len2_ * kSin(r));
}

inline KPointF Robot4::jointAngleCoorToToolPos(const KJointCoor4 &coor) const
{
    double r1 = kDegreesToRadians(coor.j1());
    double r12 = kDegreesToRadians(coor.j1() + coor.j2());
    double r = kDegreesToRadians(coor.j1() + coor.j2() +
                                 coor.j4() + tool_.offsetRadian());
    return KPointF(len1_ * kCos(r1) + len2_ * kCos(r12) +
                   tool_.offsetLength() * kCos(r),
                   len1_ * kSin(r1) + len2_ * kSin(r12) +
                   tool_.offsetLength() * kSin(r));
}

inline KPointF Robot4::jointRadianCoorToToolPos(const KJointCoor4 &coor) const
{
    double r12 = coor.j1() + coor.j2();
    double r = coor.j1() + coor.j2() + coor.j4() + tool_.offsetRadian();
    return KPointF(len1_ * kCos(coor.j1()) + len2_ * kCos(r12) +
                   tool_.offsetLength() * kCos(r),
                   len1_ * kSin(coor.j1()) + len2_ * kSin(r12) +
                   tool_.offsetLength() * kSin(r));
}

inline bool Robot4::isAngle1Legal(double angle) const
{
    return angle1_range_.contains(angle);
}

inline bool Robot4::isAngle2Legal(double angle) const
{
    return angle2_range_.contains(angle);
}

#endif // ROBOT4_H
