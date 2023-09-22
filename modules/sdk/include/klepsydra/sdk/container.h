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

#ifndef CONTAINER_SDK_H
#define CONTAINER_SDK_H

#include <string>

#include <klepsydra/sdk/function_stats.h>
#include <klepsydra/sdk/publication_stats.h>
#include <klepsydra/sdk/service_stats.h>
#include <klepsydra/sdk/subscription_stats.h>

namespace kpsr {

class Service;
class Environment;

class ContainerImpl;
class Container
{
public:
    /**
     * @brief Container constructor
     * @param env to administer
     * @param applicationName to use as id of the process running these services.
     */
    Container() = default;

    virtual ~Container() = default;

    /**
     * @brief start all master services.
     */
    virtual void start() = 0;

    /**
     * @brief stop all services.
     */
    virtual void stop() = 0;

    /**
     * @brief attach a service and its statistics variable to the container
     * @param service Pointer to a service
     */
    virtual void attach(Service *service) = 0;

    /**
     * @brief detach
     * @param service Pointer to a service
     */
    virtual void detach(Service *service) = 0;

    /**
     * @brief attach a custom method statistics to the container
     * @param functionStats Pointer to a basic stat object.
     */
    virtual void attach(FunctionStats *functionStats) = 0;

    /**
     * @brief detach
     * @param functionStats
     */
    virtual void detach(FunctionStats *functionStats) = 0;

    /**
     * @brief attach a service statistics to the container
     * @param serviceStats Pointer to a service stats.
     */
    virtual void attach(ServiceStats *serviceStats) = 0;

    /**
     * @brief attach a publication statistics to the container
     * @param publicationStats Pointer to a publication stats.
     */
    virtual void attach(PublicationStats *publicationStats) = 0;

    /**
     * @brief detach a publication statistics to the container
     * @param publicationStats Pointer to a publication stats.
     */
    virtual void detach(PublicationStats *publicationStats) = 0;

    /**
     * @brief attach a subscription statistics to the container
     * @param subscriptionStats Pointer to a subscription stats.
     */
    virtual void attach(SubscriptionStats *subscriptionStats) = 0;

    /**
     * @brief detach
     * @param subscriptionStats
     */
    virtual void detach(SubscriptionStats *subscriptionStats) = 0;

    virtual std::string getName() const = 0;

    virtual kpsr::Environment *getEnvironment() const = 0;
};
} // namespace kpsr
#endif
