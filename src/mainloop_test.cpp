#include "mainloop.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockEndpoint : public Endpoint {
public:
    MOCK_METHOD(int, write_msg, (const struct buffer *pbuf), (override));
    MOCK_METHOD(int, flush_pending_msgs, (), (override));
    MOCK_METHOD(ssize_t, _read_msg, (uint8_t * buf, size_t len), (override));
};

TEST(MainLoopTest, termination)
{
    Mainloop &mainloop = Mainloop::init();
    mainloop.open();
    mainloop.request_exit(0);
    int ret = mainloop.loop();
    EXPECT_EQ(0, ret);
    mainloop.teardown();
}

TEST(MainLoopTest, wrong_termination)
{
    Mainloop &mainloop = Mainloop::init();
    mainloop.open();
    mainloop.request_exit(-1);
    int ret = mainloop.loop();
    EXPECT_EQ(-1, ret);
    mainloop.teardown();
}
