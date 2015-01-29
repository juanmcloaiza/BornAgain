// This file has been generated by Py++.

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Automatically generated boost::python code for BornAgain Python bindings
//! @brief     Automatically generated boost::python code for BornAgain Python bindings
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Juelich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_OFF(missing-field-initializers)
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter)
GCC_DIAG_ON(missing-field-initializers)
#include "__call_policies.pypp.hpp"
#include "__convenience.pypp.hpp"
#include "PythonCoreList.h"
#include "ParameterDistribution.pypp.h"

namespace bp = boost::python;

struct ParameterDistribution_wrapper : ParameterDistribution, bp::wrapper< ParameterDistribution > {

    ParameterDistribution_wrapper(::std::string const & par_name, ::IDistribution1D const & distribution, ::std::size_t nbr_samples, double sigma_factor=0.0 )
    : ParameterDistribution( par_name, boost::ref(distribution), nbr_samples, sigma_factor )
      , bp::wrapper< ParameterDistribution >(){
        // constructor
    
    }

    ParameterDistribution_wrapper(::ParameterDistribution const & other )
    : ParameterDistribution( boost::ref(other) )
      , bp::wrapper< ParameterDistribution >(){
        // copy constructor
    
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
        if( dynamic_cast< ParameterDistribution_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
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

void register_ParameterDistribution_class(){

    { //::ParameterDistribution
        typedef bp::class_< ParameterDistribution_wrapper, bp::bases< IParameterized > > ParameterDistribution_exposer_t;
        ParameterDistribution_exposer_t ParameterDistribution_exposer = ParameterDistribution_exposer_t( "ParameterDistribution", bp::init< std::string const &, IDistribution1D const &, std::size_t, bp::optional< double > >(( bp::arg("par_name"), bp::arg("distribution"), bp::arg("nbr_samples"), bp::arg("sigma_factor")=0.0 )) );
        bp::scope ParameterDistribution_scope( ParameterDistribution_exposer );
        ParameterDistribution_exposer.def( bp::init< ParameterDistribution const & >(( bp::arg("other") )) );
        { //::ParameterDistribution::getDistribution
        
            typedef ::IDistribution1D const * ( ::ParameterDistribution::*getDistribution_function_type)(  ) const;
            
            ParameterDistribution_exposer.def( 
                "getDistribution"
                , getDistribution_function_type( &::ParameterDistribution::getDistribution )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ParameterDistribution::getMainParameterName
        
            typedef ::std::string ( ::ParameterDistribution::*getMainParameterName_function_type)(  ) const;
            
            ParameterDistribution_exposer.def( 
                "getMainParameterName"
                , getMainParameterName_function_type( &::ParameterDistribution::getMainParameterName ) );
        
        }
        { //::ParameterDistribution::getNbrSamples
        
            typedef ::std::size_t ( ::ParameterDistribution::*getNbrSamples_function_type)(  ) const;
            
            ParameterDistribution_exposer.def( 
                "getNbrSamples"
                , getNbrSamples_function_type( &::ParameterDistribution::getNbrSamples ) );
        
        }
        { //::ParameterDistribution::getSigmaFactor
        
            typedef double ( ::ParameterDistribution::*getSigmaFactor_function_type)(  ) const;
            
            ParameterDistribution_exposer.def( 
                "getSigmaFactor"
                , getSigmaFactor_function_type( &::ParameterDistribution::getSigmaFactor ) );
        
        }
        { //::ParameterDistribution::linkParameter
        
            typedef ::ParameterDistribution & ( ::ParameterDistribution::*linkParameter_function_type)( ::std::string ) ;
            
            ParameterDistribution_exposer.def( 
                "linkParameter"
                , linkParameter_function_type( &::ParameterDistribution::linkParameter )
                , ( bp::arg("par_name") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ParameterDistribution::operator=
        
            typedef ::ParameterDistribution & ( ::ParameterDistribution::*assign_function_type)( ::ParameterDistribution const & ) ;
            
            ParameterDistribution_exposer.def( 
                "assign"
                , assign_function_type( &::ParameterDistribution::operator= )
                , ( bp::arg("other") )
                , bp::return_self< >() );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type)(  ) ;
            typedef bool ( ParameterDistribution_wrapper::*default_areParametersChanged_function_type)(  ) ;
            
            ParameterDistribution_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&ParameterDistribution_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type)(  ) ;
            typedef void ( ParameterDistribution_wrapper::*default_clearParameterPool_function_type)(  ) ;
            
            ParameterDistribution_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&ParameterDistribution_wrapper::default_clearParameterPool) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type)(  ) const;
            typedef ::ParameterPool * ( ParameterDistribution_wrapper::*default_createParameterTree_function_type)(  ) const;
            
            ParameterDistribution_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&ParameterDistribution_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type)(  ) const;
            typedef void ( ParameterDistribution_wrapper::*default_printParameters_function_type)(  ) const;
            
            ParameterDistribution_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&ParameterDistribution_wrapper::default_printParameters) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            ParameterDistribution_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &ParameterDistribution_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type)( ::std::string const &,double ) ;
            typedef bool ( ParameterDistribution_wrapper::*default_setParameterValue_function_type)( ::std::string const &,double ) ;
            
            ParameterDistribution_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&ParameterDistribution_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type)(  ) ;
            typedef void ( ParameterDistribution_wrapper::*default_setParametersAreChanged_function_type)(  ) ;
            
            ParameterDistribution_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&ParameterDistribution_wrapper::default_setParametersAreChanged) );
        
        }
    }

}