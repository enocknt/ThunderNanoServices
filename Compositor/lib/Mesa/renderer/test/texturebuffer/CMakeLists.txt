# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2021 Metrological
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

add_library(PixelBuffer INTERFACE)
target_include_directories(PixelBuffer INTERFACE ${CMAKE_CURRENT_LIST_DIR})
add_library(PixelBuffer::PixelBuffer ALIAS PixelBuffer)

add_library(DmaBuffer INTERFACE)
target_include_directories(DmaBuffer INTERFACE ${CMAKE_CURRENT_LIST_DIR})
add_library(DmaBuffer::DmaBuffer ALIAS DmaBuffer)