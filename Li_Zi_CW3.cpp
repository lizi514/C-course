#include <iostream>
#include <string>
using namespace std;

class fraction {
    friend ostream &operator<< (ostream &os, const fraction &f);
    friend fraction operator+ (const int &i, const fraction &f);
    friend fraction operator- (const int &i, const fraction &f);
    friend fraction operator* (const int &i, const fraction &f);
    friend fraction operator/ (const int &i, const fraction &f);
    friend bool operator< (const double &d, const fraction &f);
private:
    int numerator, denominator;
    void reduce();
public:
    operator double() const {
        return (double)numerator / (double)denominator;
    }
    fraction(int n = 0, int d = 1) : numerator(n), denominator(d) { reduce(); }
    fraction(const fraction &f) : numerator(f.numerator), denominator(f.denominator) { reduce(); }
    fraction operator+ (const fraction &f) const;
    fraction operator+ (const int &i) const;  
    fraction operator- (const fraction &f) const; 
    fraction operator- (const int &i) const;  
    fraction operator* (const fraction &f) const;
    fraction operator* (const int &i) const;  
    fraction operator/ (const fraction &f) const;
    fraction operator/ (const int &i) const;  
    fraction &operator+= (const fraction &f);
    fraction &operator-= (const fraction &f);
    fraction &operator*= (const fraction &f);
    fraction &operator/= (const fraction &f);
    bool operator< (const fraction &f) const;
    fraction operator- () const { fraction res(-numerator, denominator); return res; }
};

ostream &operator<< (ostream &os, const fraction &f) {
    if(f.denominator == 1){
        os << f.numerator;
    }
    else{
        os << f.numerator << "/" << f.denominator;
    }
    return os; 
}

void fraction::reduce(){
    int a = numerator; int b = denominator; int c = 1;
    while( b != 0 && c != 0){
        c = a % b;
        a = b; b = c;
    }
    denominator = denominator / a;
    numerator = numerator / a;
    if (denominator * numerator < 0){
        numerator = -abs(numerator);
        denominator = abs(denominator);
    }
}

//f + f
fraction fraction::operator+ (const fraction &f) const {
   int newdenominator = denominator * f.denominator;
    int newnumerator = numerator * f.denominator + f.numerator * denominator;
    fraction c = fraction(newnumerator,newdenominator);
    return c;
}

//int + f
fraction operator+ (const int &i, const fraction &f) {
    int newnumerator = i * f.denominator + f.numerator;
    fraction c = fraction(newnumerator,f.denominator);
    return c;
}

//f + int
fraction fraction::operator+ (const int &i) const {
    int newnumerator = i * denominator + numerator;
    fraction c = fraction(newnumerator,denominator);
    return c;
}

//f - f
fraction fraction::operator- (const fraction &f) const {
    int newdenominator = denominator * f.denominator;
    int newnumerator = numerator * f.denominator - f.numerator * denominator;
    fraction c = fraction(newnumerator,newdenominator);
    return c;
}

//f - int
fraction fraction::operator- (const int &i) const {
    int newnumerator = numerator - i * denominator;
    fraction c = fraction(newnumerator,denominator);
    return c;
}

//int - f
fraction operator- (const int &i, const fraction &f) {
    int newnumerator = i * f.denominator - f.numerator;
    fraction c = fraction(newnumerator,f.denominator);
    return c;
}

//f * f
fraction fraction::operator* (const fraction &f) const {
    int newdenominator = denominator * f.denominator;
    int newnumerator = numerator * f.numerator;
    fraction c = fraction(newnumerator,newdenominator);
    return c;
}

//f * int
fraction fraction::operator* (const int &i) const {
    int newnumerator = i * numerator;
    fraction c = fraction(newnumerator,denominator);
    return c;
}

//int * f
fraction operator* (const int &i, const fraction &f) {
    int newnumerator = i * f.numerator;
    fraction c = fraction(newnumerator,f.denominator);
    return c;
}

//f / f
fraction fraction::operator/ (const fraction &f) const {
    fraction c = fraction(f.denominator,f.numerator);
    return *this * c;
}

//f / int
fraction fraction::operator/ (const int &i) const {
    fraction c = fraction(1,i);
    return *this * c;
}

//int / f
fraction operator/ (const int &i, const fraction &f) {
    fraction c = fraction(f.denominator,f.numerator);
    return i * c;
}

fraction &fraction::operator+= (const fraction &f) {
    numerator = numerator * f.denominator + f.numerator * denominator;
    denominator = denominator * f.denominator;
    reduce();
    return *this;
}

fraction &fraction::operator-= (const fraction &f) {
    numerator = numerator * f.denominator - f.numerator * denominator;
    denominator = denominator * f.denominator;
    reduce();
    return *this;
}

fraction &fraction::operator*= (const fraction &f) {
    numerator = numerator * f.numerator;
    denominator = denominator * f.denominator;
    reduce();
    return *this;
}

fraction &fraction::operator/= (const fraction &f) {
    numerator = numerator * f.denominator;
    denominator = denominator * f.numerator;
    reduce();
    return *this;
}

bool fraction::operator< (const fraction &f) const{
    int a = numerator * f.denominator;
    int b = f.numerator * denominator;
    return ( a < b);
}

bool operator< (const double &d, const fraction &f) {
    double a = (double) f;
    return ( d < a);
}

int main()
{
    fraction a(1,12), b(1,25), c(1,300), e(3,4), f(2,5), g(7,2), h;
    cout << a << " + " << b << " + " << c << " = " << a+b+c << endl;
    if (-a < b) cout << -a << " < " << b << endl;
    else cout << -a << " >= " << b << endl;
    h = e*f-g;
    cout << e << " * " << f << " - " << g << " = " << h << endl;
    fraction i(-1,6), j(5,17), k(3,5);
    cout << i << " + " << j << " / " << k << " = " << i+j/k << endl;
    int m = 2, q = 1;
    fraction n(1,3), p(4,5), s(a), t(b), u(c), w(e), x(f), y(g), v, z;
    cout << m << " + " << n << " = " << m+n << endl;
    cout << p << " - " << q << " = " << p-q << endl;
    v = (a+=b-=u);
    cout << s << " += " << t << " -= " << u << " = " << v << endl;
    z = (e*=f/=g);
    cout << w << " *= " << x << " /= " << y << " = " << z << endl;
    double d = (double) e;
    if (d < f) cout << d << " < " << f << endl;
    else cout << d << " >= " << f << endl;
    return 0;
}
