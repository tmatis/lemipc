#include <ft_test.h>
#include <strategy.h>

START_TEST(get_distance, "Test get_distance()")
{
    double distance = get_distance(0, 0, 0, 0);
    assert_equal(distance, 0);

    distance = get_distance(0, 0, 1, 0);
    assert_equal(distance, 1);
} END_TEST