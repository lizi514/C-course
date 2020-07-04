#include <iostream>
#include <complex>
#include <vector>
#include <math.h>
using namespace std;

template <typename T> class mathvector{
    
    friend mathvector operator* (const T &r, const mathvector &m) {
        mathvector<T> product;
        for (int i = 0; i < m.a.size(); i++) {
            product.push_back(r*m.a[i]);
        }
        return product;
    }
    friend ostream &operator<< (ostream &os, const mathvector &m){
        for (int i = 0; i < m.a.size()-1; i++) {
            os << m.a[i] << ", ";
        }
        os << m.a[m.a.size()-1];
        return os;
    }
    
    
    public:
    vector<T> a;
    mathvector() {}
    mathvector(vector<T> v): a(v) {}
    void push_back(T i) { a.push_back(i);}
    int dimension() { return a.size();}
    mathvector<T> operator+ (const mathvector &m) const;
    mathvector<T> operator- (const mathvector &m) const;
    mathvector<T> operator* (const T &r) const;
    T operator* (const mathvector &m) const;
    mathvector<T> operator- () const;
    mathvector<T> &operator+= (const mathvector &m);
    mathvector<T> &operator*= (const T &r);
    int type_id() const { return 0; }
    ~mathvector() {}
};

template<>
int mathvector<complex<double> >::type_id() const {return 1;}

template<>
int mathvector<double>::type_id() const {return 2;}

//+
template <typename T>
mathvector<T> mathvector<T>::operator+ (const mathvector &m) const {
    mathvector<T> sum;
    if (a.size() != m.a.size()){
        cout << "N/A" << endl;
    }
    else {
        for (int i = 0; i < a.size(); i++) {
            sum.push_back(a[i] + m.a[i]);
        }
    }
    return sum;
}

//-
template <typename T>
mathvector<T> mathvector<T>::operator- (const mathvector &m) const {
    mathvector<T> difference;
    if (a.size() != m.a.size()){
        cout << "N/A" << endl;
    }
    else {
        for (int i = 0; i < a.size(); i++) {
            difference.push_back(a[i] - m.a[i]);
        }
    }
    return difference;
}

//*
template <typename T>
mathvector<T> mathvector<T>::operator* (const T &r) const {
    mathvector<T> product;
    for (int i = 0; i < a.size(); i++) {
        product.push_back(a[i] *r);
    }
    return product;
}

// inner product
/*template <>
int mathvector<int>::operator* (const mathvector &m) const {
    int product = 0;
    if (a.size() != m.a.size()){
        cout << "N/A" << endl;
    }
    else {
        for (int i = 0; i < a.size(); i++) {
            product = product + a[i] * m.a[i];
        }
    }
    return product;
}

template <>
float mathvector<float>::operator* (const mathvector &m) const {
    float product = 0;
    if (a.size() != m.a.size()){
        cout << "N/A" << endl;
    }
    else {
        for (int i = 0; i < a.size(); i++) {
            product = product + a[i] * m.a[i];
        }
    }
    return product;
}*/

template <>
double mathvector<double>::operator* (const mathvector &m) const {
    double product = 0;
    if (a.size() != m.a.size()){
        cout << "N/A" << endl;
    }
    else {
        for (int i = 0; i < a.size(); i++) {
            product = product + a[i] * m.a[i];
        }
    }
    return product;
}

template <>
complex<double> mathvector<complex<double> >::operator* (const mathvector &m) const {
    complex<double> product = 0;
    if (a.size() != m.a.size()){
        cout << "N/A" << endl;
    }
    else {
        for (int i = 0; i < a.size(); i++) {
            product = product + conj(a[i]) * m.a[i];
        }
    }
    return product;
}

//negate
template <typename T>
mathvector<T> mathvector<T>::operator- () const {
    mathvector<T> negate;
    for (int i = 0; i < a.size(); i++) {
        negate.push_back(-a[i]);
    }
    return negate;
}

//+=
template <typename T>
mathvector<T> &mathvector<T>::operator+= (const mathvector &m) {
    if (a.size() != m.a.size()){
        cout << "N/A" << endl;
    }
    else {
        for (int i = 0; i < a.size(); i++) {
            a[i] = a[i] + m.a[i];
        }
    }
    return *this;
}

//*=
template <typename T>
mathvector<T> &mathvector<T>::operator*= (const T &r) {
    for (int i = 0; i < a.size(); i++) {
        a[i] = a[i] * r;
    }
    return *this;
}

//mathmatrix
template <typename T> class mathmatrix{
public:
    mathmatrix() {}
    virtual mathvector<T> operator* (mathvector<T> m) const = 0;
    virtual void y_eq_Ax(mathvector<T> &y, const mathvector<T> &x) const = 0;
    virtual T power_method(const mathvector<T> &m, int k) const = 0;
    virtual mathmatrix<T> &operator+= (const T &r) = 0;
    virtual mathmatrix<T> &operator-= (const T &r) = 0;
};

//fullmatrix
template <typename T> class fullmatrix: public mathmatrix<T>{
    friend ostream &operator<< (ostream &os, const fullmatrix &m){
        for (int i = 0; i < m.b.size()-1; i++) {
            for (int j = 0; j < m.b[0].size(); j++){
                os << m.b[i][j] << ", ";
            }
            os << endl;
        }
        for (int i = 0; i < m.b[0].size()-1; i++){
            os << m.b[m.b.size()-1][i] << ", ";
        }
        os << m.b[m.b.size()-1][m.b[0].size()-1] << ".";
        return os;
    }

public:
    vector<vector<T> > b;
    fullmatrix(const vector<vector<T> > &v) {
        b = v;
    }
    mathvector<T> operator* (mathvector<T> m) const {
        mathvector<T> product;
        if ( b[0].size() != m.a.size()){
            cout << "N/A" << endl;
            cout << b[0].size() << endl;
            return m;
        }
        else {
            for (int i = 0; i < b.size(); i++){
                T sum = 0;
                for (int j = 0; j < m.a.size(); j++) {
                    sum = sum + b[i][j] * m.a[j];
                }
                product.push_back(sum);
            }
            return product;
        }
    }
    
    void y_eq_Ax(mathvector<T> &y, const mathvector<T> &x) const {
        y = *this * x;
    }
    
    T power_method(const mathvector<T> &m, int k) const {
        mathvector<T> q = m * (1.0 / sqrt(m * m));
        for (int i = 0; i < k; i++) {
            mathvector<T> z = *this * q;
            q = z * (1.0 / sqrt(z * z));
        }
        T lambda = q * (*this * q);
        return lambda;
    }
    
    mathmatrix<T> &operator+= (const T &r) {
        for (int i = 0; i < b.size(); i++) {
            b[i][i] = b[i][i] + r;
        }
        return *this;
    }
    
    mathmatrix<T> &operator-= (const T &r) {
        for (int i = 0; i < b.size(); i++) {
            b[i][i] = b[i][i] - r;
        }
        return *this;
    }
};

//diagmatrix
template <typename T> class diagmatrix: public mathmatrix<T>{
    
    friend ostream &operator<< (ostream &os, const diagmatrix &d){
        for (int i = 0; i < d.c.size()-1; i++) {
            os << d.c[i] << ", ";
        }
        os << d.c[d.c.size()-1];
        return os;
    }

public:
    vector<T> c;
    diagmatrix(const vector<T> &v) {
        c = v;
    }
    mathvector<T> operator* (mathvector<T> m) const {
        mathvector<T> product;
        if ( c.size() != m.a.size()){
            cout << "N/A" << endl;
            cout << c.size() << endl;
            return m;
        }
        else {
            for (int i = 0; i < c.size(); i++){
                product.push_back(c[i] * m.a[i]);
            }
            return product;
        }
    }
    
    void y_eq_Ax(mathvector<T> &y, const mathvector<T> &x) const {
        y = *this * x;
    }
    
    T power_method(const mathvector<T> &m, int k) const {
        mathvector<T> q = m * (1.0 / sqrt(m * m));
        for (int i = 0; i < k; i++) {
            mathvector<T> z = *this * q;
            q = z * (1.0 / sqrt(z * z));
        }
        T lambda = q * (*this * q);
        return lambda;
    }
    
    mathmatrix<T> &operator+= (const T &r) {
        for (int i = 0; i < c.size(); i++) {
            c[i] = c[i] + r;
        }
        return *this;
    }
    
    mathmatrix<T> &operator-= (const T &r) {
        for (int i = 0; i < c.size(); i++) {
            c[i] = c[i] - r;
        }
        return *this;
    }
};

//CW5_matrix
template <typename T> class CW5_matrix: public mathmatrix<T>{
public:
    int n;
    CW5_matrix (int r): n(r) {}
    
    mathvector<T> operator* (mathvector<T> m) const {
        if (n == m.a.size()) {
            mathvector<T> product;
            if (n == 1) {
                product.push_back(2 * m.a[0]);
            }
            else if (n == 2) {
                product.push_back(2 * m.a[0] - m.a[1]);
                product.push_back(-m.a[0] + 2 * m.a[1]);
            }
            else {
                product.push_back(2 * m.a[0] - m.a[1] - m.a[m.a.size()-1]);
                for (int i = 1; i < n-1; i++){
                    product.push_back(2 * m.a[i] - m.a[i-1] - m.a[i+1]);
                }
                product.push_back(-m.a[0] - m.a[m.a.size()-2] + 2 * m.a[m.a.size()-1]);
            }
            return product;
        }
        else {
            cout << "N/A" << endl;
            return m;
        }
    }
    
    void y_eq_Ax(mathvector<T> &y, const mathvector<T> &x) const {
        y = *this * x;
    }
    
    T power_method(const mathvector<T> &m, int k) const {
        mathvector<T> q = m * (1.0 / sqrt(m * m));
        for (int i = 0; i < k; i++) {
            mathvector<T> z = *this * q;
            q = z * (1.0 / sqrt(z * z));
        }
        T lambda = q * (*this * q);
        return lambda;
    }
    
    mathmatrix<T> &operator+= (const T &r) {
        return *this;
    }
    mathmatrix<T> &operator-= (const T &r) {
        return *this;
    }
    
};
    
int main()
{
    int N = 10000, K = 4000;
    mathvector<double> x_a;
    for (int i = 0; i < N; i++) x_a.push_back(i+1);
    CW5_matrix<double> A(N);
    double lambda = A.power_method(x_a, K);
    cout << "largest lambda (in modulus) for A = " << lambda << endl;
    double b[] = {1.0, 1.0, 1.0, 1.0};
    vector<double> vb(b, b+4); mathvector<double> x_b(vb);// x = (1,1,1,1)^T
    cout << " x . x = " << x_b * x_b << endl;
    double r1[] = {3.0, 1.0, 2.0, 5.0}, r2[] = {1.0, 1.0, 3.0, 7.0}, r3[] = {2.0, 3.0, 2.0, 4.0}, r4[] = {5.0, 7.0, 4.0, 2.0};
    vector<double> row1(r1, r1+4), row2(r2, r2+4), row3(r3, r3+4), row4(r4,r4+4);
    vector<vector<double> > BB;
    BB.push_back(row1); BB.push_back(row2); BB.push_back(row3); BB.push_back(row4);
    fullmatrix<double> B(BB);
    B.y_eq_Ax(x_a, x_b); cout << x_a << endl;
    lambda = B.power_method(x_b, K);
    B -= lambda;
    double l2 = B.power_method(x_b, K);
    B += lambda;
    cout << "The spectrum of B lies between " << lambda << " and " << l2 + lambda << endl;
    diagmatrix<double> D(row4);
    lambda = D.power_method(x_b, K);
    cout << "largest lambda (in modulus) for D = " << lambda << endl;
    
    
    vector<vector<complex<double> > > CC;
    for (int i = 0; i < 4; i++) {
        vector<complex<double> > v;
        for (int j = 0; j < 4; j++) {
            complex<double> vv(i, j);
            v.push_back(vv);
        }
        CC.push_back(v);
    }
    
    fullmatrix<complex<double> > C(CC);
    cout << C << endl;
    
    return 0;
}
