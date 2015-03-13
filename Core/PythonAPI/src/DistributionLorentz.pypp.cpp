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
#include "DistributionLorentz.pypp.h"

namespace bp = boost::python;

struct DistributionLorentz_wrapper : DistributionLorentz, bp::wrapper< DistributionLorentz > {

    DistributionLorentz_wrapper(DistributionLorentz const & arg )
    : DistributionLorentz( arg )
      , bp::wrapper< DistributionLorentz >(){
        // copy constructor
        m_pyobj = 0;
    }

    DistributionLorentz_wrapper( )
    : DistributionLorentz( )
      , bp::wrapper< DistributionLorentz >(){
        // null constructor
    m_pyobj = 0;
    }

    DistributionLorentz_wrapper(double mean, double hwhm )
    : DistributionLorentz( mean, hwhm )
      , bp::wrapper< DistributionLorentz >(){
        // constructor
    m_pyobj = 0;
    }

    virtual ::DistributionLorentz * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->DistributionLorentz::clone(  );
        }
    }
    
    ::DistributionLorentz * default_clone(  ) const  {
        return DistributionLorentz::clone( );
    }

    virtual ::std::vector< double > generateValueList( ::std::size_t nbr_samples, double sigma_factor ) const  {
        if( bp::override func_generateValueList = this->get_override( "generateValueList" ) )
            return func_generateValueList( nbr_samples, sigma_factor );
        else{
            return this->DistributionLorentz::generateValueList( nbr_samples, sigma_factor );
        }
    }
    
    ::std::vector< double > default_generateValueList( ::std::size_t nbr_samples, double sigma_factor ) const  {
        return DistributionLorentz::generateValueList( nbr_samples, sigma_factor );
    }

    virtual double getMean(  ) const  {
        if( bp::override func_getMean = this->get_override( "getMean" ) )
            return func_getMean(  );
        else{
            return this->DistributionLorentz::getMean(  );
        }
    }
    
    double default_getMean(  ) const  {
        return DistributionLorentz::getMean( );
    }

    virtual double probabilityDensity( double x ) const  {
        if( bp::override func_probabilityDensity = this->get_override( "probabilityDensity" ) )
            return func_probabilityDensity( x );
        else{
            return this->DistributionLorentz::probabilityDensity( x );
        }
    }
    
    double default_probabilityDensity( double x ) const  {
        return DistributionLorentz::probabilityDensity( x );
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

    virtual void registerParameter( ::std::string const & name, double * parpointer, ::AttLimits const & limits=AttLimits::limitless( ) ) {
        namespace bpl = boost::python;
        if( bpl::override func_registerParameter = this->get_override( "registerParameter" ) ){
            bpl::object py_result = bpl::call<bpl::object>( func_registerParameter.ptr(), name, parpointer, limits );
        }
        else{
            IParameterized::registerParameter( name, parpointer, boost::ref(limits) );
        }
    }
    
    static void default_registerParameter( ::IParameterized & inst, ::std::string const & name, long unsigned int parpointer, ::AttLimits const & limits=AttLimits::limitless( ) ){
        if( dynamic_cast< DistributionLorentz_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ), limits);
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ), limits);
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

    PyObject* m_pyobj;

};

void register_DistributionLorentz_class(){

    { //::DistributionLorentz
        typedef bp::class_< DistributionLorentz_wrapper, bp::bases< IDistribution1D >, std::auto_ptr< DistributionLorentz_wrapper > > DistributionLorentz_exposer_t;
        DistributionLorentz_exposer_t DistributionLorentz_exposer = DistributionLorentz_exposer_t( "DistributionLorentz", bp::init< >() );
        bp::scope DistributionLorentz_scope( DistributionLorentz_exposer );
        DistributionLorentz_exposer.def( bp::init< double, double >(( bp::arg("mean"), bp::arg("hwhm") )) );
        { //::DistributionLorentz::clone
        
            typedef ::DistributionLorentz * ( ::DistributionLorentz::*clone_function_type)(  ) const;
            typedef ::DistributionLorentz * ( DistributionLorentz_wrapper::*default_clone_function_type)(  ) const;
            
            DistributionLorentz_exposer.def( 
                "clone"
                , clone_function_type(&::DistributionLorentz::clone)
                , default_clone_function_type(&DistributionLorentz_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::DistributionLorentz::generateValueList
        
            typedef ::std::vector< double > ( ::DistributionLorentz::*generateValueList_function_type)( ::std::size_t,double ) const;
            typedef ::std::vector< double > ( DistributionLorentz_wrapper::*default_generateValueList_function_type)( ::std::size_t,double ) const;
            
            DistributionLorentz_exposer.def( 
                "generateValueList"
                , generateValueList_function_type(&::DistributionLorentz::generateValueList)
                , default_generateValueList_function_type(&DistributionLorentz_wrapper::default_generateValueList)
                , ( bp::arg("nbr_samples"), bp::arg("sigma_factor") ) );
        
        }
        { //::DistributionLorentz::getHWHM
        
            typedef double ( ::DistributionLorentz::*getHWHM_function_type)(  ) const;
            
            DistributionLorentz_exposer.def( 
                "getHWHM"
                , getHWHM_function_type( &::DistributionLorentz::getHWHM ) );
        
        }
        { //::DistributionLorentz::getMean
        
            typedef double ( ::DistributionLorentz::*getMean_function_type)(  ) const;
            typedef double ( DistributionLorentz_wrapper::*default_getMean_function_type)(  ) const;
            
            DistributionLorentz_exposer.def( 
                "getMean"
                , getMean_function_type(&::DistributionLorentz::getMean)
                , default_getMean_function_type(&DistributionLorentz_wrapper::default_getMean) );
        
        }
        { //::DistributionLorentz::probabilityDensity
        
            typedef double ( ::DistributionLorentz::*probabilityDensity_function_type)( double ) const;
            typedef double ( DistributionLorentz_wrapper::*default_probabilityDensity_function_type)( double ) const;
            
            DistributionLorentz_exposer.def( 
                "probabilityDensity"
                , probabilityDensity_function_type(&::DistributionLorentz::probabilityDensity)
                , default_probabilityDensity_function_type(&DistributionLorentz_wrapper::default_probabilityDensity)
                , ( bp::arg("x") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type)(  ) ;
            typedef bool ( DistributionLorentz_wrapper::*default_areParametersChanged_function_type)(  ) ;
            
            DistributionLorentz_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&DistributionLorentz_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type)(  ) ;
            typedef void ( DistributionLorentz_wrapper::*default_clearParameterPool_function_type)(  ) ;
            
            DistributionLorentz_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&DistributionLorentz_wrapper::default_clearParameterPool) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type)(  ) const;
            typedef ::ParameterPool * ( DistributionLorentz_wrapper::*default_createParameterTree_function_type)(  ) const;
            
            DistributionLorentz_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&DistributionLorentz_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type)(  ) const;
            typedef void ( DistributionLorentz_wrapper::*default_printParameters_function_type)(  ) const;
            
            DistributionLorentz_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&DistributionLorentz_wrapper::default_printParameters) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int,::AttLimits const & );
            
            DistributionLorentz_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &DistributionLorentz_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer"), bp::arg("limits")=AttLimits::limitless( ) ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type)( ::std::string const &,double ) ;
            typedef bool ( DistributionLorentz_wrapper::*default_setParameterValue_function_type)( ::std::string const &,double ) ;
            
            DistributionLorentz_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&DistributionLorentz_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type)(  ) ;
            typedef void ( DistributionLorentz_wrapper::*default_setParametersAreChanged_function_type)(  ) ;
            
            DistributionLorentz_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&DistributionLorentz_wrapper::default_setParametersAreChanged) );
        
        }
    }

}
