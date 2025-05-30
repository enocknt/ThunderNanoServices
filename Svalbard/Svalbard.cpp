/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 Metrological
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Svalbard.h"

namespace Thunder {
namespace Plugin {

    namespace {

        static Metadata<Svalbard> metadata(
            // Version
            1, 0, 0,
            // Preconditions
            { subsystem::PLATFORM, subsystem::PROVISIONING },
            // Terminations
            {},
            // Controls
            { subsystem::CRYPTOGRAPHY }
        );
    }

    const string Svalbard::Initialize(PluginHost::IShell* service) /* override */
    {
        string message;

        ASSERT(service != nullptr);
        ASSERT(_service == nullptr);
        ASSERT(_svalbard == nullptr);
        ASSERT(_connectionId == 0);

        _service = service;
        _service->AddRef();

        _service->Register(&_notification);
        _svalbard = _service->Root<Exchange::IConfiguration>(_connectionId, Core::infinite, _T("CryptographyImplementation"));

        if (_svalbard == nullptr) {
            message = _T("Svalbard could not be instantiated.");
        }
        else {
            if (_svalbard->Configure(_service) == Core::ERROR_NONE) {
                PluginHost::ISubSystem* const subSystems = service->SubSystems();
                ASSERT(subSystems != nullptr);

                if (subSystems != nullptr) {
                    subSystems->Set(PluginHost::ISubSystem::CRYPTOGRAPHY, nullptr);
                    subSystems->Release();
                }
            }
        }

        return message;
    }

    void Svalbard::Deinitialize(PluginHost::IShell* service) /* override */
    {
        ASSERT(service != nullptr);

        if (_service != nullptr) {
            ASSERT(_service == service);

            _service->Unregister(&_notification);

            if (_svalbard != nullptr) {
                RPC::IRemoteConnection* connection(_service->RemoteConnection(_connectionId));

                VARIABLE_IS_NOT_USED uint32_t result = _svalbard->Release();
                _svalbard = nullptr;
                ASSERT( (result == Core::ERROR_CONNECTION_CLOSED) || (result == Core::ERROR_DESTRUCTION_SUCCEEDED));

                if (connection != nullptr) {
                    TRACE(Trace::Error, (_T("Svalbard is not properly destructed. %d"), _connectionId));

                    connection->Terminate();
                    connection->Release();
                }
            }

            _connectionId = 0;
            _service->Release();
            _service = nullptr;
        }
    }

    string Svalbard::Information() const /* override */
    {
        return string();
    }

    void Svalbard::Deactivated(RPC::IRemoteConnection* connection)
    {
        if (connection->Id() == _connectionId) {

            ASSERT(_service != nullptr);

            Core::IWorkerPool::Instance().Submit(PluginHost::IShell::Job::Create(_service,
                PluginHost::IShell::DEACTIVATED,
                PluginHost::IShell::FAILURE));
        }
    }

} // namespace Plugin
} // namespace
