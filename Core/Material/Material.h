// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/Material.h
//! @brief     Defines and implements class Material.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Complex.h"
#include "Vectors3D.h"
#include "EigenCore.h"
#include "BaseMaterialImpl.h"
#include <vector>
#include <memory>

class Transform3D;
class WavevectorInfo;

//! A wrapper for homogeneous and wavelength-independent materials
//! @ingroup materials

class BA_CORE_API_ Material
{
public:
    //! Material copy-constructor
    Material(const Material& material);

    //! Material move-constructor
    Material(Material&& material) = default;

#ifndef SWIG
    //! Creates material with particular material implementation
    Material(std::unique_ptr<BaseMaterialImpl> material_impl);
#endif //SWIG

    //! Constructs a material with inverted magnetization
    Material inverted() const;

    complex_t refractiveIndex(double wavelength) const;
    complex_t refractiveIndex2(double wavelength) const;

    //! Indicates whether the interaction with the material is scalar.
    //! This means that different polarization states will be diffracted equally
    bool isScalarMaterial() const;

    bool isMagneticMaterial() const;

    //! Returns the name of material
    std::string getName() const;

    //! Returns hash code of underlying material implementation
    size_t dataType() const;

    //! Get the magnetization (in A/m)
    kvector_t magnetization() const;

    //! Returns underlying material data
    complex_t materialData() const;

    bool isEmpty() {return !m_material_impl;}

    //! Returns \pi/(wl*wl) - sld, with wl being the wavelength
    complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const;

#ifndef SWIG
    //! Returns \pi/(wl*wl) - sld matrix with magnetization corrections. wl denotes the wavelength
    Eigen::Matrix2cd polarizedSubtrSLD(const WavevectorInfo& wavevectors) const;
#endif

    Material transformedMaterial(const Transform3D& transform) const;

    friend BA_CORE_API_ std::ostream& operator<<(
            std::ostream& ostr, const Material& mat);

private:
    std::unique_ptr<BaseMaterialImpl> m_material_impl;
};

//! Comparison operator for material wrapper
BA_CORE_API_ bool operator==(const Material& left, const Material& right);

#endif /* MATERIAL_H_ */
