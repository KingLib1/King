#ifndef KING_H
#define KING_H

namespace King {

enum AspectRatioMode {
    IgnoreAspectRatio,
    KeepAspectRatio,
    KeepAspectRatioByExpanding
};

enum ArcCreateMode {
    PointPointPoint,
    TangentPointPoint,
    PointPointTangent
};

enum Graphics3DType {
    Point3D,
    Line3D,
    Arc3D,
    Circle3D,
    Ellipse3D,
    Rect3D,
    RegularPolygon3D,
    Polygon3D,
    Torus3D,
};

namespace Line {
enum LinePlace {
    Start,
    Mid,
    End,
    Inner
};
}

namespace Circle {
enum CirclePlace {
    Center,
    Left,
    Right,
    Up,
    Down,
    Ring,
    Inner
};
}

namespace Arc {
enum ArcPlace {
    Center,
    Start,
    Mid,
    End,
    Ring
};
}

namespace Ellipse {
enum EllipsePlace {
    Center,
    Left,
    Right,
    Top,
    Bottom,
    Focus1,  // +
    Focus2,  // -
    Ring,
    Inner
};
}

namespace Rect {
enum RectPlace {
    Center,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    Left,
    Right,
    Top,
    Bottom,
    Inner
};
}

namespace RegularPolygon {
enum RegularPolygonPlace {
    Center,
    Vertex,
    Side,
    Inner
};
}

enum CoordinateAxisType {
    XAxis,
    YAxis,
    ZAxis,
};

enum CoordinateSystemAxisCreatMode {
    XY_Axis,
    YZ_Axis,
    ZX_Axis
};

enum PlaneType {
    XY_Plane,
    YZ_Plane,
    ZX_Plane,
};

enum OffsetType {
    LineConnection, //直线连接
    ArcConnection,  //圆弧连接
    ExtendConnection    //延长连接
};

enum ContainsType {
    NoContains, // 不包含
    OnSurface, // 在表面上
    Contains, // 包含在里面
};

}

#endif // KING_H
