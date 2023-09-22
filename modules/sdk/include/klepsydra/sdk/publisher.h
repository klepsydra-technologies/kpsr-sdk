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

#ifndef PUBLISHER_SDK_H
#define PUBLISHER_SDK_H

#include <functional>
#include <memory>
#include <string>

#include <klepsydra/sdk/container.h>
#include <klepsydra/sdk/publication_stats.h>

namespace kpsr {

class PublisherBase
{
public:
    PublisherBase(Container *container, const std::string &name, const std::string &type);

    virtual ~PublisherBase();

    virtual void setContainer(Container *container);

    PublicationStats publicationStats;

    std::string name;

protected:
    Container *_container;
};

/*!
 * @brief The Publisher class
 *
 * @copyright Klepsydra Technologies AG 2023-2031.
 *
 * @ingroup kpsr-application
 *
 * @details Main publisher API. Applications using Klepsydra should use pointers to this class in order to publish event to either other classes (intra process) or to the middleware (inter process)
*/
template<class T>
class Publisher : public PublisherBase
{
public:
    /*!
     * @brief Publisher
     * @param container
     * @param name
     * @param type
     */
    Publisher(Container *container, const std::string &name, const std::string &type)
        : PublisherBase(container, name, type)
    {}

    virtual ~Publisher() {}

    /*!
     * @brief publish
     * @param event
     */
    void publish(const T &event)
    {
        publicationStats.startProcessMeasure();
        internalPublish(event);
        publicationStats.stopProcessMeasure();
    }

    /*!
     * @brief publish without copy
     * @param event
     */
    void publish(std::shared_ptr<const T> event)
    {
        publicationStats.startProcessMeasure();
        internalPublish(event);
        publicationStats.stopProcessMeasure();
    }

    /*!
     * @brief processAndPublish
     * @param process
     */
    virtual void processAndPublish(std::function<void(T &)> process) = 0;

protected:
    /*!
     * @brief internalPublish
     * @param event
      * Real implementation of the publishing method.
     */
    virtual void internalPublish(const T &event) = 0;

    /*!
     * @brief internalPublish
     * @param event
      * Real implementation of the publishing method.
     */
    virtual void internalPublish(std::shared_ptr<const T> event) = 0;
};
} // namespace kpsr
#endif
