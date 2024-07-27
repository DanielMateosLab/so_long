#include "gtest/gtest.h"
#include <string>
#include <array>
#include <cstdio>
#include <memory>

extern "C" {
#include "so_long.h"
}

// Helper function to run a command and capture its output
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

class ExecutableTest : public ::testing::Test {
protected:
    std::string exec_path = "../../so_long";

    std::string runExecutable(const std::string& args) {
        std::string command = exec_path + " " + args;
        return exec(command.c_str());
    }
};

#define ASSERT_CONTAINS(haystack, needle) \
    EXPECT_NE(haystack.find(needle), std::string::npos) \
        << "Expected to find '" << needle << "' in:\n" << haystack

TEST_F(ExecutableTest, NoArgs) {
    std::string output = runExecutable("");
    ASSERT_CONTAINS(output, ARGC_ERR);
}

TEST_F(ExecutableTest, TooManyArgs) {
    std::string output = runExecutable("arg1 arg2");
    ASSERT_CONTAINS(output, ARGC_ERR);
}

TEST_F(ExecutableTest, InvalidExtension) {
    std::string output = runExecutable("invalid_extension.txt");
    ASSERT_CONTAINS(output, FILE_EXT_ERR);
}

TEST_F(ExecutableTest, PathErr) {
    std::string output = runExecutable("non_existing_map_path.ber");
    ASSERT_CONTAINS(output, PATH_ERR);
}

TEST_F(ExecutableTest, EmptyMap) {
	std::string output = runExecutable("../../maps/empty.ber");
	ASSERT_CONTAINS(output, EMPTY_MAP_ERR);
}

TEST_F(ExecutableTest, NotRectangleMap) {
	std::string output = runExecutable("../../maps/not_rectangle.ber");
	ASSERT_CONTAINS(output, RECT_MAP_ERR);
}

TEST_F(ExecutableTest, ForbiddenComponent) {
	std::string output = runExecutable("../../maps/forbidden_component.ber");
	ASSERT_CONTAINS(output, COMPONENTS_ERR);
}

TEST_F(ExecutableTest, NotSurroundedByWalls1) {
	std::string output = runExecutable("../../maps/not_surrounded_by_walls_1.ber");
	ASSERT_CONTAINS(output, WALL_ERR);
}

TEST_F(ExecutableTest, NotSurroundedByWalls2) {
	std::string output = runExecutable("../../maps/not_surrounded_by_walls_2.ber");
	ASSERT_CONTAINS(output, WALL_ERR);
}
