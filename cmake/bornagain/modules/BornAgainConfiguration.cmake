###############################################################################
# BornAgain project configuration
###############################################################################

# -----------------------------------------------------------------------------
# Common policies
# -----------------------------------------------------------------------------

# --- from GUI section

#if(POLICY CMP0020)
#    cmake_policy(SET CMP0020 NEW)
#endif()

#if(POLICY CMP0043)
#    cmake_policy(SET CMP0043 NEW)
#endif()

#if(POLICY CMP0028)
#    cmake_policy(SET CMP0028 NEW)
#endif()

# -----------------------------------------------------------------------------
# Common definitions
# -----------------------------------------------------------------------------

# suppress qDebug() output for release build
if(CMAKE_BUILD_TYPE STREQUAL Release)
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

# -----------------------------------------------------------------------------
# cmake runtime output configuration
# -----------------------------------------------------------------------------

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(BUILD_AUTO_DIR ${CMAKE_BINARY_DIR}/auto)
configure_file("${TEMPLATE_DIR}/auto_README.in" "${CMAKE_SOURCE_DIR}/auto/README" @ONLY)

file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bornagain)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${BUILD_AUTO_DIR})

# -----------------------------------------------------------------------------
# file extensions
# -----------------------------------------------------------------------------

if(WIN32)
    set(libprefix _lib)
    set(libsuffix .dll)
elseif(APPLE)
    set(libprefix _lib)
    set(libsuffix .so)
else()
    set(libprefix _lib)
    set(libsuffix .so)
endif()

# -----------------------------------------------------------------------------
# destinations
# -----------------------------------------------------------------------------

if(WIN32)
    set(destination_bin bin)
    set(destination_lib bin)
    set(destination_gui bin)
    set(destination_include include)
    set(destination_examples Examples)
    set(destination_images Images)
    set(destination_libexec ${destination_bin})
else()
    set(destination_suffix BornAgain-${BornAgain_VERSION_MAJOR}.${BornAgain_VERSION_MINOR})
    if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
        set(destination_bundle BornAgain.app)
        set(destination_prefix ${destination_bundle}/Contents/)
        set(destination_libexec ${destination_prefix}libexec/${destination_suffix})
    else()
        set(destination_prefix "")
        set(destination_libexec ${destination_prefix}lib/${destination_suffix})
    endif()
    set(destination_bin ${destination_prefix}bin)
    set(destination_gui ${destination_libexec})
    set(destination_lib ${destination_prefix}lib/${destination_suffix})
    set(destination_include ${destination_prefix}include/${destination_suffix})
    set(destination_share ${destination_prefix}share/${destination_suffix}/)
    set(destination_examples ${destination_share}Examples)
    set(destination_images ${destination_share}Images)
endif()

message(STATUS "Destination directories: bin->${destination_bin}, lib->${destination_lib}, gui&libexec->${destination_libexec}, include->${destination_include}, share->${destination_share}")

# -----------------------------------------------------------------------------
# configure files
# -----------------------------------------------------------------------------

if(BORNAGAIN_RELEASE)
    # configure a header file to pass CMake settings to the source code
    configure_file("${TEMPLATE_DIR}/BAVersion.h.in" "${CMAKE_SOURCE_DIR}/Core/Samples/inc/BAVersion.h")

    # configure Doxyfile
    configure_file("${CMAKE_SOURCE_DIR}/Doc/Doxygen/Doxyfile.in" "${CMAKE_SOURCE_DIR}/Doc/Doxygen/Doxyfile" @ONLY)

    # configure FindBornagain script
    configure_file("${TEMPLATE_DIR}/FindBornAgain.cmake.in" "${CMAKE_SOURCE_DIR}/Examples/cpp/CylindersAndPrisms/modules/FindBornAgain.cmake" @ONLY)
endif()

# -----------------------------------------------------------------------------
# configure BornAgain launch scripts
# -----------------------------------------------------------------------------

set(this_bindir $BORNAGAINSYS/bin)
set(this_libdir $BORNAGAINSYS/lib/${destination_suffix})
configure_file("${TEMPLATE_DIR}/thisbornagain.sh.in" "${BUILD_AUTO_DIR}/thisbornagain.sh" @ONLY)
configure_file("${TEMPLATE_DIR}/thisbornagain.csh.in" "${BUILD_AUTO_DIR}/thisbornagain.csh" @ONLY)

# -----------------------------------------------------------------------------
# configure C++ source code
# -----------------------------------------------------------------------------

configure_file("${TEMPLATE_DIR}/BAConfigure.h.in" "${BUILD_AUTO_DIR}/BAConfigure.h" @ONLY)
configure_file("${TEMPLATE_DIR}/BAPython.h.in" "${BUILD_AUTO_DIR}/BAPython.h" @ONLY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${BUILD_AUTO_DIR}")

# -----------------------------------------------------------------------------
# configure postinst and prerm for the debian package
# -----------------------------------------------------------------------------

if(BUILD_DEBIAN)
    set(CMAKE_INSTALL_PREFIX "/usr")
    execute_process(COMMAND "${PYTHON_EXECUTABLE}" -c "from distutils import sysconfig; print sysconfig.get_python_lib(1,0,prefix=None)"
        OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
        OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    configure_file("${TEMPLATE_DIR}/postinst.in" "${BUILD_AUTO_DIR}/postinst" @ONLY)
    configure_file("${TEMPLATE_DIR}/prerm.in" "${BUILD_AUTO_DIR}/prerm" @ONLY)
    set(CMAKE_INSTALL_RPATH "\$ORIGIN/../../lib/${destination_suffix}")
endif(BUILD_DEBIAN)