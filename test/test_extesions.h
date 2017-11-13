#ifndef TEST_EXTENSIONS
#define TEST_EXTENSIONS


#define EXPECT_VECTORS_EQ(vec1, vec2)		    				\
    EXPECT_NEAR((vec1).x(), (vec2).x(), utils::Vector2f::EPS); 	\
    EXPECT_NEAR((vec1).y(), (vec2).y(), utils::Vector2f::EPS);

#define EXPECT_VECTORS_NE(vec1, vec2)			\
    EXPECT_NE((vec1).x(), (vec2).x());			\
    EXPECT_NE((vec1).y(), (vec2).y());

#endif // TEST_EXTENSIONS
