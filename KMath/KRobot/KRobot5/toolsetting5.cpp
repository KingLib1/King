#include "toolsetting5.h"

#include "kmath.h"

KPair<double, double> calculateToolOffset(double len1, double len2, double a1,
                                          double b1, double a2, double b2)
{
    double offset_deg = (-b1 - b2) / 2;

    a1 += 90;
    a2 += 90;
    b1 += offset_deg;
    b2 += offset_deg;

    double ra1 = kDegreesToRadians(a1);
    double ra2 = kDegreesToRadians(a2);
    double rb1 = kDegreesToRadians(b1);
    double rb2 = kDegreesToRadians(b2);
    double real_len2 = len1 * (kCos(ra2) - kCos(ra1)) /
            (kCos(ra1 + rb1) - kCos(ra2 + rb2));

    double offset_rad = kDegreesToRadians(offset_deg);
    double fab_off_rad = kFabs(offset_rad);
    double tool_len = cosineTheorem_Edge(len1, real_len2, fab_off_rad);
    double tool_offset_rad = cosineTheorem_Radian3(len1, tool_len, real_len2);
    tool_offset_rad = K_PI - tool_offset_rad;

    if (offset_deg < 0)
        tool_offset_rad = -tool_offset_rad;

    return KPair<double, double>(tool_len, tool_offset_rad);
}
