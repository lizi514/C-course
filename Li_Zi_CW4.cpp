#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;

class point {
    public:
        double x, y;
        point (double a = 0.0, double b = 0.0): x(a), y(b) {}
        point operator+ (const point &p) const;
        point operator/ (const double &b) const;
};

point point::operator+ (const point &p) const {
    point newp;
    double xnew = x + p.x;
    double ynew = y + p.y;
    newp = point(xnew, ynew);
    return newp;
}

point point::operator/ (const double &b) const {
    point newp;
    double xnew = x / b;
    double ynew = y / b;
    newp = point(xnew, ynew);
    return newp;
}

class shape {
    protected:
        point centre;
    public:
        shape() { centre.x = centre.y = 0.0; }
        shape(const point &p) : centre(p) {}
        virtual double area() const = 0;
        virtual double circ() const = 0;
        double dist(const shape &s);
        virtual ~shape() {}
};

double shape::dist(const shape &s) {
    double distance = sqrt(pow(abs(centre.x - s.centre.x), 2) + pow(abs(centre.y - s.centre.y), 2));
    return distance;
}

class circle: public shape{
    double radius;
    public:
        circle (const point &p, double r) : shape(p) {
            if (r > 0) radius = r;
            else radius = 0.0;
        }
        double area() const {
            double a = M_PI * pow(radius, 2);
            return a;
        }
        double circ() const{
            double c = 2 * M_PI * radius;
            return c;
        }
};

class rectangle: public shape{
    double height, width;
    public:
        rectangle (const point &a, const point &b): shape((a+b)/2.0) {
            height = abs(b.y - a.y);
            width = abs(b.x - a.x);
        }
        double area() const {
            double a = height * width;
            return a;
        }
        double circ() const{
            double c = 2 * (height + width);
            return c;
        }
};

class triangle: public shape{
    double s1, s2, s3;
    public:
        triangle (const point &a, const point &b, const point &c): shape((a+b+c)/3.0) {
            s1 = sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
            s2 = sqrt(pow(abs(a.x - c.x), 2) + pow(abs(a.y - c.y), 2));
            s3 = sqrt(pow(abs(b.x - c.x), 2) + pow(abs(b.y - c.y), 2));
        }
        double area() const {
            double p = (s1 + s2 + s3) / 2.0;
            double a = sqrt(p * (p - s1) * (p - s2) * (p - s3));
            return a;
        }
        double circ() const{
            double c = s1 + s2 + s3;
            return c;
        }
};

double sratio(const shape &s) {
    double r;
    if (s.circ() == 0) r = 1.0;
    else r = s.area() / s.circ();
    return r;
}

int main()
{
    point p(-15,20), p1(0,0), p2(3,0), p3(1.5,3), p4(0,1), p5(3,2);
    circle c(p,5.0);
    triangle t(p1,p2,p3);
    rectangle r(p4,p5);
    cout << sratio(r) << endl;
    cout << "The distance between triangle and circle is " << t.dist(c) << endl;
    
    return 0;

}


