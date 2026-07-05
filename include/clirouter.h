#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

class CLIRouter {
public:
    using CommandCallback = std::function<void(const std::vector<std::string>&)>;

    // register commmand
    void reg_cmd (const std::string& cmd_name, CommandCallback callback) {
        commands[cmd_name] = callback;
    }

    // router
    void dispatch(int argc, char* argv[]) {
        if (argc < 2) {
            print_default_help();
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
            std::cout << "Error: Unknown command '" << cmd << "'\n";
            print_default_help();
        }
    }


private:
    std::map<std::string, CommandCallback> commands;

    void print_default_help() {
        std::cout << "Available commands:\n";
        for (const auto& pair : commands) {
            std::cout << "  - " << pair.first << "\n";
        }
    }
};
