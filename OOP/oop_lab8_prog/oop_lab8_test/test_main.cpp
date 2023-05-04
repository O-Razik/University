#include "mock_class.h"

#pragma comment (linker, "/HEAP:1")

TEST(CQueue, DynemicError)
{
	CQueue* queue = nullptr;
	EXPECT_THROW({
		queue = new CQueue[200000000000000000] {1.0};
		}, std::bad_alloc);
}

#pragma comment (linker, "/HEAP:1000000000000000000000000")

TEST(CQueue, DynemicNoError)
{
	CQueue* queue = nullptr;
	EXPECT_NO_THROW({
		queue = new CQueue[2];
		});
}

TEST(CQueue, EmptyTest)
{

	EXPECT_NO_THROW(MOCK_CQueue::MOCK_CQueue());
	MOCK_CQueue* mock_queue = new MOCK_CQueue;

	EXPECT_CALL((*mock_queue), QueueIsEmpty()).WillOnce(testing::Return(1));
	EXPECT_TRUE(mock_queue->QueueIsEmpty());

	EXPECT_CALL((*mock_queue), QueueSize()).WillOnce(testing::Return(0));
	EXPECT_EQ(mock_queue->QueueSize(), 0);


	EXPECT_CALL((*mock_queue), QueueMax()).WillOnce(testing::Throw(queue_err_sizeZero()));
	EXPECT_THROW((*mock_queue).QueueMax(), queue_err_sizeZero);

	EXPECT_CALL((*mock_queue), QueueMin()).WillOnce(testing::Throw(queue_err_sizeZero()));
	EXPECT_THROW((*mock_queue).QueueMin(), queue_err_sizeZero);

	EXPECT_CALL((*mock_queue), QueueAver()).WillOnce(testing::Throw(queue_err_sizeZero()));
	EXPECT_THROW((*mock_queue).QueueAver(), queue_err_sizeZero);

	EXPECT_CALL(*mock_queue, add(testing::_));
	EXPECT_NO_THROW(*mock_queue + 1.0);

	EXPECT_CALL((*mock_queue), QueueIsEmpty()).WillOnce(testing::Return(0));
	EXPECT_FALSE(mock_queue->QueueIsEmpty());

	EXPECT_CALL((*mock_queue), QueueSize()).WillOnce(testing::Return(1));
	EXPECT_EQ(mock_queue->QueueSize(), 1);

	EXPECT_CALL((*mock_queue), QueueMax()).Times(1);
	EXPECT_NO_THROW((*mock_queue).QueueMax());

	EXPECT_CALL((*mock_queue), QueueMin()).Times(1);
	EXPECT_NO_THROW((*mock_queue).QueueMin());

	EXPECT_CALL((*mock_queue), QueueAver()).Times(1);
	EXPECT_NO_THROW((*mock_queue).QueueAver());

	delete mock_queue;
}

TEST(CQueue, AddRemoveSizeTest) {
	EXPECT_THROW(MOCK_CQueue::MOCK_CQueue(NAN), std::exception);
	MOCK_CQueue* mock_queue = new MOCK_CQueue(5.0);


	EXPECT_CALL((*mock_queue), QueueSize()).WillOnce(testing::Return(1));
	EXPECT_EQ(mock_queue->QueueSize(), 1);

	EXPECT_CALL((*mock_queue), add(testing::_)).Times(2);
	(*mock_queue) + 10.0;
	(*mock_queue) + 15.0;

	EXPECT_CALL((*mock_queue), QueueSize()).WillOnce(testing::Return(3));
	EXPECT_EQ(mock_queue->QueueSize(), 3);

	EXPECT_CALL((*mock_queue), QueueMax()).WillOnce(testing::Return(15));
	EXPECT_DOUBLE_EQ((*mock_queue).QueueMax(), 15);

	EXPECT_CALL((*mock_queue), QueueMin()).WillOnce(testing::Return(5));
	EXPECT_DOUBLE_EQ((*mock_queue).QueueMin(), 5);

	EXPECT_CALL((*mock_queue), QueueAver()).WillOnce(testing::Return(10));
	EXPECT_DOUBLE_EQ((*mock_queue).QueueAver(), 10);

	EXPECT_CALL((*mock_queue), min(testing::_)).Times(1);
	(*mock_queue) - 3;
	EXPECT_CALL((*mock_queue), QueueSize()).Times(1);
	EXPECT_EQ(mock_queue->QueueSize(), 0);

	EXPECT_CALL((*mock_queue), QueueMax()).WillOnce(testing::Throw(queue_err_sizeZero()));
	EXPECT_THROW((*mock_queue).QueueMax(), queue_err_sizeZero);

	EXPECT_CALL((*mock_queue), QueueMin()).WillOnce(testing::Throw(queue_err_sizeZero()));
	EXPECT_THROW((*mock_queue).QueueMin(), queue_err_sizeZero);

	EXPECT_CALL((*mock_queue), QueueAver()).WillOnce(testing::Throw(queue_err_sizeZero()));
	EXPECT_THROW((*mock_queue).QueueAver(), queue_err_sizeZero);

	delete mock_queue;
}

TEST(CQueue, ScalarMultiplication) {
	MOCK_CQueue* mock_queue = new MOCK_CQueue();

	EXPECT_CALL((*mock_queue), add(testing::_)).Times(3);
	(*mock_queue) + 5.0;
	(*mock_queue) + 10.0;
	(*mock_queue) + 15.0;

	EXPECT_CALL((*mock_queue), multip(testing::_)).Times(1);
	(*mock_queue) * 2.0;

	EXPECT_CALL((*mock_queue), QueueMax()).WillOnce(testing::Return(30));
	EXPECT_DOUBLE_EQ((*mock_queue).QueueMax(), 30);

	EXPECT_CALL((*mock_queue), QueueMin()).WillOnce(testing::Return(10));
	EXPECT_DOUBLE_EQ((*mock_queue).QueueMin(), 10);

	EXPECT_CALL((*mock_queue), QueueAver()).WillOnce(testing::Return(20));
	EXPECT_DOUBLE_EQ((*mock_queue).QueueAver(), 20);

	EXPECT_CALL((*mock_queue), min(testing::_)).Times(1);
	(*mock_queue) - 1;

	EXPECT_CALL((*mock_queue), QueueMax()).WillOnce(testing::Return(30));
	EXPECT_DOUBLE_EQ((*mock_queue).QueueMax(), 30);

	EXPECT_CALL((*mock_queue), QueueMin()).WillOnce(testing::Return(20));
	EXPECT_DOUBLE_EQ((*mock_queue).QueueMin(), 20);

	EXPECT_CALL((*mock_queue), QueueAver()).WillOnce(testing::Return(25));
	EXPECT_DOUBLE_EQ((*mock_queue).QueueAver(), 25);

	EXPECT_CALL((*mock_queue), multip(testing::_)).WillOnce(testing::Throw(std::exception()));
	EXPECT_THROW(((*mock_queue) * NAN), std::exception);

	delete mock_queue;
}

TEST(CQueue, CopyConstructor) {
	CQueue* queue1 = new CQueue(7.0);
	*queue1 + 11.0;
	*queue1 + 3.0;

	CQueue* queue2 = new CQueue(*queue1);
	EXPECT_EQ(queue2->QueueSize(), (*queue1).QueueSize());
	EXPECT_EQ(queue2->QueueAver(), (*queue1).QueueAver());

	EXPECT_EQ(queue2->QueueMax(), (*queue1).QueueMax());
	EXPECT_EQ(queue2->QueueMin(), (*queue1).QueueMin());
}

TEST(CQueue, CopyAssignment) {
	CQueue* queue1 = new CQueue(7.0);
	*queue1 + 11.0;
	*queue1 + 3.0;

	CQueue* queue2 = new CQueue;
	*queue2 = *queue1;
	EXPECT_EQ((*queue2).QueueSize(), queue1->QueueSize());
	EXPECT_EQ((*queue2).QueueAver(), queue1->QueueAver());

	EXPECT_EQ((*queue2).QueueMax(), queue1->QueueMax());
	EXPECT_EQ((*queue2).QueueMin(), queue1->QueueMin());
}

TEST(CQueueTest, MoveConstructor) {
	CQueue* queue1 = new CQueue(7.0);
	*queue1 + 11.0;
	*queue1 + 3.0;
	CQueue* queue2 = new CQueue(move(*queue1));

	EXPECT_EQ(queue1->QueueSize(), 0.0);
	EXPECT_EQ(queue2->QueueSize(), 3.0);
	EXPECT_DOUBLE_EQ(queue2->getFirst(), 7.0);
	EXPECT_DOUBLE_EQ(queue2->getLast(), 3.0);
}

TEST(CQueueTest, MoveAssignment) {
	CQueue* queue1 = new CQueue(7.0);
	*queue1 + 11.0;
	*queue1 + 3.0;
	CQueue* queue2 = new CQueue;
	*queue2 = move(*queue1);

	EXPECT_EQ(queue1->QueueSize(), 0.0);
	EXPECT_EQ(queue2->QueueSize(), 3.0);
	EXPECT_DOUBLE_EQ(queue2->getFirst(), 7.0);
	EXPECT_DOUBLE_EQ(queue2->getLast(), 3.0);

}

TEST(CQueue, InputWorkstTest) {
	CQueue* queue = new CQueue;
	istringstream input("1.0 2.0 3.0");
	input >> *queue;
	EXPECT_EQ(queue->QueueSize(), 3);
	EXPECT_DOUBLE_EQ(queue->getFirst(), 1.0);
	EXPECT_DOUBLE_EQ(queue->getLast(), 3.0);

	input = istringstream();
	EXPECT_THROW((input >> (*queue)), std::exception);
}

TEST(CQueue, OutputWorksTest) {
	CQueue* queue = new CQueue;
	ostringstream output;
	EXPECT_THROW(output << *queue, std::exception);

	*queue + 1.0;
	*queue + 2.0;
	*queue + 3.0;
	
	output << *queue;
	EXPECT_EQ(output.str(), "1 2 3 ");
	output.clear();
}

TEST(CQueueTest, ExceptionTest) {

	MOCK_CQueue mockQueue;

	EXPECT_CALL(mockQueue, QueueMax()).WillOnce(testing::Throw(queue_err_sizeZero()));
	EXPECT_THROW(mockQueue.QueueMax(), queue_err_sizeZero);

	EXPECT_CALL(mockQueue, QueueMin()).WillOnce(testing::Throw(queue_err_sizeZero()));
	EXPECT_THROW(mockQueue.QueueMin(), queue_err_sizeZero);

	EXPECT_CALL(mockQueue, QueueAver()).WillOnce(testing::Throw(queue_err_sizeZero()));
	EXPECT_THROW(mockQueue.QueueAver(), queue_err_sizeZero);

	EXPECT_CALL(mockQueue, add(testing::_))
		.WillOnce(testing::Throw(std::exception("Error: add failed.")));
	EXPECT_THROW(mockQueue + 1, std::exception);

	EXPECT_CALL(mockQueue, multip(testing::_))
		.WillOnce(testing::Throw(std::exception("Error: multip failed.")));
	EXPECT_THROW(mockQueue * 2.0, std::exception);

	istringstream input("");
	EXPECT_CALL(mockQueue, inWrapper(testing::_, testing::_))
		.WillOnce(testing::Throw(std::exception("Error: Failed to read input from stream.")));
	EXPECT_THROW(mockQueue.inWrapper(input,mockQueue) , std::exception);

}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}