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

#ifndef SERVICE_H
#define SERVICE_H

#include <atomic>
#include <map>

#include <klepsydra/sdk/environment.h>
#include <klepsydra/sdk/service_stats.h>

namespace kpsr {
class Container;

/*!
 * @brief The Service class
 *
 * @copyright Klepsydra Technologies AG 2023-2031.
 *
 * @ingroup kpsr-application
 *
 * @details Service Interface. Custumer applications using Klepsydra that need remote administration, access to
 * configuration perform regular task, etc should implement this interface.
 *
 * The only pure virtual methods to implement are start, stop and execute.
 * Master services start running as soon as the application is _started and should not implement the start method.
 * There are some stat gathering helper functions that are used within the container interface.
 */
class Service
{
public:
    /*!
     * @brief Service
     * @param container
     * @param environment
     * @param serviceName
     * @param isMaster
     */
    Service(Container *container,
            Environment *environment,
            const std::string &serviceName,
            bool isMaster = true);

    virtual ~Service();
    /*!
     * @brief runOnce
     *
     * This public method is used to invoke the custom service execute method.
     * Usually this method is invoked within a main application. E.g., in the Ros world, this will be invoked within
     * the runOnce of Ros.
     */
    void runOnce();

    /*!
     * @brief startup
     *
     * This public method is used to invoke the custom service start method.
     * Usually this method is invoked within a main application.
     */
    void startup();

    /*!
     * @brief shutdown
     *
     * This public method is used to invoke the custom service stop method.
     * Usually this method is invoked within a main application.
     */
    void shutdown();

    /*!
     * @brief getMetadata
     *
     * This method is intented to be used from the container. It provides metadata related to the service including status,
     * running time, etc.
     *
     * @return
     */
    virtual std::map<std::string, std::string> getMetadata();

    /*!
     * @brief container
     */
    Container *container;

    /*!
     * @brief environment
     */
    Environment *environment;

    /*!
     * @brief serviceStats
     */
    ServiceStats serviceStats;

    /*!
     * @brief isMaster
     */
    bool isMaster;

    /*!
     * @brief started
     */
    std::atomic<bool> started;

protected:
    virtual void execute() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};
} // namespace kpsr
#endif
