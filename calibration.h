#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <cmath>
#include "Eigen"
#include <iostream>
#ifdef _WIN32
    #include <corecrt_math_defines.h>
#endif

using namespace Eigen;

const  Matrix<double, 3, 1> OPT_DEFAULT(-1200, 2000, 50);

class Calibration
{
public:
    Calibration();
    Calibration(const Matrix<int, Dynamic, 1> & channel, const Matrix<double, Dynamic, 1> & angle, Matrix<double, 3, 1> opt = OPT_DEFAULT);
    // Getters
    Matrix<int, Dynamic, 1> channel() const ;
    Matrix<double, Dynamic, 1> angle() const ;
    Matrix<double, 3, 1> opt() const ;
    long int n_points() const ;
    // Setters
    Calibration &set_opt(Eigen::Matrix<double, 3, 1> opt);
    Calibration &set_opt(double a, double s, double beta);
    // Calculations
    double f(double x) const;
    double der_f_a(double x) const;
    double der_f_s(double x) const;
    Calibration & fit(double alpha = 1);
    Calibration & fit_cycle(int n, double alpha = 1);
    double error() const;

    // Info
    void info() const;

private:
    Matrix<int, Dynamic, 1> m_channel;
    Matrix<double, Dynamic, 1> m_angle;
    Matrix<double, 3, 1> m_opt;
    long int m_n_points;
};

#endif // CALIBRATION_H
