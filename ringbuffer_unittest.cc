#include "ringbuffer.h"
#include "gtest/gtest.h"
#include <stdio.h>

RINGBUFFER_EXTERN(rb)
RINGBUFFER_NEW(rb, 20)

#define LOOP_NUM 20

TEST(RingBufferTest, INIT)
{
	EXPECT_EQ(0, rb.buffer[8]);

	EXPECT_EQ(20, rb.size);
	EXPECT_EQ(0, rb.fill);

//	EXPECT_TRUE(NULL == rb.read);
//	EXPECT_TRUE(NULL == rb.write);

	EXPECT_TRUE(rb.write == rb.read);
	EXPECT_TRUE(rb.buffer == rb.read);
}

TEST(RingBufferTest, ReadWrite)
{
	unsigned char buf[8*LOOP_NUM], buf1[10];
	for (int i=0; i<8*LOOP_NUM; i++)
		buf[i] = i+1;

	int bytesWritten = 0;
	unsigned char* p = buf;

	for (int i=0; i<LOOP_NUM; i++)
	{
		bytesWritten = ringbuffer_write(&rb, p, 8);
		memset(buf1, 0x0, 10);
		int bytesRead = ringbuffer_read(&rb, buf1, 10);
		if (bytesRead) {
			for (int i=0; i<10; i++)
				printf("buf1[%d] = %d\n", i, buf1[i]);
		}
		p += bytesWritten;
	}

	for (int i=0; i<20; i++)
		printf("ringbuffer[%d] = %d\n", i, rb.buffer[i]);

}
