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

#ifndef MOCK_CONTAINER_SDK_H
#define MOCK_CONTAINER_SDK_H

#include "gmock/gmock.h"

#include <klepsydra/sdk/container.h>
#include <klepsydra/sdk/environment.h>
#include <klepsydra/sdk/publisher.h>
#include <klepsydra/sdk/service.h>

namespace kpsr {

class MockContainer : public Container
{
public:
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, attach, (Service * service), (override));
    MOCK_METHOD(void, detach, (Service * service), (override));
    MOCK_METHOD(void, attach, (FunctionStats * functionStats), (override));
    MOCK_METHOD(void, detach, (FunctionStats * functionStats), (override));
    MOCK_METHOD(void, attach, (ServiceStats * serviceStats), (override));
    MOCK_METHOD(void, attach, (PublicationStats * publicationStats), (override));
    MOCK_METHOD(void, detach, (PublicationStats * publicationStats), (override));
    MOCK_METHOD(void, attach, (SubscriptionStats * subscriptionStats), (override));
    MOCK_METHOD(void, detach, (SubscriptionStats * subscriptionStats), (override));
    MOCK_METHOD(std::string, getName, (), (const, override));
    MOCK_METHOD(kpsr::Environment *, getEnvironment, (), (const, override));
};

class MockEnvironment : public Environment
{
public:
    MOCK_METHOD(bool,
                getPropertyString,
                (const std::string &key,
                 std::string &value,
                 std::string const &defaultValue,
                 std::string const &rootNode),
                (override));
    MOCK_METHOD(
        bool,
        getPropertyInt,
        (const std::string &key, int &value, const int defaultValue, std::string const &rootNode),
        (override));
    MOCK_METHOD(bool,
                getPropertyFloat,
                (const std::string &key,
                 float &value,
                 const float defaultValue,
                 std::string const &rootNode),
                (override));
    MOCK_METHOD(
        bool,
        getPropertyBool,
        (const std::string &key, bool &value, const bool defaultValue, std::string const &rootNode),
        (override));
    MOCK_METHOD(void,
                setPropertyString,
                (const std::string &key, const std::string &value, std::string const &rootNode),
                (override));
    MOCK_METHOD(void,
                setPropertyInt,
                (const std::string &key, const int &value, std::string const &rootNode),
                (override));
    MOCK_METHOD(void,
                setPropertyFloat,
                (const std::string &key, const float &value, std::string const &rootNode),
                (override));
    MOCK_METHOD(void,
                setPropertyBool,
                (const std::string &key, const bool &value, std::string const &rootNode),
                (override));
    MOCK_METHOD(bool,
                loadFile,
                (const std::string &fileName, const std::string &nodeName),
                (override));
};

template<class T>
class MockPublisher : public Publisher<T>
{
public:
    MockPublisher(Container *container, const std::string &name, const std::string &type)
        : Publisher<T>(container, name, type)
    {}
    MOCK_METHOD(void, processAndPublish, (std::function<void(T &)> process), (override));
    MOCK_METHOD(void, internalPublish, (const T &event), (override));
    MOCK_METHOD(void, internalPublish, (std::shared_ptr<const T> event), (override));
};

class MockService : public Service
{
public:
    MockService(Container *container,
                Environment *environment,
                const std::string &serviceName,
                bool isMaster = true)
        : Service(container, environment, serviceName, isMaster)
    {}
    MOCK_METHOD((std::map<std::string, std::string>), getMetadata, (), (override));
    MOCK_METHOD(void, execute, (), (override));
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
};
} // namespace kpsr
#endif
