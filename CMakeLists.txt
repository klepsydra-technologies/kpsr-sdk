# Copyright 2023 Klepsydra Technologies AG
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Main header: Project name & Configuration
# ------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.12)

set(PROJ_MAIN_NAME sdk)
set(KLEPSYDRA_SDK_VERSION_MAJOR 2)
set(KLEPSYDRA_SDK_VERSION_MINOR 0)
set(KLEPSYDRA_SDK_VERSION_PATCH 1)
set(KLEPSYDRA_SDK_VERSION
    ${KLEPSYDRA_SDK_VERSION_MAJOR}.${KLEPSYDRA_SDK_VERSION_MINOR}.${KLEPSYDRA_SDK_VERSION_PATCH}
)

if(DEFINED KPSR_BUILD_PATH)

else()
    set(KPSR_BUILD_PATH ${CMAKE_SOURCE_DIR}/kpsr-build)
endif()

message(STATUS "kpsr-build path: " ${KPSR_BUILD_PATH})

if(DEFINED THIRDPARTIES_PATH)

else()
    set(THIRDPARTIES_PATH ${CMAKE_SOURCE_DIR}/thirdparties)
endif()

message(STATUS "Thirdparties install path: " ${THIRDPARTIES_PATH})

# Setting CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/os/common
     ${KPSR_BUILD_PATH}/cmake ${KPSR_BUILD_PATH}/os/common)

# Including CMake modules
# -----------------------
# Common modules
# ----------
# Must use GNUInstallDirs to install libraries into correct locations on all
# platforms.
include(GNUInstallDirs)
include(CheckCXXCompilerFlag)
include(CheckIncludeFileCXX)
include(GenerateVersion)
include(SetCxxStandard)
include(KlepsydraBuild)
include(KlepsydraLinkerFlags)
include(ConfigureLinux)
# OS specific modules
# ----------
include(SetCpackDebianVariables)

project(
    kpsr-${PROJ_MAIN_NAME}
    LANGUAGES CXX
    VERSION ${KLEPSYDRA_SDK_VERSION})

if(DEFINED TARGET_OS)
    include(${OS_CMAKE})
endif()

if(NOT DEFINED GTEST_PATH)
    set(GTEST_PATH ${THIRDPARTIES_PATH}/googletest) # default google test path
endif()
message(STATUS "Google test path: " ${GTEST_PATH})

# Configuration types
set(CMAKE_CONFIGURATION_TYPES
    "Debug;Release"
    CACHE STRING "Configs" FORCE)

if(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
                                                 ${CMAKE_CONFIGURATION_TYPES})
endif()

# Configure variables
# ------------------------------------------------------------------------------------------------------
set(LIBRARY_OUTPUT_PATH
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH "Library output" FORCE)
set(EXECUTABLE_OUTPUT_PATH
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH "Executable output" FORCE)

set(MINIMAL_BUILD
    Off
    CACHE BOOL "Minimal build mode")
include(KlepsydraExamplesTests)

set(BUILD_SHARED_LIBS
    ON
    CACHE BOOL "Build shared libraries")

kpsr_set_linker_flags()

check_cxx_compiler_flag(-pedantic HAS_PEDANTIC)
if(HAS_PEDANTIC)
    add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:-pedantic>)
endif()

check_cxx_compiler_flag(-Wall HAS_WALL)
if(HAS_WALL)
    add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:-Wall>)
endif()

check_include_file_cxx(sys/epoll.h HAS_EPOLL)
if(HAS_EPOLL)
    add_compile_definitions($<$<COMPILE_LANGUAGE:CXX>:HAS_EPOLL>)
else()
    add_compile_definitions($<$<COMPILE_LANGUAGE:CXX>:USE_GET_WRITE_QUEUE>)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # require at least gcc 4.8
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 7.5)
        add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:-faligned-new>)
    endif()
endif()

add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:-fno-strict-overflow>)

if(KPSR_WITH_CODE_METRICS)
    if(CMAKE_BUILD_TYPE MATCHES Debug AND CMAKE_COMPILER_IS_GNUCXX)
        include(CodeCoverage)
        set(CODE_COVERAGE_VERBOSE ON)
        append_coverage_compiler_flags()
    endif()

    # Code style check
    include(CppcheckTargets)
    include(Findcppcheck)
endif()

# Code format check
include(CodeFormat)

# CCACHE support
include(FindCcache)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Configuration current project
# ------------------------------------------------------------------------------------------------------

# Project Logic
# ------------------------------------------------------------------------------------------------------

# ##############################################################################
# ADD SUB FOLDERS
# ##############################################################################
add_subdirectory(modules)

if(KPSR_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Code Coverage
if(KPSR_WITH_CODE_METRICS
   AND CMAKE_BUILD_TYPE MATCHES Debug
   AND CMAKE_COMPILER_IS_GNUCXX)
    string(REPLACE ${CMAKE_SOURCE_DIR}/ "" THIRDPARTIES_PATH_COVERAGE
                   ${THIRDPARTIES_PATH})
    list(
        APPEND
        COVERAGE_EXCLUDES
        ${THIRDPARTIES_PATH_COVERAGE}
        ${CMAKE_PREFIX_PATH}
        tests
        examples
        /usr/
        /opt)
    setup_target_for_coverage_gcovr_xml(NAME coverage EXECUTABLE make test)
endif()

# Install
# ------------------------------------------------------------------------------------------------------
set(INSTALL_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/klepsydrasdk)
message("CORE_EXPORT_TARGETS: " ${CORE_EXPORT_TARGETS})

# Install binaries

# Export the package for use from the build-tree (this registers the build-tree
# with a global CMake-registry)
export(TARGETS kpsr-sdk FILE "${PROJECT_BINARY_DIR}/KlepsydraSDKTargets.cmake")
export(PACKAGE klepsydrasdk)

# Create the KlepsydraConfig.cmake and KlepsydraConfigVersion files
include(CMakePackageConfigHelpers)

configure_package_config_file(
    KlepsydraSDKConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/KlepsydraSDKConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CMAKE_DIR}
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/KlepsydraSDKConfigVersion.cmake
    VERSION ${KLEPSYDRA_SDK_VERSION}
    COMPATIBILITY SameMajorVersion)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/KlepsydraSDKConfig.cmake
          ${CMAKE_CURRENT_BINARY_DIR}/KlepsydraSDKConfigVersion.cmake
    DESTINATION ${INSTALL_CMAKE_DIR}
    COMPONENT dev)

# Install the export set for use with the install-tree
install(
    EXPORT KlepsydraSDKTargets
    FILE KlepsydraSDKTargets.cmake
    DESTINATION "${INSTALL_CMAKE_DIR}"
    COMPONENT dev)

# PACKAGING
if(NOT DEFINED KPSR_VERSION_MAJOR)
    set(KPSR_VERSION_MAJOR ${KLEPSYDRA_SDK_VERSION_MAJOR})
endif()

if(NOT DEFINED KPSR_VERSION_MINOR)
    set(KPSR_VERSION_MINOR ${KLEPSYDRA_SDK_VERSION_MINOR})
endif()

if(NOT DEFINED KPSR_VERSION_PATCH)
    set(KPSR_VERSION_PATCH ${KLEPSYDRA_SDK_VERSION_PATCH})
endif()

set(KPSR_PACKAGE_DESCRIPTION "Klepsydra SDK Libraries")
set(KPSR_PACKAGE_DESCRIPTION_SUMMARY "Klepsydra SDK Libraries")

include(KlepsydraPackaging)
