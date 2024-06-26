# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2022 Metrological
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
cmake_minimum_required(VERSION 3.3)
set(PLUGIN_NAME UDPMessageOutput)

find_package(${NAMESPACE}Messaging REQUIRED)

add_executable(${PLUGIN_NAME}
    UDPMessageOutput.cpp
    Module.cpp
)

set_target_properties(${PLUGIN_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES)

target_link_libraries(${PLUGIN_NAME}
    PRIVATE
        ${NAMESPACE}Messaging::${NAMESPACE}Messaging)

install(TARGETS ${PLUGIN_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})