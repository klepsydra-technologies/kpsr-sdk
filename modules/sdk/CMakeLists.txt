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
set(PROJ_NAME kpsr-sdk)

# Source
# ---------------------------------------------------#
file(GLOB_RECURSE ${PROJ_NAME}_HEADERS "include/*.h")
file(GLOB ${PROJ_NAME}_SRC "src/*.cpp")

# Create Library
# ---------------------------------------------------#
add_library(${PROJ_NAME} SHARED ${${PROJ_NAME}_HEADERS} ${${PROJ_NAME}_SRC})

target_include_directories(
    ${PROJ_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                        $<INSTALL_INTERFACE:include>)

set_target_properties(
    ${PROJ_NAME} PROPERTIES VERSION ${KLEPSYDRA_SDK_VERSION}
                            SOVERSION ${KLEPSYDRA_SDK_VERSION_MAJOR})

set(HEADERS_TO_INSTALL
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/container.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/environment.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/event_transform_forwarder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/function_stats.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/pointer_abstraction_layer_h.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/publication_stats.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/publisher.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/scheduler.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/service.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/service_stats.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/subscriber.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/subscription_stats.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/klepsydra/sdk/time_utils.h")
# Install
install(
    TARGETS ${PROJ_NAME}
    EXPORT KlepsydraSDKTargets
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT libs)

install(
    FILES ${HEADERS_TO_INSTALL}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/klepsydra/sdk"
    COMPONENT dev)

add_core_export_target(${PROJ_NAME})
