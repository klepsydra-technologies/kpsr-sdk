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

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <functional>
#include <memory>
#include <string>

#include <klepsydra/sdk/container.h>
#include <klepsydra/sdk/subscription_stats.h>

namespace kpsr {

class SubscriberBase
{
public:
    SubscriberBase(Container *container, const std::string &name, const std::string &type);

    virtual ~SubscriberBase() = default;

    virtual void setContainer(Container *container);

    std::string name;
    std::string type;
    Container *container;
};

template<class T>
/*!
 * @brief The Subscriber class
 *
 * @copyright Klepsydra Technologies AG 2023-2031.
 *
 * @ingroup kpsr-application
 *
 * @details Subscriber interface. It keeps track of the listeners that registers for events coming from a middleware.
 */
class Subscriber : public SubscriberBase
{
public:
    /*!
     * @brief Subscriber
     * @param container
     * @param name
     * @param type
     */
    Subscriber(Container *container, const std::string &name, const std::string &type)
        : SubscriberBase(container, name, type)
    {}

    /*!
     * @brief registerListener registers an std::function to be invoked everything an event is received.
     * @param name with which the listener is registered.
     * @param listener function to be invoked for an event.
     */
    virtual void registerListener(const std::string &name,
                                  const std::function<void(const T &)> listener) = 0;

    /*!
     * @brief registerListenerOnce registers an std::function to be invoked when an event is received.
     * Once invoked this listeners is removed from the list of listeners.
     * @param listener function to be invoked for an event.
     */
    virtual void registerListenerOnce(const std::function<void(const T &)> listener) = 0;

    /*!
     * @brief registerSharedPtrListener registers an std::function to be invoked everything a shared pointer of an event is received.
     * @param name with which the listener is registered.
     * @param listener function to be invoked for an event.
     */
    virtual void registerSharedPtrListener(
        const std::string &name,
        const std::function<void(const std::shared_ptr<const T> &)> listener) = 0;

    /*!
     * @brief registerSharedPtrListenerOnce registers an std::function to be invoked when an event is received.
     * Once invoked this listeners is removed from the list of listeners.
     * @param listener function to be invoked for an event.
     */
    virtual void registerSharedPtrListenerOnce(
        const std::function<void(const std::shared_ptr<const T> &)> listener) = 0;

    /*!
     * @brief removeListener removes the listener from the list of active listeners.
     * @param name
     */
    virtual void removeListener(const std::string &name) = 0;

    /*!
     * @brief getSubscriptionStats retrieves the performance information of the listener.
     * @param name
     */
    virtual std::shared_ptr<SubscriptionStats> getSubscriptionStats(const std::string &name) = 0;
};
} // namespace kpsr
#endif
