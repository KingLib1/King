#include "kellipsex.h"

#include "kmatrix2x2.h"

KEllipseX::KEllipseX() : a_(0), b_(0)
{

}

KEllipseX::KEllipseX(double a, double b, const KRectCoordSystem2D &sys) :
    a_(a), b_(b), sys_(sys)
{

}

KEllipseX::KEllipseX(const KVector3D &coefficient)
{
    double a = coefficient.x();
    double b = coefficient.y();
    double c = coefficient.z();
    double c_2 = c / 2;
    KMatrix2x2 A(a, c_2, c_2, b);
    KPair<double, double> eigenvalues;
    KPair<KVector2D, KVector2D> eigenvectors = A.eigenvectors(eigenvalues);
    a_ = kSqrt(1.0 / eigenvalues.first);
    b_ = kSqrt(1.0 / eigenvalues.second);
    sys_.setXAxis(eigenvectors.first);
}

KVector3D KEllipseX::toEquationCoefficient() const
{
    double a = 1.0 / (a_ * a_);
    double b = 1.0 / (b_ * b_);
    double c = sys_.xAxis().x();
    double d = sys_.xAxis().y();
    double c2 = c * c;
    double d2 = d * d;
    return KVector3D(a*c2 + b*d2, a*d2 + b*c2, 2*(a - b)*c*d);
}
