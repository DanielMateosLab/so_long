#include "gtest/gtest.h"
#include <fstream>
#include <string>

extern "C" {
#include "so_long.h"
}

int map_length(char **map) {
	int length = 0;
	while (map[length] && map[length + 1])
		length++;
	return length;
}

char *path = "../../maps/42.ber";

class MapTest : public ::testing::Test {
protected:
	char **map;

	void SetUp() override {
		map = read_map(path);
	}

	void TearDown() override {
		ft_clear_str_arr(map);
	}
};

TEST_F(MapTest, read_map_ok) {
	ASSERT_NE(map, nullptr);
}

TEST_F(MapTest, read_length_ok) {
	ASSERT_EQ(map_length(map), 11);
}

TEST_F(MapTest, read_length_ko) {
	ASSERT_NE(map_length(map), 10);
}

TEST_F(MapTest, check_map_content) {
    std::ifstream file(path);
    ASSERT_TRUE(file.is_open()) << "Failed to open the file.";

    std::string line;
    int i = 0;
    while (std::getline(file, line)) {
        ASSERT_STREQ(map[i], line.c_str()) << "Mismatch on line " << i;
        i++;
    }

    file.close();
}

TEST(wrong_path, ok) {
	char *path = "wrong_path";
	ASSERT_EQ(read_map(path), nullptr);
}
