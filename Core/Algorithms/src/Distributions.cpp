// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/Distributions.cpp
//! @brief     Implements classes representing distributions.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Distributions.h"

#include "MathFunctions.h"
#include "Exceptions.h"

#include <math.h>

std::vector<ParameterSample> IDistribution1D::generateSamples(
		size_t nbr_samples, double sigma_factor) const {
	if (nbr_samples == 0) {
		throw OutOfBoundsException("IDistribution1D::generateSamples: number "
				"of generated samples must be bigger than zero");
	}
	std::vector<double> sample_values = generateValueList(
			nbr_samples, sigma_factor);
	std::vector<ParameterSample> result;
	result.resize(nbr_samples);
	double norm_factor = 0.0;
	for (size_t i=0; i<nbr_samples; ++i) {
		double pdf = probabilityDensity(sample_values[i]);
		result[i].value = sample_values[i];
		result[i].weight = pdf;
		norm_factor += pdf;
	}
	if (norm_factor <= 0.0) {
		throw RuntimeErrorException("IDistribution1D::generateSamples: "
				"total probability must be bigger than zero");;
	}
	for (size_t i=0; i<nbr_samples; ++i) {
		result[i].weight /= norm_factor;
	}
	return result;
}

//! Interface
void IDistribution1D::SignalBadInitialization(
	std::string distribution_name) const
{
	throw new ClassInitializationException(distribution_name +
			": not correctly initialized");
}

//! DistributionGate
DistributionGate::DistributionGate(double mean, double hwhm)
: m_mean(mean)
, m_hwhm(hwhm)
{
	checkInitialization();
}

double DistributionGate::probabilityDensity(double x) const
{
	if (std::abs(x - m_mean) > m_hwhm) return 0.0;
	return 1.0/(2.0*m_hwhm);
}

std::vector<double> DistributionGate::generateValueList(size_t nbr_samples,
		double sigma_factor) const
{
	std::vector<double> result;
	if (nbr_samples < 2) {
		result.push_back(m_mean);
	}
	else {
		result.resize(nbr_samples);
		double xmin = m_mean - m_hwhm;
		double xmax = m_mean + m_hwhm;
		for (int i=0; i<nbr_samples; ++i) {
			result[i] = xmin + i*(xmax-xmin)/(nbr_samples-1.0);
		}
	}
	return result;
}

bool DistributionGate::checkInitialization() const
{
	bool result = true;
	if (m_hwhm <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionGate");
	return result;
}

//! DistributionLorenz
DistributionLorentz::DistributionLorentz(double mean, double hwhm)
: m_mean(mean)
, m_hwhm(hwhm)
{
	checkInitialization();
}

double DistributionLorentz::probabilityDensity(double x) const
{
	return m_hwhm/(m_hwhm*m_hwhm + (x-m_mean)*(x-m_mean))/M_PI;
}

std::vector<double> DistributionLorentz::generateValueList(size_t nbr_samples,
		double sigma_factor) const
{
	std::vector<double> result;
	if (nbr_samples < 2) {
		result.push_back(m_mean);
	}
	else {
		if (sigma_factor <= 0.0) sigma_factor = 2.0;
		result.resize(nbr_samples);
		double xmin = m_mean - sigma_factor*m_hwhm;
		double xmax = m_mean + sigma_factor*m_hwhm;
		for (int i=0; i<nbr_samples; ++i) {
			result[i] = xmin + i*(xmax-xmin)/(nbr_samples-1.0);
		}
	}
	return result;
}

bool DistributionLorentz::checkInitialization() const
{
	bool result = true;
	if (m_hwhm <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionLorentz");
	return result;
}

//! DistributionGaussian
DistributionGaussian::DistributionGaussian(double mean, double std_dev)
: m_mean(mean)
, m_std_dev(std_dev)
{
	checkInitialization();
}

double DistributionGaussian::probabilityDensity(double x) const
{
	double exponential = std::exp(-(x-m_mean)*(x-m_mean)
			/(2.0*m_std_dev*m_std_dev));
	return exponential/m_std_dev/std::sqrt(2.0*M_PI);
}

std::vector<double> DistributionGaussian::generateValueList(size_t nbr_samples,
		double sigma_factor) const
{
	std::vector<double> result;
	if (nbr_samples < 2) {
		result.push_back(m_mean);
	}
	else {
		if (sigma_factor <= 0.0) sigma_factor = 2.0;
		result.resize(nbr_samples);
		double xmin = m_mean - sigma_factor*m_std_dev;
		double xmax = m_mean + sigma_factor*m_std_dev;
		for (int i=0; i<nbr_samples; ++i) {
			result[i] = xmin + i*(xmax-xmin)/(nbr_samples-1.0);
		}
	}
	return result;
}

bool DistributionGaussian::checkInitialization() const
{
	bool result = true;
	if (m_std_dev <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionGaussian");
	return result;
}

//! DistributionLogNormal
DistributionLogNormal::DistributionLogNormal(double mean_log, double sigma)
: m_mean_log(mean_log)
, m_sigma(sigma)
{
	checkInitialization();
}

double DistributionLogNormal::probabilityDensity(double x) const
{
	double t = (std::log(x) - m_mean_log)/m_sigma;
	return std::exp(-t*t/2.0)/(x*m_sigma*std::sqrt(2.0*M_PI));
}

double DistributionLogNormal::getMean() const
{
	double exponent = m_mean_log + m_sigma*m_sigma/2.0;
	return std::exp(exponent);
}

std::vector<double> DistributionLogNormal::generateValueList(size_t nbr_samples,
		double sigma_factor) const
{
	std::vector<double> result;
	if (nbr_samples < 2) {
		result.push_back(std::exp(m_mean_log));
	}
	else {
		if (sigma_factor <= 0.0) sigma_factor = 2.0;
		result.resize(nbr_samples);
		double xmin = std::exp(m_mean_log - sigma_factor*m_sigma);
		double xmax = std::exp(m_mean_log + sigma_factor*m_sigma);
		for (int i=0; i<nbr_samples; ++i) {
			result[i] = xmin + i*(xmax-xmin)/(nbr_samples-1.0);
		}
	}
	return result;
}

bool DistributionLogNormal::checkInitialization() const
{
	bool result = true;
	if (m_sigma <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionLogNormal");
	return result;
}

//! DistributionLogNormal
DistributionCosine::DistributionCosine(double mean, double sigma)
: m_mean(mean)
, m_sigma(sigma)
{
	checkInitialization();
}

double DistributionCosine::probabilityDensity(double x) const
{
	return (1.0 + std::cos((x-m_mean)/m_sigma))/(m_sigma*2.0*M_PI);
}

std::vector<double> DistributionCosine::generateValueList(size_t nbr_samples,
		double sigma_factor) const
{
	std::vector<double> result;
	if (nbr_samples < 2) {
		result.push_back(m_mean);
	}
	else {
		if (sigma_factor <= 0.0 || sigma_factor > 2.0) sigma_factor = 2.0;
		result.resize(nbr_samples);
		double xmin = m_mean - sigma_factor*m_sigma*M_PI/2.0;
		double xmax = m_mean + sigma_factor*m_sigma*M_PI/2.0;
		for (int i=0; i<nbr_samples; ++i) {
			result[i] = xmin + i*(xmax-xmin)/(nbr_samples-1.0);
		}
	}
	return result;
}

bool DistributionCosine::checkInitialization() const
{
	bool result = true;
	if (m_sigma <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionCosine");
	return result;
}
