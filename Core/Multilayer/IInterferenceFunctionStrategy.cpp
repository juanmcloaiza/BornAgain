// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IInterferenceFunctionStrategy.cpp
//! @brief     Implements default behaviour of IInterferenceFunctionStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IInterferenceFunctionStrategy.h"
#include "WeightedFormFactor.h"
#include "IFormFactor.h"
#include "IInterferenceFunction.h"
#include "IntegratorMCMiser.h"
#include "LayerSpecularInfo.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include "ScalarRTCoefficients.h"
#include "SimulationElement.h"
#include "WavevectorInfo.h"

IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(
    const SimulationOptions& sim_params)
    : mP_iff { nullptr }
    , m_options(sim_params)
{
    mP_integrator = make_integrator_miser(
        this, &IInterferenceFunctionStrategy::evaluate_for_fixed_angles, 2);
    mP_integrator_pol = make_integrator_miser(
        this, &IInterferenceFunctionStrategy::evaluate_for_fixed_angles_pol, 2);
}

// destructor should be defined and it should be in *.cpp,
// otherwise forward declaration of IntegratorMCMiser doesn't work
IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy() {}

void IInterferenceFunctionStrategy::init(
    const SafePointerVector<WeightedFormFactor>& weighted_formfactors,
    const IInterferenceFunction& iff)
{
    m_weighted_ffs = weighted_formfactors;
    mP_iff.reset(iff.clone());
    m_total_abundance = 0;
    for (const auto wff: m_weighted_ffs)
        m_total_abundance += wff->m_abundance;
}

void IInterferenceFunctionStrategy::setSpecularInfo(const LayerSpecularInfo& specular_info)
{
    if (mP_specular_info.get() != &specular_info)
        mP_specular_info.reset(specular_info.clone());
}

double IInterferenceFunctionStrategy::evaluate(const SimulationElement& sim_element) const
{
    if (m_options.isIntegrate() && (sim_element.getSolidAngle() > 0.0))
        return MCIntegratedEvaluate(sim_element);
    precomputeParticleFormfactors(sim_element);
    return evaluateForList(sim_element);
}

double IInterferenceFunctionStrategy::evaluatePol(const SimulationElement& sim_element) const
{
    if (m_options.isIntegrate()) // TODO: consider testing solid angle as in scalar case
        return MCIntegratedEvaluatePol(sim_element);
    precomputeParticleFormfactorsPol(sim_element);
    return evaluateForMatrixList(sim_element);
}

//! Precomputes scalar form factors.
void IInterferenceFunctionStrategy::precomputeParticleFormfactors(
        const SimulationElement& sim_element) const
{
    m_ff.clear();

    double wavelength = sim_element.getWavelength();
    double wavevector_scattering_factor = M_PI/wavelength/wavelength;
    WavevectorInfo wavevectors(sim_element.getKI(), sim_element.getMeanKF(), wavelength);

    const std::unique_ptr<const ILayerRTCoefficients> P_in_coeffs(
        mP_specular_info->getInCoefficients(sim_element));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(sim_element));
    for (auto wff: m_weighted_ffs) {
        wff->mp_ff->setSpecularInfo(P_in_coeffs.get(), P_out_coeffs.get());
        complex_t ff_mat = wff->mp_ff->evaluate(wavevectors);
        m_ff.push_back(wavevector_scattering_factor*ff_mat);
    }
}

//! Precomputes matrix form factors.
void IInterferenceFunctionStrategy::precomputeParticleFormfactorsPol(
        const SimulationElement& sim_element) const
{
    m_ff_pol.clear();

    double wavelength = sim_element.getWavelength();
    double wavevector_scattering_factor = M_PI/wavelength/wavelength;
    WavevectorInfo wavevectors(sim_element.getKI(), sim_element.getMeanKF(), wavelength);

    const std::unique_ptr<const ILayerRTCoefficients> P_in_coeffs(
        mP_specular_info->getInCoefficients(sim_element));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(sim_element));
    for (auto wff: m_weighted_ffs) {
        wff->mp_ff->setSpecularInfo(P_in_coeffs.get(), P_out_coeffs.get());
        Eigen::Matrix2cd ff_mat = wff->mp_ff->evaluatePol(wavevectors);
        m_ff_pol.push_back(wavevector_scattering_factor*ff_mat);
    }
}

double IInterferenceFunctionStrategy::MCIntegratedEvaluate(
    const SimulationElement& sim_element) const
{
    double min_array[] = {0.0, 0.0};
    double max_array[] = {1.0, 1.0};
    return mP_integrator->integrate(
        min_array, max_array, (void*)&sim_element, m_options.getMcPoints());
}

double IInterferenceFunctionStrategy::MCIntegratedEvaluatePol(
        const SimulationElement& sim_element) const
{
    double min_array[] = {0.0, 0.0};
    double max_array[] = {1.0, 1.0};
    return mP_integrator_pol->integrate(
        min_array, max_array, (void*)&sim_element, m_options.getMcPoints());
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_angles(
    double* fractions, size_t, void* params) const
{
    double par0 = fractions[0];
    double par1 = fractions[1];

    SimulationElement* pars = static_cast<SimulationElement*>(params);

    SimulationElement sim_element(*pars, par0, par1);
    precomputeParticleFormfactors(sim_element);
    return pars->getIntegrationFactor(par0, par1) * evaluateForList(sim_element);
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_angles_pol(
    double* fractions, size_t, void* params) const
{
    double par0 = fractions[0];
    double par1 = fractions[1];

    SimulationElement* pars = static_cast<SimulationElement*>(params);

    SimulationElement sim_element(*pars, par0, par1);
    precomputeParticleFormfactorsPol(sim_element);
    return pars->getIntegrationFactor(par0, par1) * evaluateForMatrixList(sim_element);
}
