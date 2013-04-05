// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "PythonCoreList.h"
#include "MultiLayer.pypp.h"

namespace bp = boost::python;

struct MultiLayer_wrapper : MultiLayer, bp::wrapper< MultiLayer > {

    MultiLayer_wrapper( )
    : MultiLayer( )
      , bp::wrapper< MultiLayer >(){
        // null constructor
    
    }

    virtual ::MultiLayer * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->MultiLayer::clone(  );
        }
    }
    
    ::MultiLayer * default_clone(  ) const  {
        return MultiLayer::clone( );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else{
            return this->IParameterized::areParametersChanged(  );
        }
    }
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else{
            this->IParameterized::clearParameterPool(  );
        }
    }
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else{
            return this->IParameterized::createParameterTree(  );
        }
    }
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual ::ICompositeSample * getCompositeSample(  ) {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample * default_getCompositeSample(  ) {
        return ICompositeSample::getCompositeSample( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ICompositeSample::getCompositeSample( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else{
            this->IParameterized::printParameters(  );
        }
    }
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else{
            return this->IParameterized::setParameterValue( name, value );
        }
    }
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else{
            this->IParameterized::setParametersAreChanged(  );
        }
    }
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

    virtual ::size_t size(  ) const  {
        if( bp::override func_size = this->get_override( "size" ) )
            return func_size(  );
        else{
            return this->ICompositeSample::size(  );
        }
    }
    
    ::size_t default_size(  ) const  {
        return ICompositeSample::size( );
    }

};

void register_MultiLayer_class(){

    { //::MultiLayer
        typedef bp::class_< MultiLayer_wrapper, bp::bases< ICompositeSample >, boost::noncopyable > MultiLayer_exposer_t;
        MultiLayer_exposer_t MultiLayer_exposer = MultiLayer_exposer_t( "MultiLayer", bp::init< >() );
        bp::scope MultiLayer_scope( MultiLayer_exposer );
        { //::MultiLayer::addLayer
        
            typedef void ( ::MultiLayer::*addLayer_function_type )( ::Layer const & ) ;
            
            MultiLayer_exposer.def( 
                "addLayer"
                , addLayer_function_type( &::MultiLayer::addLayer )
                , ( bp::arg("p_child") ) );
        
        }
        { //::MultiLayer::addLayerWithTopRoughness
        
            typedef void ( ::MultiLayer::*addLayerWithTopRoughness_function_type )( ::Layer const &,::LayerRoughness const & ) ;
            
            MultiLayer_exposer.def( 
                "addLayerWithTopRoughness"
                , addLayerWithTopRoughness_function_type( &::MultiLayer::addLayerWithTopRoughness )
                , ( bp::arg("layer"), bp::arg("roughness") ) );
        
        }
        { //::MultiLayer::clear
        
            typedef void ( ::MultiLayer::*clear_function_type )(  ) ;
            
            MultiLayer_exposer.def( 
                "clear"
                , clear_function_type( &::MultiLayer::clear ) );
        
        }
        { //::MultiLayer::clone
        
            typedef ::MultiLayer * ( ::MultiLayer::*clone_function_type )(  ) const;
            typedef ::MultiLayer * ( MultiLayer_wrapper::*default_clone_function_type )(  ) const;
            
            MultiLayer_exposer.def( 
                "clone"
                , clone_function_type(&::MultiLayer::clone)
                , default_clone_function_type(&MultiLayer_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::MultiLayer::getCrossCorrLength
        
            typedef double ( ::MultiLayer::*getCrossCorrLength_function_type )(  ) const;
            
            MultiLayer_exposer.def( 
                "getCrossCorrLength"
                , getCrossCorrLength_function_type( &::MultiLayer::getCrossCorrLength ) );
        
        }
        { //::MultiLayer::getCrossCorrSpectralFun
        
            typedef double ( ::MultiLayer::*getCrossCorrSpectralFun_function_type )( ::kvector_t const &,::size_t,::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getCrossCorrSpectralFun"
                , getCrossCorrSpectralFun_function_type( &::MultiLayer::getCrossCorrSpectralFun )
                , ( bp::arg("kvec"), bp::arg("j"), bp::arg("k") ) );
        
        }
        { //::MultiLayer::getLayer
        
            typedef ::Layer const * ( ::MultiLayer::*getLayer_function_type )( ::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getLayer"
                , getLayer_function_type( &::MultiLayer::getLayer )
                , ( bp::arg("i_layer") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::MultiLayer::getLayerBottomInterface
        
            typedef ::LayerInterface const * ( ::MultiLayer::*getLayerBottomInterface_function_type )( ::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getLayerBottomInterface"
                , getLayerBottomInterface_function_type( &::MultiLayer::getLayerBottomInterface )
                , ( bp::arg("i_layer") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::MultiLayer::getLayerBottomZ
        
            typedef double ( ::MultiLayer::*getLayerBottomZ_function_type )( ::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getLayerBottomZ"
                , getLayerBottomZ_function_type( &::MultiLayer::getLayerBottomZ )
                , ( bp::arg("i_layer") ) );
        
        }
        { //::MultiLayer::getLayerInterface
        
            typedef ::LayerInterface const * ( ::MultiLayer::*getLayerInterface_function_type )( ::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getLayerInterface"
                , getLayerInterface_function_type( &::MultiLayer::getLayerInterface )
                , ( bp::arg("i_interface") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::MultiLayer::getLayerThickness
        
            typedef double ( ::MultiLayer::*getLayerThickness_function_type )( ::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getLayerThickness"
                , getLayerThickness_function_type( &::MultiLayer::getLayerThickness )
                , ( bp::arg("i_layer") ) );
        
        }
        { //::MultiLayer::getLayerTopInterface
        
            typedef ::LayerInterface const * ( ::MultiLayer::*getLayerTopInterface_function_type )( ::size_t ) const;
            
            MultiLayer_exposer.def( 
                "getLayerTopInterface"
                , getLayerTopInterface_function_type( &::MultiLayer::getLayerTopInterface )
                , ( bp::arg("i_layer") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::MultiLayer::getNumberOfInterfaces
        
            typedef ::size_t ( ::MultiLayer::*getNumberOfInterfaces_function_type )(  ) const;
            
            MultiLayer_exposer.def( 
                "getNumberOfInterfaces"
                , getNumberOfInterfaces_function_type( &::MultiLayer::getNumberOfInterfaces ) );
        
        }
        { //::MultiLayer::getNumberOfLayers
        
            typedef ::size_t ( ::MultiLayer::*getNumberOfLayers_function_type )(  ) const;
            
            MultiLayer_exposer.def( 
                "getNumberOfLayers"
                , getNumberOfLayers_function_type( &::MultiLayer::getNumberOfLayers ) );
        
        }
        { //::MultiLayer::setCrossCorrLength
        
            typedef void ( ::MultiLayer::*setCrossCorrLength_function_type )( double ) ;
            
            MultiLayer_exposer.def( 
                "setCrossCorrLength"
                , setCrossCorrLength_function_type( &::MultiLayer::setCrossCorrLength )
                , ( bp::arg("crossCorrLength") ) );
        
        }
        { //::MultiLayer::setLayerThickness
        
            typedef void ( ::MultiLayer::*setLayerThickness_function_type )( ::size_t,double ) ;
            
            MultiLayer_exposer.def( 
                "setLayerThickness"
                , setLayerThickness_function_type( &::MultiLayer::setLayerThickness )
                , ( bp::arg("i_layer"), bp::arg("thickness") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( MultiLayer_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            MultiLayer_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&MultiLayer_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type )(  ) ;
            typedef void ( MultiLayer_wrapper::*default_clearParameterPool_function_type )(  ) ;
            
            MultiLayer_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&MultiLayer_wrapper::default_clearParameterPool) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( MultiLayer_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            MultiLayer_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&MultiLayer_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ICompositeSample::getCompositeSample
        
            typedef ::ICompositeSample * ( ::ICompositeSample::*getCompositeSample_function_type )(  ) ;
            typedef ::ICompositeSample * ( MultiLayer_wrapper::*default_getCompositeSample_function_type )(  ) ;
            
            MultiLayer_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ICompositeSample::getCompositeSample)
                , default_getCompositeSample_function_type(&MultiLayer_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ICompositeSample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ICompositeSample::*getCompositeSample_function_type )(  ) const;
            typedef ::ICompositeSample const * ( MultiLayer_wrapper::*default_getCompositeSample_function_type )(  ) const;
            
            MultiLayer_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ICompositeSample::getCompositeSample)
                , default_getCompositeSample_function_type(&MultiLayer_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( MultiLayer_wrapper::*default_printParameters_function_type )(  ) const;
            
            MultiLayer_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&MultiLayer_wrapper::default_printParameters) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type )( ::std::string const &,double ) ;
            typedef bool ( MultiLayer_wrapper::*default_setParameterValue_function_type )( ::std::string const &,double ) ;
            
            MultiLayer_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&MultiLayer_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( MultiLayer_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            MultiLayer_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&MultiLayer_wrapper::default_setParametersAreChanged) );
        
        }
        { //::ICompositeSample::size
        
            typedef ::size_t ( ::ICompositeSample::*size_function_type )(  ) const;
            typedef ::size_t ( MultiLayer_wrapper::*default_size_function_type )(  ) const;
            
            MultiLayer_exposer.def( 
                "size"
                , size_function_type(&::ICompositeSample::size)
                , default_size_function_type(&MultiLayer_wrapper::default_size) );
        
        }
    }

}
