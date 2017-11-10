#ifndef TEST_EXTENSIONS
#define TEST_EXTENSIONS

#define EPS 0.0001f

#define EXPECT_VECTORS_EQ(vec1, vec2)		    \
    EXPECT_FLOAT_EQ((vec1).x(), (vec2).x()); 	\
    EXPECT_FLOAT_EQ((vec1).y(), (vec2).y());

#define EXPECT_VECTORS_NE(vec1, vec2)			\
    EXPECT_NE((vec1).x(), (vec2).x());			\
    EXPECT_NE((vec1).y(), (vec2).y());

#endif // TEST_EXTENSIONS
