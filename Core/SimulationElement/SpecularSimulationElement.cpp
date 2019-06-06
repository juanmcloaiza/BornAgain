// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SimulationElement/SpecularSimulationElement.cpp
//! @brief     Implements the class SpecularSimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularSimulationElement.h"
#include "KzComputation.h"
#include "Layer.h"
#include "MultiLayer.h"

SpecularSimulationElement::SpecularSimulationElement(double kz)
    : m_kz(kz)
    , m_intensity(0.0)
    , m_calculation_flag(true)
    , m_kz_computation([kz](const MultiLayer& sample) {
          return KzComputation::computeKzFromSLDs(sample, kz);
      })
{}

SpecularSimulationElement::SpecularSimulationElement(double wavelength, double alpha)
    : m_kz(0)
    , m_intensity(0.0)
    , m_calculation_flag(true)
    , m_kz_computation(
          [k = vecOfLambdaAlphaPhi(wavelength, alpha, /*phi =*/0.0)](const MultiLayer& sample) {
              return KzComputation::computeKzFromRefIndeces(sample, k);
          })
{
    m_kz = vecOfLambdaAlphaPhi(wavelength, alpha, /*phi =*/0.0).z();
}

SpecularSimulationElement::SpecularSimulationElement(const SpecularSimulationElement& other)
    : m_kz(other.m_kz)
    , m_polarization(other.m_polarization)
    , m_intensity(other.m_intensity)
    , m_calculation_flag(other.m_calculation_flag)
    , m_kz_computation(other.m_kz_computation)
{
}

SpecularSimulationElement::SpecularSimulationElement(SpecularSimulationElement&& other) noexcept
    : m_kz(other.m_kz)
    , m_polarization(std::move(other.m_polarization))
    , m_intensity(other.m_intensity)
    , m_calculation_flag(other.m_calculation_flag)
    , m_kz_computation(std::move(other.m_kz_computation))
{
}

SpecularSimulationElement::~SpecularSimulationElement() = default;

SpecularSimulationElement& SpecularSimulationElement::
operator=(const SpecularSimulationElement& other)
{
    if (this != &other) {
        SpecularSimulationElement tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

std::vector<complex_t> SpecularSimulationElement::produceKz(const MultiLayer& sample)
{
    return m_kz_computation(sample);
}

void SpecularSimulationElement::swapContent(SpecularSimulationElement &other)
{
    m_polarization.swapContent(other.m_polarization);
    std::swap(m_intensity, other.m_intensity);
    std::swap(m_calculation_flag, other.m_calculation_flag);
    m_kz_computation.swap(other.m_kz_computation);
}
