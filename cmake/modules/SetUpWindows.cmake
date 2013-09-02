set(BORNAGAIN_ARCHITECTURE win32)
set(ROOT_PLATFORM win32)

#math(EXPR VC_MAJOR "${MSVC_VERSION} / 100")
#math(EXPR VC_MINOR "${MSVC_VERSION} % 100")

#set(SOEXT dll)
#set(EXEEXT exe)

#set(SYSLIBS advapi32.lib)
#set(XLIBS)
#set(CILIBS)
#set(CRYPTLIBS)

#---Select compiler flags----------------------------------------------------------------
#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -Z7")
#set(CMAKE_CXX_FLAGS_RELEASE        "-O2")
#set(CMAKE_CXX_FLAGS_DEBUG          "-Od -Z7")
#set(CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -Z7")
#set(CMAKE_C_FLAGS_RELEASE          "-O2")
#set(CMAKE_C_FLAGS_DEBUG            "-Od -Z7")


#if(CMAKE_PROJECT_NAME STREQUAL ROOT)
#  set(CMAKE_CXX_FLAGS "-nologo -I${CMAKE_SOURCE_DIR}/build/win -FIw32pragma.h -FIsehmap.h ${BLDCXXFLAGS} -EHsc- -W3 -wd4244 -D_WIN32")
#  set(CMAKE_C_FLAGS   "-nologo -I${CMAKE_SOURCE_DIR}/build/win -FIw32pragma.h -FIsehmap.h ${BLDCFLAGS} -EHsc- -W3 -D_WIN32")
#  install(FILES ${CMAKE_SOURCE_DIR}/build/win/w32pragma.h  DESTINATION include COMPONENT headers)
#  install(FILES ${CMAKE_SOURCE_DIR}/build/win/sehmap.h  DESTINATION include COMPONENT headers)  
#else()
#  set(CMAKE_CXX_FLAGS "-nologo -FIw32pragma.h -FIsehmap.h ${BLDCXXFLAGS} -EHsc- -W3 -wd4244 -D_WIN32")
#  set(CMAKE_C_FLAGS   "-nologo -FIw32pragma.h -FIsehmap.h ${BLDCFLAGS} -EHsc- -W3 -D_WIN32")
#endif()
#set(CMAKE_CXX_FLAGS "-D_WIN32")
#set(CMAKE_C_FLAGS   "-nologo -FIw32pragma.h -FIsehmap.h ${BLDCFLAGS} -EHsc- -W3 -D_WIN32")

#---Set Linker flags----------------------------------------------------------------------
#set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -ignore:4049,4206,4217,4221 -incremental:no")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -ignore:4049,4206,4217,4221 -incremental:no")

#set(CMAKE_C_OUTPUT_EXTENSION ".o")

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${CMAKE_SOURCE_DIR}/Core/Tools/inc -FIw32pragma.h")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mincoming-stack-boundary=2 -FIw32pragma.h")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mincoming-stack-boundary=2 -Wno-unused-local-typedefs -Wno-attributes")
endif()

