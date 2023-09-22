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

#include <string>

#include <klepsydra/sdk/publisher.h>

#include "mock_classes.h"

namespace kpsr {

TEST(PublisherBaseTest, NominalTest)
{
    MockContainer container;

    EXPECT_CALL(container, attach(::testing::A<PublicationStats *>())).Times(1);
    EXPECT_CALL(container, detach(::testing::A<PublicationStats *>())).Times(1);

    {
        ASSERT_NO_THROW(PublisherBase publisherTest(&container, "testPublisher", "test"));
    }

    {
        ASSERT_NO_THROW(PublisherBase publisherNoContainerTest(nullptr, "testPublisher", "test"));
    }
}

TEST(PublisherTest, NominalTest)
{
    MockContainer container;
    EXPECT_CALL(container, attach(::testing::A<PublicationStats *>())).Times(1);
    EXPECT_CALL(container, detach(::testing::A<PublicationStats *>())).Times(1);

    using TestType = std::string;
    TestType dummyString = "Test message";
    MockPublisher<TestType> publisher(&container, "testPublisher", "test");

    EXPECT_CALL(publisher, internalPublish(dummyString)).Times(1);

    ASSERT_NO_THROW(publisher.publish(dummyString));

    EXPECT_GT(publisher.publicationStats.totalProcessed, 0);
    EXPECT_GT(publisher.publicationStats.totalProcessingTimeInNanoSecs, 0);
}

TEST(PublisherTest, NoContainerTest)
{
    using TestType = std::string;
    TestType dummyString = "Test message";

    MockPublisher<TestType> publisherNoContainer(nullptr, "testPubNoContainer", "test");
    EXPECT_CALL(publisherNoContainer, internalPublish(dummyString)).Times(1);

    ASSERT_NO_THROW(publisherNoContainer.publish(dummyString));

    EXPECT_GT(publisherNoContainer.publicationStats.totalProcessed, 0);
    EXPECT_EQ(publisherNoContainer.publicationStats.totalProcessingTimeInNanoSecs, 0);
}

TEST(PublisherTest, SetContainerTest)
{
    using TestType = std::string;
    TestType dummyString = "Test message";

    MockContainer container;
    EXPECT_CALL(container, attach(::testing::A<PublicationStats *>())).Times(0);

    MockPublisher<TestType> publisher(nullptr, "testPublisher", "test");
    EXPECT_CALL(publisher, internalPublish(dummyString)).Times(2);

    ASSERT_NO_THROW(publisher.publish(dummyString));

    EXPECT_GT(publisher.publicationStats.totalProcessed, 0);
    EXPECT_EQ(publisher.publicationStats.totalProcessingTimeInNanoSecs, 0);

    EXPECT_CALL(container, attach(::testing::A<PublicationStats *>())).Times(1);
    EXPECT_CALL(container, detach(::testing::A<PublicationStats *>())).Times(1);

    ASSERT_NO_THROW(publisher.setContainer(&container));

    ASSERT_NO_THROW(publisher.publish(dummyString));

    EXPECT_GT(publisher.publicationStats.totalProcessed, 1);
    EXPECT_GT(publisher.publicationStats.totalProcessingTimeInNanoSecs, 0);

    ASSERT_NO_THROW(publisher.setContainer(nullptr));
}

} // namespace kpsr
