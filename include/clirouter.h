#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

class CLIRouter {
public:
    using CommandCallback = std::function<void(const std::vector<std::string>&)>;
    using ErrorCallback = std::function<void(const std::string&)>;

    // register commmand
    void reg_cmd (const std::string& cmd_name, CommandCallback callback) {
        commands[cmd_name] = callback;
    }

    // register error
    void set_error_handler(ErrorCallback handler) {
        error_handler = handler;
    }

    // router
    void dispatch(int argc, char* argv[]) {
        if (argc < 2) {
            handle_error("No command provided.");
            return;
        }

        std::string cmd = argv[1];

        std::vector<std::string> args;
        for (int i = 2; i < argc; ++i) {
            args.push_back(argv[i]);
        }

        auto it = commands.find(cmd);
        if (it != commands.end()) {
            it->second(args);
        } else {
            handle_error("Unknown command: " + cmd);
        }
    }


private:
    std::map<std::string, CommandCallback> commands;
    ErrorCallback error_handler = nullptr;

    void handle_error(const std::string& error_msg) {
        if (error_handler) {
            error_handler(error_msg);
        } else {
            std::cerr << "Error: " << error_msg << "\n\n";
            print_default_help();
        }
    }

    void print_default_help() {
        std::cout << "Available commands:\n";
        for (const auto& pair : commands) {
            std::cout << "  - " << pair.first << "\n";
        }
    }
};
