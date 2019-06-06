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

#include "SpecularComputation.h"
#include "IComputationUtils.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"
#include "SpecularSimulationElement.h"
#include <complex>
#define TINY 1e-30

inline void matmul(std::complex<double> a[2][2], std::complex<double> b[2][2],
                   std::complex<double> c[2][2])
{
    c[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    c[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
    c[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    c[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
}


static_assert(std::is_copy_constructible<SpecularComputation>::value == false,
              "SpecularComputation should not be copy constructible");
static_assert(std::is_copy_assignable<SpecularComputation>::value == false,
              "SpecularComputation should not be copy assignable");

SpecularComputation::SpecularComputation(const MultiLayer& multilayer,
                                         const SimulationOptions& options,
                                         ProgressHandler& progress, SpecularElementIter begin_it,
                                         SpecularElementIter end_it)
    : IComputation(options, progress, multilayer)
    , m_begin_it(begin_it), m_end_it(end_it)
{}

SpecularComputation::~SpecularComputation() = default;

void SpecularComputation::runProtected()
{
    if (!mp_progress->alive() || mP_multi_layer->requiresMatrixRTCoefficients())
        return;

    m_computation_term.setProgressHandler(mp_progress);
    const std::unique_ptr<MultiLayer> avr_sample =
                    IComputationUtils::CreateAveragedMultilayer(*mP_multi_layer, m_sim_options);
    double doubleVal(3.14159265);
    std::vector<complex_t> slds;
    std::vector<double_t> thicknesses;
    std::vector<double_t> roughnesses;
    for(size_t i = 0; i < avr_sample->numberOfLayers(); i++){
        double th = avr_sample->layerThickness(i);
        complex_t sl = avr_sample->layerMaterial(i).materialData();
        double rg = 0.0;

        slds.push_back(sl);
        thicknesses.push_back(th);
        roughnesses.push_back(rg);
    }

    std::vector<double_t> qvals;
    for (auto it = m_begin_it; it != m_end_it; ++it){
        qvals.push_back(it->kz());
    }
    auto npoints = qvals.size();
    std::vector<double> reflectometry(npoints);

    {
        {
            using namespace std;

            double scale, bkg;
            double num = 0, den = 0, answer = 0;

            complex<double> super;
            complex<double> sub;
            complex<double> oneC = complex<double>(1., 0.);
            complex<double> MRtotal[2][2];
            complex<double> MI[2][2];
            complex<double> temp2[2][2];
            complex<double> qq2;
            complex<double>* SLD = nullptr;
            complex<double>* thickness = nullptr;
            double* rough_sqr = nullptr;

            size_t nlayers = size_t(thicknesses.size());

            scale = 1.0;
            bkg = 0.0;
            sub = complex<double>(2.07, 0.0 + TINY);
            super = complex<double>(0.00, 0.0);

            try {
                SLD = new complex<double>[nlayers + 2];
                thickness = new complex<double>[nlayers];
                rough_sqr = new double[nlayers + 1];
            } catch (...) {
                goto done;
            }
            // fill out all the SLD's for all the layers
            for (int ii = 1; ii < int(nlayers + 1); ii += 1) {
                SLD[ii] = 4e-6 * M_PI * (complex<double>(slds[size_t(ii - 1)]) + TINY) - super;
                thickness[ii - 1] = complex<double>(0, thicknesses[size_t(ii - 1)]);
                rough_sqr[ii - 1] = -2 * roughnesses[size_t(ii - 1)] * roughnesses[size_t(ii - 1)];
            }

            SLD[0] = complex<double>(0, 0);
            SLD[nlayers + 1] = 4e-6 * M_PI * (sub - super);
            rough_sqr[nlayers] = 0.0;

            for (size_t j = 0; j < npoints; j++) {
                complex<double> beta, rj;
                complex<double> kn, kn_next;

                qq2 = complex<double>(qvals[j] * qvals[j] / 4, 0);

                // now calculate reflectivities and wavevectors
                kn = std::sqrt(qq2);
                for (int ii = 0; ii < int(nlayers + 1); ii++) {
                    // wavevector in the layer
                    kn_next = std::sqrt(qq2 - SLD[ii + 1]);

                    // reflectance of the interface
                    rj = (kn - kn_next) / (kn + kn_next) * std::exp(kn * kn_next * rough_sqr[ii]);

                    if (!ii) {
                        // characteristic matrix for first interface
                        MRtotal[0][0] = oneC;
                        MRtotal[0][1] = rj;
                        MRtotal[1][1] = oneC;
                        MRtotal[1][0] = rj;
                    } else {
                        // work out the beta for the layer
                        beta = std::exp(kn * thickness[ii - 1]);
                        // this is the characteristic matrix of a layer
                        MI[0][0] = beta;
                        MI[0][1] = rj * beta;
                        MI[1][1] = oneC / beta;
                        MI[1][0] = rj * MI[1][1];

                        // multiply MRtotal, MI to get the updated total matrix.
                        memcpy(temp2, MRtotal, sizeof(MRtotal));
                        matmul(temp2, MI, MRtotal);
                    }
                    kn = kn_next;
                }

                num = std::norm(MRtotal[1][0]);
                den = std::norm(MRtotal[0][0]);
                answer = (num / den);
                answer = (answer * scale) + bkg;

                reflectometry[j] = answer;
            }

done:
            if (SLD)
                delete[] SLD;
            if (thickness)
                delete[] thickness;
            if (rough_sqr)
                delete[] rough_sqr;

            // return reflectometry;
        }

    }


    size_t count = 0;
    for (auto it = m_begin_it; it != m_end_it; ++it){
        it->setIntensity(reflectometry[count++]);
    }
}
