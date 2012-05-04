#ifndef MULTILAYER_H
#define MULTILAYER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MultiLayer.h
//! @brief  Definition of MultiLayer class
//! @author James Bond <j.bond@fz-juelich.de>, Chuck Norris <c.norris@fz-juelich.de>
//! @date   01.04.2012

#include <vector>

#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"


//- -------------------------------------------------------------------
/// @class MultiLayer
/// @brief Stack of layers one on top of the other
///
/// Example of system of 4 layers (3 interfaces):
///
///  ambience    layer #0        z=getLayerBottomZ(0)=0.0
///  ---------   interface #0
///  Fe, 20A     layer #1        z=getLayerBottomZ(1)=-20.0
///  ---------   interface #1
///  Cr, 40A     layer #2        z=getLayerBottomZ(2)=-60.0
///  ---------   interface #2
///  substrate   layer #3        z=getLayerBottomZ(3)=-60.0
///
//- -------------------------------------------------------------------
class MultiLayer : public ISample
{
public:
    MultiLayer();
    ~MultiLayer();

    /// return number of layers in multilayer
    inline size_t getNumberOfLayers() const { return m_layers.size(); }

    /// add object to multilayer, overrides from ISample
    void addLayer(const Layer &p_child);

    /// add layer with top roughness
    void addLayerWithTopRoughness(const Layer &layer, const LayerRoughness &roughness);

    /// return layer with given index
    const Layer *getLayer(size_t i_layer) const { return m_layers[ check_layer_index(i_layer) ]; }

    /// return z-coordinate of the layer's bottom
    double getLayerBottomZ(size_t i_layer) const { return m_layers_z[ check_layer_index(i_layer) ]; }

    /// return top interface of layer
    const LayerInterface *getLayerTopInterface(size_t i_layer) const;

    /// return bottom interface of layer
    const LayerInterface *getLayerBottomInterface(size_t i_layer) const;

    /// destruct allocated objects
    void clear();

    /// return clone of multilayer with clones of all layers and recreated interfaces between layers
    virtual MultiLayer *clone() const;

    /// print structure of multilayer
    void print();

private:
    /// hiding copy constructor & assignment operator
    MultiLayer(const MultiLayer &);
    MultiLayer &operator=(const MultiLayer &);

    /// check index of layer w.r.t. vector length
    inline size_t check_layer_index(size_t i_layer) const { return i_layer < m_layers.size() ? i_layer : throw OutOfBoundsException("Layer index is out of bounds"); }

    /// check index of interface w.r.t. vector length
    inline size_t check_interface_index(size_t i_interface) const { return i_interface < m_interfaces.size() ? i_interface : throw OutOfBoundsException("Interface index is out of bounds"); }

    std::vector<Layer *> m_layers;                ///< stack of layers [nlayers]
    std::vector<double > m_layers_z;              ///< coordinate of layer's bottoms [nlayers]
    std::vector<LayerInterface *> m_interfaces;   ///< stack of layer interfaces [nlayers-1]
};

#endif // MULTILAYER_H

