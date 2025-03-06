#ifndef ROBOT6_H
#define ROBOT6_H

#include "connectingrod6.h"
#include "jointrange6.h"
#include "posture.h"

class Robot6
{
public:
    Robot6();
    ~Robot6();

    inline void setConnectingRodParameter(const ConnectingRod6 &parameters);
    inline void setJointRange(const JointRange6 &range);
    inline void setToolCoordinateSystem(const Posture &tool);
    inline void setUserCoordinateSystem(const Posture &user);
//    inline void rotateTo(const JointCoor6 &coor);
//    inline void moveTo();

    inline const ConnectingRod6 &connectingRodParameters() const;
    inline const JointRange6 &jointRange() const;
    inline const Posture &toolCoordinateSystem() const;
    inline const Posture &userCoordinateSystem() const;
    inline const JointCoor6 &jointCoor() const;
    inline const Posture &flangeCoor() const;
    inline const Posture &rectCoor() const;
    inline const Posture &userCoor() const;

private:
    void jointCoorToFlangeCoor(const JointCoor6 &joint);

    ConnectingRod6 para_;  // 连杆参数
    JointRange6 range_;    // 关节范围
    JointCoor6 jointcoor_; // 关节坐标
    Posture flangecoor_;   // 法兰坐标
    Posture rectcoor_;     // 刀尖直角坐标
    Posture usercoor_;     // 刀尖用户坐标
    Posture toolsys_;      // 工具坐标系
    Posture usersys_;      // 用户坐标系

    KMatrix4x4 tool_mat_;  // 刀具坐标系矩阵
    KMatrix4x4 user_mat_;  // 用户坐标系矩阵
};

inline void Robot6::setConnectingRodParameter(const ConnectingRod6 &parameters)
{
    para_ = parameters;
}

inline void Robot6::setJointRange(const JointRange6 &range)
{
    range_ = range;
}

inline void Robot6::setToolCoordinateSystem(const Posture &tool)
{
    toolsys_ = tool;
    tool_mat_ = tool.toMatrix();
}

inline void Robot6::setUserCoordinateSystem(const Posture &user)
{
    usersys_ = user;
    user_mat_ = user.toMatrix();
}

inline const ConnectingRod6 &Robot6::connectingRodParameters() const
{
    return para_;
}

inline const JointRange6 &Robot6::jointRange() const
{
    return range_;
}

inline const Posture &Robot6::toolCoordinateSystem() const
{
    return toolsys_;
}

inline const Posture &Robot6::userCoordinateSystem() const
{
    return usersys_;
}

inline const JointCoor6 &Robot6::jointCoor() const
{
    return jointcoor_;
}

inline const Posture &Robot6::flangeCoor() const
{
    return flangecoor_;
}

inline const Posture &Robot6::rectCoor() const
{
    return rectcoor_;
}

inline const Posture &Robot6::userCoor() const
{
    return usercoor_;
}

#endif // ROBOT6_H
