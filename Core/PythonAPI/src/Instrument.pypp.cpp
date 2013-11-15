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
#include "Instrument.pypp.h"

namespace bp = boost::python;

struct Instrument_wrapper : Instrument, bp::wrapper< Instrument > {

    Instrument_wrapper( )
    : Instrument( )
      , bp::wrapper< Instrument >(){
        // null constructor
    
    }

    Instrument_wrapper(::Instrument const & other )
    : Instrument( boost::ref(other) )
      , bp::wrapper< Instrument >(){
        // copy constructor
    
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

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else
            return this->IParameterized::createParameterTree(  );
    }
    
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
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
        if( dynamic_cast< Instrument_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
    }

    virtual int setMatchedParametersValue( ::std::string const & wildcards, double value ) {
        if( bp::override func_setMatchedParametersValue = this->get_override( "setMatchedParametersValue" ) )
            return func_setMatchedParametersValue( wildcards, value );
        else
            return this->IParameterized::setMatchedParametersValue( wildcards, value );
    }
    
    
    int default_setMatchedParametersValue( ::std::string const & wildcards, double value ) {
        return IParameterized::setMatchedParametersValue( wildcards, value );
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

};

void register_Instrument_class(){

    { //::Instrument
        typedef bp::class_< Instrument_wrapper, bp::bases< IParameterized > > Instrument_exposer_t;
        Instrument_exposer_t Instrument_exposer = Instrument_exposer_t( "Instrument", bp::init< >() );
        bp::scope Instrument_scope( Instrument_exposer );
        Instrument_exposer.def( bp::init< Instrument const & >(( bp::arg("other") )) );
        { //::Instrument::getBeam
        
            typedef ::Beam ( ::Instrument::*getBeam_function_type )(  ) const;
            
            Instrument_exposer.def( 
                "getBeam"
                , getBeam_function_type( &::Instrument::getBeam ) );
        
        }
        { //::Instrument::getDetector
        
            typedef ::Detector ( ::Instrument::*getDetector_function_type )(  ) const;
            
            Instrument_exposer.def( 
                "getDetector"
                , getDetector_function_type( &::Instrument::getDetector ) );
        
        }
        { //::Instrument::getDetectorAxis
        
            typedef ::IAxis const & ( ::Instrument::*getDetectorAxis_function_type )( ::std::size_t ) const;
            
            Instrument_exposer.def( 
                "getDetectorAxis"
                , getDetectorAxis_function_type( &::Instrument::getDetectorAxis )
                , ( bp::arg("index") )
                , bp::return_value_policy< bp::copy_const_reference >() );
        
        }
        { //::Instrument::getDetectorDimension
        
            typedef ::std::size_t ( ::Instrument::*getDetectorDimension_function_type )(  ) const;
            
            Instrument_exposer.def( 
                "getDetectorDimension"
                , getDetectorDimension_function_type( &::Instrument::getDetectorDimension ) );
        
        }
        { //::Instrument::getIntensity
        
            typedef double ( ::Instrument::*getIntensity_function_type )(  ) const;
            
            Instrument_exposer.def( 
                "getIntensity"
                , getIntensity_function_type( &::Instrument::getIntensity ) );
        
        }
        { //::Instrument::matchDetectorParameters
        
            typedef void ( ::Instrument::*matchDetectorParameters_function_type )( ::OutputData< double > const & ) ;
            
            Instrument_exposer.def( 
                "matchDetectorParameters"
                , matchDetectorParameters_function_type( &::Instrument::matchDetectorParameters )
                , ( bp::arg("output_data") ) );
        
        }
        { //::Instrument::setBeam
        
            typedef void ( ::Instrument::*setBeam_function_type )( ::Beam const & ) ;
            
            Instrument_exposer.def( 
                "setBeam"
                , setBeam_function_type( &::Instrument::setBeam )
                , ( bp::arg("beam") ) );
        
        }
        { //::Instrument::setBeamIntensity
        
            typedef void ( ::Instrument::*setBeamIntensity_function_type )( double ) ;
            
            Instrument_exposer.def( 
                "setBeamIntensity"
                , setBeamIntensity_function_type( &::Instrument::setBeamIntensity )
                , ( bp::arg("intensity") ) );
        
        }
        { //::Instrument::setBeamParameters
        
            typedef void ( ::Instrument::*setBeamParameters_function_type )( double,double,double ) ;
            
            Instrument_exposer.def( 
                "setBeamParameters"
                , setBeamParameters_function_type( &::Instrument::setBeamParameters )
                , ( bp::arg("lambda"), bp::arg("alpha_i"), bp::arg("phi_i") ) );
        
        }
        { //::Instrument::setDetectorParameters
        
            typedef void ( ::Instrument::*setDetectorParameters_function_type )( ::std::size_t,double,double,::std::size_t,double,double,bool ) ;
            
            Instrument_exposer.def( 
                "setDetectorParameters"
                , setDetectorParameters_function_type( &::Instrument::setDetectorParameters )
                , ( bp::arg("n_phi"), bp::arg("phi_f_min"), bp::arg("phi_f_max"), bp::arg("n_alpha"), bp::arg("alpha_f_min"), bp::arg("alpha_f_max"), bp::arg("isgisaxs_style")=(bool)(false) ) );
        
        }
        { //::Instrument::setDetectorParameters
        
            typedef void ( ::Instrument::*setDetectorParameters_function_type )( ::DetectorParameters const & ) ;
            
            Instrument_exposer.def( 
                "setDetectorParameters"
                , setDetectorParameters_function_type( &::Instrument::setDetectorParameters )
                , ( bp::arg("params") ) );
        
        }
        { //::Instrument::setDetectorResolutionFunction
        
            typedef void ( ::Instrument::*setDetectorResolutionFunction_function_type )( ::IResolutionFunction2D const & ) ;
            
            Instrument_exposer.def( 
                "setDetectorResolutionFunction"
                , setDetectorResolutionFunction_function_type( &::Instrument::setDetectorResolutionFunction )
                , ( bp::arg("p_resolution_function") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( Instrument_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            Instrument_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&Instrument_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type )(  ) ;
            typedef void ( Instrument_wrapper::*default_clearParameterPool_function_type )(  ) ;
            
            Instrument_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&Instrument_wrapper::default_clearParameterPool) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( Instrument_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            Instrument_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&Instrument_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( Instrument_wrapper::*default_printParameters_function_type )(  ) const;
            
            Instrument_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&Instrument_wrapper::default_printParameters) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            Instrument_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &Instrument_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setMatchedParametersValue
        
            typedef int ( ::IParameterized::*setMatchedParametersValue_function_type )( ::std::string const &,double ) ;
            typedef int ( Instrument_wrapper::*default_setMatchedParametersValue_function_type )( ::std::string const &,double ) ;
            
            Instrument_exposer.def( 
                "setMatchedParametersValue"
                , setMatchedParametersValue_function_type(&::IParameterized::setMatchedParametersValue)
                , default_setMatchedParametersValue_function_type(&Instrument_wrapper::default_setMatchedParametersValue)
                , ( bp::arg("wildcards"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type )( ::std::string const &,double ) ;
            typedef bool ( Instrument_wrapper::*default_setParameterValue_function_type )( ::std::string const &,double ) ;
            
            Instrument_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&Instrument_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( Instrument_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            Instrument_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&Instrument_wrapper::default_setParametersAreChanged) );
        
        }
    }

}
