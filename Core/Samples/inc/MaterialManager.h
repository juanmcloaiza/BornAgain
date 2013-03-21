// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/MaterialManager.h
//! @brief     Defines class MaterialManager.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include "Exceptions.h"
#include "ISingleton.h"
#include "HomogeneousMaterial.h"

//! Manager of materials used in simulation.
//!
//! It is a singleton which provides common and unique interface for
//! material creation and access.

class MaterialManager: public ISingleton<MaterialManager>
{
public:
    virtual ~MaterialManager() { clear(); }

    //! definition of materials container
    typedef std::map<std::string, IMaterial *> materials_t;

    //! return material from container
    static const IMaterial *getMaterial(const std::string &name)
    { return instance().this_getMaterial(name); }

    //! add material to the container
    static const IMaterial *getHomogeneousMaterial(const std::string &name, const complex_t &refractive_index)
    { return instance().this_getHomogeneousMaterial(name, refractive_index); }

    //! add material to the container
    static const IMaterial *getHomogeneousMaterial(const std::string &name, double refractive_index_real, double refractive_index_imag)
    { return instance().this_getHomogeneousMaterial(name, refractive_index_real, refractive_index_imag); }

    //! print material class
    friend std::ostream &operator<<(std::ostream &ostr, const MaterialManager &m) { m.print(ostr); return ostr; }

protected:
    MaterialManager(){}
    friend class ISingleton<MaterialManager >;

    //! clean collection of material
    void clear();


    //! print material class
    virtual void print(std::ostream &ostr) const;

    materials_t m_materials; //! container with defined materials
private:
    const IMaterial *this_getMaterial(const std::string &name);
    const IMaterial *this_getHomogeneousMaterial(const std::string &name, const complex_t &refractive_index);
    const IMaterial *this_getHomogeneousMaterial(const std::string &name, double refractive_index_real, double refractive_index_imag);

};

#endif // MATERIALMANAGER_H
