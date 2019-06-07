// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/Material.cpp
//! @brief     Implements and implements class Material.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Material.h"
#include "BaseMaterialImpl.h"
#include "WavevectorInfo.h"
#include "Transform3D.h"
#include "Exceptions.h"
#include "Units.h"
#include <typeinfo>

Material::Material(const Material& material)
{
    if (material.isEmpty())
        throw Exceptions::NullPointerException("Material: Error! Attempt to initialize material with nullptr.");
    m_material_impl.reset(material.m_material_impl->clone());
}

Material::Material(std::unique_ptr<BaseMaterialImpl> material_impl)
    : m_material_impl(std::move(material_impl))
{}

Material& Material::operator=(const Material& other)
{
    if (other.isEmpty())
        throw Exceptions::NullPointerException("Material: Error! Attempt to assign nullptr to material.");
    m_material_impl.reset(other.m_material_impl->clone());
    return *this;
}

Material Material::inverted() const
{
    std::unique_ptr<BaseMaterialImpl> material_impl(m_material_impl->inverted());
    return Material(std::move(material_impl));
}

complex_t Material::refractiveIndex(double wavelength) const
{
    return m_material_impl->refractiveIndex(wavelength);
}

complex_t Material::refractiveIndex2(double wavelength) const
{
    return m_material_impl->refractiveIndex2(wavelength);
}

bool Material::isScalarMaterial() const
{
    return m_material_impl->isScalarMaterial();
}

bool Material::isMagneticMaterial() const {
    return m_material_impl->isMagneticMaterial();
}

std::string Material::getName() const
{
    return m_material_impl->getName();
}

MATERIAL_TYPES Material::typeID() const
{
    return m_material_impl->typeID();
}

kvector_t Material::magnetization() const
{
    return m_material_impl->magnetization();
}

complex_t Material::materialData() const
{
    return m_material_impl->materialData();
}

bool Material::isDefaultMaterial() const
{
    return materialData() == complex_t() && isScalarMaterial();
}

complex_t Material::scalarSubtrSLD(const WavevectorInfo& wavevectors) const
{
    return m_material_impl->scalarSubtrSLD(wavevectors);
}

complex_t Material::SLD(const double wavelength) const
{
    //getSLD = complex_t(sld_real, -sld_imag);
    const double square_angstroms = Units::angstrom * Units::angstrom;
    double prefactor = wavelength * wavelength / M_PI;
    complex_t sld = ( 1.0 - refractiveIndex2(wavelength) ) / prefactor;
    double sld_real = sld.real();
    double sld_imag = sld.imag();
    return complex_t(sld_real * square_angstroms, sld_imag * square_angstroms);
}

Eigen::Matrix2cd Material::polarizedSubtrSLD(const WavevectorInfo& wavevectors) const
{
    return m_material_impl->polarizedSubtrSLD(wavevectors);
}

Material Material::transformedMaterial(const Transform3D& transform) const
{
    std::unique_ptr<BaseMaterialImpl> material_impl(m_material_impl->transformedMaterial(transform));
    return Material(std::move(material_impl));
}

std::ostream& operator<<(std::ostream& ostr, const Material& m)
{
    m.m_material_impl->print(ostr);
    return ostr;
}

bool operator==(const Material& left, const Material& right)
{
    if (left.getName() != right.getName()) return false;
    if (left.magnetization() != right.magnetization()) return false;
    if (left.materialData() != right.materialData()) return false;
    if (left.typeID() != right.typeID()) return false;
    return true;
}

bool operator!=(const Material& left, const Material& right)
{
    return !(left == right);
}

