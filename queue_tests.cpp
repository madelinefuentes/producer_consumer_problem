#include "../src/BoundedBuffer.h"
#include "../src/ProducerConsumer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>

//Test checking if bounded buffer is empty
TEST(PCTest, Test1) {
    BoundedBuffer *BB = new BoundedBuffer(5);
    EXPECT_TRUE(BB->isEmpty());

    delete BB;
}

//Test checking append() and remove() from buffer
TEST(PCTest, Test2){
    BoundedBuffer *BB = new BoundedBuffer(5);
    BB->append(0);
    ASSERT_EQ(0,BB->remove());

    delete BB;
}

//Test checking multiple calls to append() and remove()
TEST(PCTest, Test3){
    BoundedBuffer *BB = new BoundedBuffer(5);
    BB->append(2);
    BB->append(5);
    ASSERT_EQ(2,BB->remove());

    BB->append(1);
    BB->append(3);
    BB->append(4);

    ASSERT_EQ(5,BB->remove());
    ASSERT_EQ(1,BB->remove());

    delete BB;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}