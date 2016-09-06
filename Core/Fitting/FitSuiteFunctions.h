// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteFunctions.h
//! @brief     Defines classes IFitSuiteFunction,
//!              FitSuiteChiSquaredFunction, FitSuiteGradientFunction
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEFUNCTIONS_H
#define FITSUITEFUNCTIONS_H

#include "WinDllMacros.h"
#include <vector>
using std::size_t;

class FitKernel;

//! @class IFitSuiteFunction
//! @ingroup fitting_internal
//! @brief Fitting functions interface to be used by Minimizer.

class BA_CORE_API_ IFitSuiteFunction
{
 public:
    IFitSuiteFunction() : m_kernel(0), m_ncall(0) {}
    virtual ~IFitSuiteFunction() {}
    virtual void init(FitKernel* fit_suite) { m_kernel = fit_suite; }
    virtual size_t getNCalls() const { return m_ncall; }
 protected:
    FitKernel* m_kernel;
    size_t m_ncall;
};


//! @class FitSuiteChiSquaredFunction
//! @ingroup fitting_internal
//! @brief Chi squared fitting function for minimizer

class BA_CORE_API_ FitSuiteChiSquaredFunction : public IFitSuiteFunction
{
 public:
    FitSuiteChiSquaredFunction() {}
    virtual ~FitSuiteChiSquaredFunction() {}
    //! evaluate method for chi2 value called directly from the minimizer
    double evaluate(const double* pars);
};


//! @class FitSuiteGradientFunction
//! @ingroup fitting_internal
//! @brief Gradient fitting function for minimizer

class BA_CORE_API_ FitSuiteGradientFunction : public IFitSuiteFunction
{
 public:
    FitSuiteGradientFunction()
        : m_npars(0), m_ndatasize(0), m_prev_index(-1),
          m_ncalls_total(0), m_ncalls_gradient(0) {}
    virtual ~FitSuiteGradientFunction() {}
    //! evaluate method for gradients and residuals called directly from the minimizer
    double evaluate(const double* pars, unsigned int index, double* gradients);
    virtual size_t getNCallsTotal() const { return m_ncalls_total; }
    virtual size_t getNCallsGradient() const { return m_ncalls_gradient; }

 private:
    void verify_arrays();
    void verify_minimizer_logic(bool parameters_have_changed, int current_index);
    void calculate_residuals(const double* pars);
    void calculate_gradients(const double* pars);
    void runSimulation(const double* pars);

    size_t m_npars;
    size_t m_ndatasize;
    int m_prev_index;
    std::vector<double> m_residuals; // [m_ndatasize]
    std::vector<std::vector<double>> m_gradients; // [m_npars][m_ndatasize]
    size_t m_ncalls_total;
    size_t m_ncalls_gradient;
};

#endif // FITSUITEFUNCTIONS_H