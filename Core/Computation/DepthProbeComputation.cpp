// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputation.cpp
//! @brief     Implements class SpecularComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DepthProbeComputation.h"
#include "DepthProbeElement.h"
#include "IComputationUtils.h"
#include "MatrixFresnelMap.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"
#include "ScalarFresnelMap.h"

static_assert(std::is_copy_constructible<DepthProbeComputation>::value == false,
              "DepthProbeComputation should not be copy constructible");
static_assert(std::is_copy_assignable<DepthProbeComputation>::value == false,
              "DepthProbeComputation should not be copy assignable");

DepthProbeComputation::DepthProbeComputation(const MultiLayer& multilayer,
                                             const SimulationOptions& options,
                                             ProgressHandler& progress,
                                             DepthProbeElementIter begin_it,
                                             DepthProbeElementIter end_it)
    : IComputation(options, progress, multilayer)
    , m_begin_it(begin_it), m_end_it(end_it)
    , mP_fresnel_map(IComputationUtils::CreateFresnelMap(multilayer, options, false))
    , m_computation_term(mP_multi_layer.get(), mP_fresnel_map.get())
{}

DepthProbeComputation::~DepthProbeComputation() = default;

void DepthProbeComputation::runProtected()
{
    if (!mp_progress->alive() || mP_multi_layer->requiresMatrixRTCoefficients())
        return;
    std::for_each(m_begin_it, m_end_it, m_computation_term);
}
