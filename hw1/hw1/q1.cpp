#include <iostream>
#include <array>
#include<cmath>
#include<vector>
using namespace std;

double* dynamics(double x, double y, double z, double u, double v, double w, double phi, double theta, double shi, double p, double q, double r, double Fx, double Fy, double Fz, double Mx, double My, double Mz, double m, double Ix, double Iy, double Iz, double g)
{
    //definations
    double dx = (u * cos(theta) * cos(shi)) + (v * ((sin(phi) * sin(theta) * cos(shi)) - (cos(phi) * sin(shi)))) + (w * ((cos(phi) * sin(theta) * cos(shi)) + (sin(phi) * sin(shi))));
    double dy = (u * cos(theta) * sin(shi)) + (v * ((sin(phi) * sin(theta) * sin(shi)) + (cos(phi) * cos(shi)))) + (w * ((cos(phi) * sin(theta) * sin(shi)) - (sin(phi) * cos(shi))));
    double dz = (-u * sin(theta)) + (v * sin(phi) * cos(theta)) + (w * cos(phi) * cos(theta));
    double du = (r * v) - (q * w) - (g * sin(theta)) + (Fx / m);
    double dv = (p * w) - (r * u) + (g * sin(phi) * cos(theta)) + (Fy / m);
    double dw = (q * u) - (p * v) + (g * cos(phi) * cos(theta)) + (Fz / m);
    double dphi = p + (((q * sin(phi)) + (r * cos(phi))) * tan(theta));
    double dtheta = (q * cos(phi)) - (r * sin(phi));
    double dshi = ((q * sin(phi)) + (r * cos(phi))) / cos(theta);
    double dp = (((Iy - Iz) * q * r) + Mx) / Ix;
    double dq = (((Iz - Ix) * r * p) + My) / Iy;
    double dr = (((Ix - Iy) * p * q) + Mz) / Iz;
    double a[] = { dx, dy, dz, du, dv, dw, dphi, dtheta, dshi, dp, dq, dr }; // converting it into array
    return a;
}



double* integration(double x, double y, double z, double u, double v, double w, double phi, double theta, double shi, double p, double q, double r, double Fx, double Fy, double Fz, double Mx, double My, double Mz, double m, double Ix, double Iy, double Iz, double g, double T, double dt)
{
    for (double t = 0; t < T; t += dt)
    {
        // for loop for euler method
        double* b = dynamics(x, y, z, u, v, w, phi, theta, shi, p, q, r, Fx, Fy, Fz, Mx, My, Mz, m, Ix, Iy, Iz, g); // getting updated derivatives
        x = x + (b[0] * dt);
        y = y + (b[1] * dt);
        z = z + (b[2] * dt);
        u = u + (b[3] * dt);
        v = v + (b[4] * dt);
        w = w + (b[5] * dt);
        if (phi < 3.14 && phi >= -3.14)
        {
            phi = phi + (b[6] * dt);
        }
        if (theta < 3.14 && theta >= -3.14)
        {
            theta = theta + (b[7] * dt);
        }
        if (shi < 3.14 && shi >= -3.14)
        {
            shi = shi + (b[8] * dt);
        }
        p = p + (b[9] * dt);
        q = q + (b[10] * dt);
        r = r + (b[11] * dt);
        // for (int i = 0; i < 12; i++)
         //{
           //  cout << b[i] << "       ";
         //}
         //cout << endl;
    }
    static double c[] = { x,y,z,u,v,w,phi,theta,phi,p,q,r };
    return c;
}

int main()
{
    // Inital Conditions
    double x, y, u, v, w, phi, theta, shi, p, q, r, Fx, Fy, My, Mz;
    x = 0;
    y = 0;
    u = 0;
    v = 0;
    w = 0;
    phi = 0;
    theta = 0;
    shi = 0;
    p = 0;
    q = 0;
    r = 0;
    Fx = 0;
    Fy = 0;
    My = 0;
    Mz = 0;
    double m = 1.5;
    double Ix = 0.05;
    double Iy = 0.05;
    double Iz = 0.07;
    double g = 9.81;
    double z = -1;
    double Fz = -m * g;
    double Mx = 1;
    double dt = 0.001;
    double T = 3;

    double* final;
    final = integration(x, y, z, u, v, w, phi, theta, shi, p, q, r, Fx, Fy, Fz, Mx, My, Mz, m, Ix, Iy, Iz, g, T, dt);
    // Final States
    cout << "Array is: " << endl;
    cout << "x :" << final[0] << "\n";
    cout << "y :" << final[1] << "\n";
    cout << "z :" << final[2] << "\n";
    cout << "u :" << final[3] << "\n";
    cout << "v :" << final[4] << "\n";
    cout << "w :" << final[5] << "\n";
    cout << "phi :" << final[6] << "\n";
    cout << "theta :" << final[7] << "\n";
    cout << "shi :" << final[8] << "\n";
    cout << "p :" << final[9] << "\n";
    cout << "q :" << final[10] << "\n";
    cout << "r :" << final[11] << "\n";
    return 0;
}
