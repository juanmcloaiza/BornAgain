// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "__call_policies.pypp.hpp"
#include "__convenience.pypp.hpp"
#include "PythonCoreList.h"
#include "ILayout.pypp.h"

namespace bp = boost::python;

struct ILayout_wrapper : ILayout, bp::wrapper< ILayout > {

    ILayout_wrapper( )
    : ILayout( )
      , bp::wrapper< ILayout >(){
        // null constructor
    
    }

    virtual void accept( ::ISampleVisitor * visitor ) const {
        bp::override func_accept = this->get_override( "accept" );
        func_accept( boost::python::ptr(visitor) );
    }

    virtual ::ILayout * clone(  ) const {
        bp::override func_clone = this->get_override( "clone" );
        return func_clone(  );
    }

    virtual ::ILayout * cloneInvertB(  ) const {
        bp::override func_cloneInvertB = this->get_override( "cloneInvertB" );
        return func_cloneInvertB(  );
    }

    virtual double getAbundanceFractionOfParticle( ::std::size_t index ) const {
        bp::override func_getAbundanceFractionOfParticle = this->get_override( "getAbundanceFractionOfParticle" );
        return func_getAbundanceFractionOfParticle( index );
    }

    virtual ::SafePointerVector< IInterferenceFunction > getInterferenceFunctions(  ) const {
        bp::override func_getInterferenceFunctions = this->get_override( "getInterferenceFunctions" );
        return func_getInterferenceFunctions(  );
    }

    virtual ::std::size_t getNumberOfInterferenceFunctions(  ) const  {
        if( bp::override func_getNumberOfInterferenceFunctions = this->get_override( "getNumberOfInterferenceFunctions" ) )
            return func_getNumberOfInterferenceFunctions(  );
        else
            return this->ILayout::getNumberOfInterferenceFunctions(  );
    }
    
    
    ::std::size_t default_getNumberOfInterferenceFunctions(  ) const  {
        return ILayout::getNumberOfInterferenceFunctions( );
    }

    virtual ::std::size_t getNumberOfParticles(  ) const {
        bp::override func_getNumberOfParticles = this->get_override( "getNumberOfParticles" );
        return func_getNumberOfParticles(  );
    }

    virtual ::ParticleInfo const * getParticleInfo( ::std::size_t index ) const {
        bp::override func_getParticleInfo = this->get_override( "getParticleInfo" );
        return func_getParticleInfo( index );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else
            return this->IParameterized::areParametersChanged(  );
    }
    
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else
            this->IParameterized::clearParameterPool(  );
    }
    
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
    }

    virtual bool containsMagneticMaterial(  ) const  {
        if( bp::override func_containsMagneticMaterial = this->get_override( "containsMagneticMaterial" ) )
            return func_containsMagneticMaterial(  );
        else
            return this->ISample::containsMagneticMaterial(  );
    }
    
    
    bool default_containsMagneticMaterial(  ) const  {
        return ISample::containsMagneticMaterial( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else
            return this->IParameterized::createParameterTree(  );
    }
    
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual ::ICompositeSample * getCompositeSample(  ) {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else
            return this->ICompositeSample::getCompositeSample(  );
    }
    
    
    ::ICompositeSample * default_getCompositeSample(  ) {
        return ICompositeSample::getCompositeSample( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else
            return this->ICompositeSample::getCompositeSample(  );
    }
    
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ICompositeSample::getCompositeSample( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else
            this->IParameterized::printParameters(  );
    }
    
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void printSampleTree(  ) {
        if( bp::override func_printSampleTree = this->get_override( "printSampleTree" ) )
            func_printSampleTree(  );
        else
            this->ISample::printSampleTree(  );
    }
    
    
    void default_printSampleTree(  ) {
        ISample::printSampleTree( );
    }

    virtual void registerParameter( ::std::string const & name, double * parpointer ) {
        namespace bpl = boost::python;
        if( bpl::override func_registerParameter = this->get_override( "registerParameter" ) ){
            bpl::object py_result = bpl::call<bpl::object>( func_registerParameter.ptr(), name, parpointer );
        }
        else{
            IParameterized::registerParameter( name, parpointer );
        }
    }
    
    static void default_registerParameter( ::IParameterized & inst, ::std::string const & name, long unsigned int parpointer ){
        if( dynamic_cast< ILayout_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else
            return this->IParameterized::setParameterValue( name, value );
    }
    
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else
            this->IParameterized::setParametersAreChanged(  );
    }
    
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

    virtual ::std::size_t size(  ) const  {
        if( bp::override func_size = this->get_override( "size" ) )
            return func_size(  );
        else
            return this->ICompositeSample::size(  );
    }
    
    
    ::std::size_t default_size(  ) const  {
        return ICompositeSample::size( );
    }

};

void register_ILayout_class(){

    { //::ILayout
        typedef bp::class_< ILayout_wrapper, bp::bases< ICompositeSample >, boost::noncopyable > ILayout_exposer_t;
        ILayout_exposer_t ILayout_exposer = ILayout_exposer_t( "ILayout", bp::init< >() );
        bp::scope ILayout_scope( ILayout_exposer );
        { //::ILayout::accept
        
            typedef void ( ::ILayout::*accept_function_type )( ::ISampleVisitor * ) const;
            
            ILayout_exposer.def( 
                "accept"
                , bp::pure_virtual( accept_function_type(&::ILayout::accept) )
                , ( bp::arg("visitor") ) );
        
        }
        { //::ILayout::clone
        
            typedef ::ILayout * ( ::ILayout::*clone_function_type )(  ) const;
            
            ILayout_exposer.def( 
                "clone"
                , bp::pure_virtual( clone_function_type(&::ILayout::clone) )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ILayout::cloneInvertB
        
            typedef ::ILayout * ( ::ILayout::*cloneInvertB_function_type )(  ) const;
            
            ILayout_exposer.def( 
                "cloneInvertB"
                , bp::pure_virtual( cloneInvertB_function_type(&::ILayout::cloneInvertB) )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ILayout::getAbundanceFractionOfParticle
        
            typedef double ( ::ILayout::*getAbundanceFractionOfParticle_function_type )( ::std::size_t ) const;
            
            ILayout_exposer.def( 
                "getAbundanceFractionOfParticle"
                , bp::pure_virtual( getAbundanceFractionOfParticle_function_type(&::ILayout::getAbundanceFractionOfParticle) )
                , ( bp::arg("index") ) );
        
        }
        { //::ILayout::getInterferenceFunctions
        
            typedef ::SafePointerVector<IInterferenceFunction> ( ::ILayout::*getInterferenceFunctions_function_type )(  ) const;
            
            ILayout_exposer.def( 
                "getInterferenceFunctions"
                , bp::pure_virtual( getInterferenceFunctions_function_type(&::ILayout::getInterferenceFunctions) ) );
        
        }
        { //::ILayout::getNumberOfInterferenceFunctions
        
            typedef ::std::size_t ( ::ILayout::*getNumberOfInterferenceFunctions_function_type )(  ) const;
            typedef ::std::size_t ( ILayout_wrapper::*default_getNumberOfInterferenceFunctions_function_type )(  ) const;
            
            ILayout_exposer.def( 
                "getNumberOfInterferenceFunctions"
                , getNumberOfInterferenceFunctions_function_type(&::ILayout::getNumberOfInterferenceFunctions)
                , default_getNumberOfInterferenceFunctions_function_type(&ILayout_wrapper::default_getNumberOfInterferenceFunctions) );
        
        }
        { //::ILayout::getNumberOfParticles
        
            typedef ::std::size_t ( ::ILayout::*getNumberOfParticles_function_type )(  ) const;
            
            ILayout_exposer.def( 
                "getNumberOfParticles"
                , bp::pure_virtual( getNumberOfParticles_function_type(&::ILayout::getNumberOfParticles) ) );
        
        }
        { //::ILayout::getParticleInfo
        
            typedef ::ParticleInfo const * ( ::ILayout::*getParticleInfo_function_type )( ::std::size_t ) const;
            
            ILayout_exposer.def( 
                "getParticleInfo"
                , bp::pure_virtual( getParticleInfo_function_type(&::ILayout::getParticleInfo) )
                , ( bp::arg("index") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ILayout::getTotalParticleSurfaceDensity
        
            typedef double ( ::ILayout::*getTotalParticleSurfaceDensity_function_type )(  ) const;
            
            ILayout_exposer.def( 
                "getTotalParticleSurfaceDensity"
                , getTotalParticleSurfaceDensity_function_type( &::ILayout::getTotalParticleSurfaceDensity ) );
        
        }
        { //::ILayout::setTotalParticleSurfaceDensity
        
            typedef void ( ::ILayout::*setTotalParticleSurfaceDensity_function_type )( double ) ;
            
            ILayout_exposer.def( 
                "setTotalParticleSurfaceDensity"
                , setTotalParticleSurfaceDensity_function_type( &::ILayout::setTotalParticleSurfaceDensity )
                , ( bp::arg("surface_density") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( ILayout_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            ILayout_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&ILayout_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type )(  ) ;
            typedef void ( ILayout_wrapper::*default_clearParameterPool_function_type )(  ) ;
            
            ILayout_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&ILayout_wrapper::default_clearParameterPool) );
        
        }
        { //::ISample::containsMagneticMaterial
        
            typedef bool ( ::ISample::*containsMagneticMaterial_function_type )(  ) const;
            typedef bool ( ILayout_wrapper::*default_containsMagneticMaterial_function_type )(  ) const;
            
            ILayout_exposer.def( 
                "containsMagneticMaterial"
                , containsMagneticMaterial_function_type(&::ISample::containsMagneticMaterial)
                , default_containsMagneticMaterial_function_type(&ILayout_wrapper::default_containsMagneticMaterial) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( ILayout_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            ILayout_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&ILayout_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ICompositeSample::getCompositeSample
        
            typedef ::ICompositeSample * ( ::ICompositeSample::*getCompositeSample_function_type )(  ) ;
            typedef ::ICompositeSample * ( ILayout_wrapper::*default_getCompositeSample_function_type )(  ) ;
            
            ILayout_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ICompositeSample::getCompositeSample)
                , default_getCompositeSample_function_type(&ILayout_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ICompositeSample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ICompositeSample::*getCompositeSample_function_type )(  ) const;
            typedef ::ICompositeSample const * ( ILayout_wrapper::*default_getCompositeSample_function_type )(  ) const;
            
            ILayout_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ICompositeSample::getCompositeSample)
                , default_getCompositeSample_function_type(&ILayout_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( ILayout_wrapper::*default_printParameters_function_type )(  ) const;
            
            ILayout_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&ILayout_wrapper::default_printParameters) );
        
        }
        { //::ISample::printSampleTree
        
            typedef void ( ::ISample::*printSampleTree_function_type )(  ) ;
            typedef void ( ILayout_wrapper::*default_printSampleTree_function_type )(  ) ;
            
            ILayout_exposer.def( 
                "printSampleTree"
                , printSampleTree_function_type(&::ISample::printSampleTree)
                , default_printSampleTree_function_type(&ILayout_wrapper::default_printSampleTree) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            ILayout_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &ILayout_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type )( ::std::string const &,double ) ;
            typedef bool ( ILayout_wrapper::*default_setParameterValue_function_type )( ::std::string const &,double ) ;
            
            ILayout_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&ILayout_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( ILayout_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            ILayout_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&ILayout_wrapper::default_setParametersAreChanged) );
        
        }
        { //::ICompositeSample::size
        
            typedef ::std::size_t ( ::ICompositeSample::*size_function_type )(  ) const;
            typedef ::std::size_t ( ILayout_wrapper::*default_size_function_type )(  ) const;
            
            ILayout_exposer.def( 
                "size"
                , size_function_type(&::ICompositeSample::size)
                , default_size_function_type(&ILayout_wrapper::default_size) );
        
        }
    }

}