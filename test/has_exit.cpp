#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <tuple>

extern "C" {
#include "so_long.h"
}

struct SaveBeginTestParams {
    const char* path;
    int expected_begin_x;
    int expected_begin_y;
};

class SaveBeginTest : public ::testing::TestWithParam<SaveBeginTestParams> {
protected:
	char **map;

	void SetUp() override {
		map = read_map(GetParam().path);
	}

	void TearDown() override {
		str_array_clear(map);
	}
};

TEST_P(SaveBeginTest, ReadMapOk) {
	const auto& params = GetParam();
	t_point	begin;

	ASSERT_NE(map, nullptr);
	save_begin(map, &begin);
	ASSERT_EQ(begin.x, params.expected_begin_x);
	ASSERT_EQ(begin.y, params.expected_begin_y);
}

INSTANTIATE_TEST_SUITE_P(
	SaveBeginTests,
	SaveBeginTest,
	::testing::Values(
		SaveBeginTestParams{"../../maps/42.ber", 1, 3},
		SaveBeginTestParams{"../../maps/map_2.ber", 1, 4}
	)
);
