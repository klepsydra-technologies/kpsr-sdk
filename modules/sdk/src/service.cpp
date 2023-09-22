/*
 * Copyright 2023 Klepsydra Technologies AG
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <klepsydra/sdk/container.h>
#include <klepsydra/sdk/service.h>

namespace kpsr {
Service::Service(Container *container,
                 Environment *environment,
                 const std::string &serviceName,
                 bool isMaster)
    : container(container)
    , environment(environment)
    , serviceStats(serviceName, container)
    , isMaster(isMaster)
    , started(false)
{
    if (container) {
        container->attach(&serviceStats);
    }
}

Service::~Service()
{
    if (container) {
        container->detach(&serviceStats);
    }
}

void Service::runOnce()
{
    if (started) {
        serviceStats.startProcessMeasure();
        execute();
        serviceStats.stopProcessMeasure();
    }
}

void Service::startup()
{
    if (started) {
        return;
    }
    started = true;

    serviceStats.startTimeWatch();

    start();
}

void Service::shutdown()
{
    if (!started) {
        return;
    }
    started = false;

    serviceStats.stopTimeWatch();

    stop();
}

std::map<std::string, std::string> Service::getMetadata()
{
    std::map<std::string, std::string> metadata;
    return metadata;
}
} // namespace kpsr
