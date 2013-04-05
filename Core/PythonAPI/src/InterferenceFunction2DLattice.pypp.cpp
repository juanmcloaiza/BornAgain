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
#include "InterferenceFunction2DLattice.pypp.h"

namespace bp = boost::python;

struct InterferenceFunction2DLattice_wrapper : InterferenceFunction2DLattice, bp::wrapper< InterferenceFunction2DLattice > {

    InterferenceFunction2DLattice_wrapper(::Lattice2DIFParameters const & lattice_params )
    : InterferenceFunction2DLattice( boost::ref(lattice_params) )
      , bp::wrapper< InterferenceFunction2DLattice >(){
        // constructor
    
    }

    virtual ::InterferenceFunction2DLattice * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->InterferenceFunction2DLattice::clone(  );
        }
    }
    
    ::InterferenceFunction2DLattice * default_clone(  ) const  {
        return InterferenceFunction2DLattice::clone( );
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

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ISample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ISample::getCompositeSample( );
    }

    virtual double getKappa(  ) const  {
        if( bp::override func_getKappa = this->get_override( "getKappa" ) )
            return func_getKappa(  );
        else{
            return this->IInterferenceFunction::getKappa(  );
        }
    }
    
    double default_getKappa(  ) const  {
        return IInterferenceFunction::getKappa( );
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

};

void register_InterferenceFunction2DLattice_class(){

    { //::InterferenceFunction2DLattice
        typedef bp::class_< InterferenceFunction2DLattice_wrapper, bp::bases< IInterferenceFunction >, boost::noncopyable > InterferenceFunction2DLattice_exposer_t;
        InterferenceFunction2DLattice_exposer_t InterferenceFunction2DLattice_exposer = InterferenceFunction2DLattice_exposer_t( "InterferenceFunction2DLattice", bp::init< Lattice2DIFParameters const & >(( bp::arg("lattice_params") )) );
        bp::scope InterferenceFunction2DLattice_scope( InterferenceFunction2DLattice_exposer );
        { //::InterferenceFunction2DLattice::clone
        
            typedef ::InterferenceFunction2DLattice * ( ::InterferenceFunction2DLattice::*clone_function_type )(  ) const;
            typedef ::InterferenceFunction2DLattice * ( InterferenceFunction2DLattice_wrapper::*default_clone_function_type )(  ) const;
            
            InterferenceFunction2DLattice_exposer.def( 
                "clone"
                , clone_function_type(&::InterferenceFunction2DLattice::clone)
                , default_clone_function_type(&InterferenceFunction2DLattice_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::InterferenceFunction2DLattice::setProbabilityDistribution
        
            typedef void ( ::InterferenceFunction2DLattice::*setProbabilityDistribution_function_type )( ::IFTDistribution2D const & ) ;
            
            InterferenceFunction2DLattice_exposer.def( 
                "setProbabilityDistribution"
                , setProbabilityDistribution_function_type( &::InterferenceFunction2DLattice::setProbabilityDistribution )
                , ( bp::arg("pdf") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( InterferenceFunction2DLattice_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            InterferenceFunction2DLattice_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&InterferenceFunction2DLattice_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type )(  ) ;
            typedef void ( InterferenceFunction2DLattice_wrapper::*default_clearParameterPool_function_type )(  ) ;
            
            InterferenceFunction2DLattice_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&InterferenceFunction2DLattice_wrapper::default_clearParameterPool) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( InterferenceFunction2DLattice_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            InterferenceFunction2DLattice_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&InterferenceFunction2DLattice_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ISample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ISample::*getCompositeSample_function_type )(  ) const;
            typedef ::ICompositeSample const * ( InterferenceFunction2DLattice_wrapper::*default_getCompositeSample_function_type )(  ) const;
            
            InterferenceFunction2DLattice_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ISample::getCompositeSample)
                , default_getCompositeSample_function_type(&InterferenceFunction2DLattice_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IInterferenceFunction::getKappa
        
            typedef double ( ::IInterferenceFunction::*getKappa_function_type )(  ) const;
            typedef double ( InterferenceFunction2DLattice_wrapper::*default_getKappa_function_type )(  ) const;
            
            InterferenceFunction2DLattice_exposer.def( 
                "getKappa"
                , getKappa_function_type(&::IInterferenceFunction::getKappa)
                , default_getKappa_function_type(&InterferenceFunction2DLattice_wrapper::default_getKappa) );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( InterferenceFunction2DLattice_wrapper::*default_printParameters_function_type )(  ) const;
            
            InterferenceFunction2DLattice_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&InterferenceFunction2DLattice_wrapper::default_printParameters) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type )( ::std::string const &,double ) ;
            typedef bool ( InterferenceFunction2DLattice_wrapper::*default_setParameterValue_function_type )( ::std::string const &,double ) ;
            
            InterferenceFunction2DLattice_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&InterferenceFunction2DLattice_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( InterferenceFunction2DLattice_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            InterferenceFunction2DLattice_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&InterferenceFunction2DLattice_wrapper::default_setParametersAreChanged) );
        
        }
    }

}
