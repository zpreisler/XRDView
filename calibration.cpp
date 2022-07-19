#include "calibration.h"


Calibration::Calibration()
{

}
Calibration::Calibration(const Matrix<int, Dynamic, 1> & channel, const Matrix<double, Dynamic, 1> & angle, Matrix<double, 3, 1> opt): m_channel(channel), m_angle(angle), m_opt(opt), m_n_points(channel.size())
{

}
// Getters
Matrix<int, Dynamic, 1> Calibration::channel() const {
    return m_channel;
}
Matrix<double, Dynamic, 1> Calibration::angle() const {
    return m_angle;
}

Matrix<double, 3, 1> Calibration::opt() const {
    return m_opt;
}

long int Calibration::n_points() const {
    return m_n_points;
}
// Setters
Calibration & Calibration::set_opt(Matrix<double, 3, 1> opt)
{
    m_opt = opt;
    return *this;
}

Calibration & Calibration::set_opt(double a, double s, double beta)
{
    Matrix<double, 3, 1> opt(a, s, beta);
    return set_opt(opt);
}

// Calculations
double Calibration::f(double x) const
{
    return (180 / M_PI) * atan( (x + m_opt(0)) / m_opt(1) ) + m_opt(2);
}

double Calibration::der_f_a(double x) const
{
    return (180 / M_PI) * m_opt(1) / ( pow(x + m_opt(0), 2) + pow(m_opt(1), 2) );
}

double Calibration::der_f_s(double x) const
{
    return - (180 / M_PI) * ( x + m_opt(0) ) / ( pow(x + m_opt(0), 2) + pow(m_opt(1), 2) );
}

Calibration & Calibration::fit(double alpha)
{
    Eigen::Matrix<double, Eigen::Dynamic, 3> Jacobian(m_n_points, 3);
    for (int i = 0; i < m_n_points; i++)
    {
        Jacobian(i, 0) = der_f_a(m_channel(i));
        Jacobian(i, 1) = der_f_s(m_channel(i));
        Jacobian(i, 2) = 1;
    }

    Eigen::Matrix<double, Eigen::Dynamic, 1> r(m_n_points, 1);
    for (int i = 0; i < m_n_points; i++)
        r(i) = m_angle(i) - f(m_channel(i));

    Eigen::Matrix<double, 3, 1> opt_evol = Jacobian.completeOrthogonalDecomposition().pseudoInverse() * r * alpha;
    m_opt += opt_evol;
    return *this;
}

Calibration & Calibration::fit_cycle(int n, double alpha)
{
    for (int i = 0; i < n; i++)
        fit(alpha);
    return *this;
}

double Calibration::error() const
{
    double error = 0;
    for (int i = 0; i < m_n_points; i++)
        error += pow(m_angle(i) - f(m_channel(i)), 2);
    return error;
}

void Calibration::info() const
{
    std::cout << m_opt.transpose() << ";\tloss = " << error() << std::endl;
}
