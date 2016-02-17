#define MOVE_TEST(cl, obj, getmethod, nullval) { \
	auto ptr = obj.getmethod(); \
	EXPECT_TRUE(ptr != nullval); \
	\
	cl obj1(std::move(obj)); \
	EXPECT_EQUAL(obj1.getmethod(), ptr); \
	EXPECT_TRUE(obj.getmethod() == nullval); \
	\
	std::swap(obj, obj1); \
	EXPECT_EQUAL(obj.getmethod(), ptr); \
	EXPECT_TRUE(obj1.getmethod() == nullval); \
	\
	cl& obj_ref = obj;  \
	obj = std::move(obj_ref);  \
	EXPECT_EQUAL(obj.getmethod(), ptr); \
}
