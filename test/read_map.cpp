#include "gtest/gtest.h"

extern "C" {
#include "so_long.h"
}

int map_length(char **map) {
	int length = 0;
	while (map[length] && map[length + 1])
		length++;
	return length;
}

TEST(read_length, ok) {
	char path[] = "../../maps/42.ber";
	char **map = read_map(path);
	ASSERT_NE(map, nullptr);
	ASSERT_EQ(map_length(map), 11);
}

TEST(read_length, ko) {
	char path[] = "../../maps/42.ber";
	char **map = read_map(path);
	ASSERT_NE(map, nullptr);
	ASSERT_NE(map_length(map), 10);
}
