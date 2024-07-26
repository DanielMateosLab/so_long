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

TEST_F(ExecutableTest, NoArgs) {
    std::string output = runExecutable("");
    EXPECT_NE(output.find(ARGC_ERR), std::string::npos);
}

TEST_F(ExecutableTest, TooManyArgs) {
    std::string output = runExecutable("arg1 arg2");
    EXPECT_NE(output.find(ARGC_ERR), std::string::npos);
}

TEST_F(ExecutableTest, InvalidExtension) {
    std::string output = runExecutable("invalid_extension.txt");
    EXPECT_NE(output.find(FILE_EXT_ERR), std::string::npos);
}

TEST_F(ExecutableTest, ReadMapError) {
    std::string output = runExecutable("non_existing_map_path.ber");
    EXPECT_NE(output.find(READ_MAP_ERR), std::string::npos);
}
