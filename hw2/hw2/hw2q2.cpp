#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

class Vector {
private:
    double x=0, y=0, z=0;
    double g[3] = {x, y, z};
public:
    Vector(double x_val=0, double y_val=0, double z_val=0) {
        x = x_val;
        y = y_val;
        z = z_val;
    }

    // addition
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y, z + other.z);
    }

    // subtraction
    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

    // Dot product
    double operator*(const Vector& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vector operator^(const Vector& other) const {
        double new_x = y * other.z - z * other.y;
        double new_y = z * other.x - x * other.z;
        double new_z = x * other.y - y * other.x;
        return Vector(new_x, new_y, new_z);
    }

    friend ostream& operator<<(std::ostream& out, const Vector& v) {
        out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return out;
    }
    double getx() 
    { return x; }
    double gety()
    { return y; }
    double getz()
    { return z; }

    ~Vector()
    {
    }
    
};

class Matrix {
private:
    double m[3][3];
    Vector x, y, z,g;
    double a, b, c;
public:
    Matrix(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
    {
        m[0][0] = a11;
        m[0][1] = a12;
        m[0][2] = a13;
        m[1][0] = a21;
        m[1][1] = a22;
        m[1][2] = a23;
        m[2][0] = a31;
        m[2][1] = a32;
        m[2][2] = a33;
    }

    // Element-wise addition
    Matrix operator+(const Matrix& other) const {
        Matrix result(0, 0, 0, 0, 0, 0, 0, 0, 0);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.m[i][j] = m[i][j] + other.m[i][j];
            }
        }
        return result;
    }

    // Element-wise subtraction
    Matrix operator-(const Matrix& other) const {
        Matrix result(0, 0, 0, 0, 0, 0, 0, 0, 0);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.m[i][j] = m[i][j] - other.m[i][j];
            }
        }
        return result;
    }

    // Matrix multiplication


    Matrix operator*(const Matrix& other) const
    {
        Matrix result(0, 0, 0, 0, 0, 0, 0, 0, 0);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.m[i][j] = 0;
                for (int k = 0; k < 3; k++)
                {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }
    //Transpose
    Matrix operator~() const
    {
        Matrix result(0, 0, 0, 0, 0, 0, 0, 0, 0);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++) {
                result.m[i][j] = m[j][i];
            }
        }
        return result;
    }
    
    //Matrix - vector multiplication
    Vector operator*(const Vector& g)
    {

            Vector result(a, b, c);
            for (int i = 0; i < 3; i++) {
                a += m[i][0] * x.getx();
            }
            for (int i = 0; i < 3; i++) {
                b+= m[i][1] * y.gety();
            }
            for (int i = 0; i < 3; i++) {
                c += m[i][2] * z.getz();
            }
          
            return result;
        }
    friend ostream& operator<<(ostream& os, const Matrix& mat) 
    {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                os << mat.m[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }
    ~Matrix()
    {
    }
};

int main() {
    Vector v(1, 2, 3);
    Matrix m(1, 2, 3, 4, 5, 6, 7, 8, 9);

    cout << "Vector = " << endl;
    cout << v << endl;

    Vector vsum = v + v;
    cout << "Vector Addition =" << endl;
    cout<< vsum << endl;

    Vector vsub = v - v;
    cout << "Vector Subtraction =" << endl;
    cout<< vsub << endl;

    double dp = v*v;
    cout << "Vector Dot Product =";
    cout << dp << endl;

    Vector cp = v ^ v;
    cout << "Vector Cross Product =" << endl;
    cout << cp << endl;

    cout << "Matrix = "<< endl;
    cout << m << endl;

    Matrix msum = m + m;
    cout << "Matrix Addition =" << endl;
    cout << msum << endl;

    Matrix msub = m - m;
    cout << "Matrix Subtraction =" << endl;
    cout << msub << endl;

    Matrix mp = m * m;
    cout << "Matrix Multiplication = " << endl;
    cout<< mp << endl;
    Matrix mt = ~m;
    cout << "Matrix Transpose = " << endl;
    cout << mt << endl;
    Vector q = m*v;
    cout << "Matrix Vector multiplication = " << endl;
    cout << q << endl;

    Vector ten = v * (m * v);
    cout << "Vector-transpose-Matrix-Vector = " << endl;
    cout << ten << endl;
    return 0;
}