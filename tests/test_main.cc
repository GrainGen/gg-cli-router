#include "ggclirouter.h"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#define TEST_PASS() std::cout << "  \033[1;32m[PASS]\033[0m " << __func__ << "\n"

// success
void test_successful_routing() {
    CLIRouter router;
    bool command_executed = false;
    std::vector<std::string> captured_args;

    router.reg_cmd("test-cmd", [&](const auto& args){
            command_executed = true;
            captured_args = args;
    });

    char* mock_argv[] = { (char*)"f2l", (char*)"test-cmd", (char*)"arg1", (char*)"arg2" };
    int mock_argc = 4;

    router.dispatch(mock_argc, mock_argv);

    assert(command_executed == true);
    assert(captured_args.size() == 2);
    assert(captured_args[0] == "arg1");
    assert(captured_args[1] == "arg2");

    TEST_PASS();
}

// unknow command
void test_unknown_command_handling() {
    CLIRouter router;
    bool error_triggered = false;
    std::string captured_error_msg = "";

    router.set_error_handler([&](const std::string& error_msg) {
            error_triggered = true;
            captured_error_msg = error_msg;
            });

    char* mock_argv[] = { (char*)"f2l", (char*)"typooo" };
    int mock_argc = 2;

    router.dispatch(mock_argc, mock_argv);

    assert(error_triggered == true);
    assert(captured_error_msg == "Unknown command: typooo");

    TEST_PASS();
}
// empty arguments
void test_empty_arguments() {
    CLIRouter router;
    bool error_triggered = false;

    router.set_error_handler([&](const std::string& error_msg) {
            error_triggered = true;
            });

    char* mock_argv[] = { (char*)"f2l" };
    int mock_argc = 1;

    router.dispatch(mock_argc, mock_argv);

    assert(error_triggered == true);
    TEST_PASS();
}

int main() {
    std::cout << "[cli_router] Running automated unit tests...\n";
    std::cout << "--------------------------------------------\n";

    test_successful_routing();
    test_unknown_command_handling();
    test_empty_arguments();

    std::cout << "--------------------------------------------\n";
    std::cout << "\033[1;32mAll tests completed successfully!\033[0m\n";
}


