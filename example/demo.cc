#include "ggclirouter.h"
#include <iostream>
#include <string>
#include <vector>

void do_fetch(const std::vector<std::string>& args) {
    if (args.size() < 2) return;
    std::cout << "[f2l Fetch] Platform: " << args[0] << ", ID: " << args[1] << "\n";
}

void do_judge(const std::vector<std::string>& args) {
    std::cout << "[f2l Judge] Running local tests...\n";
}

int main(int argc, char* argv[]) {
    CLIRouter router;

    router.reg_cmd("fetch", do_fetch);
    router.reg_cmd("judge", do_judge);
    router.reg_cmd("version", [](const auto& args) {
            std::cout << "f2l version 0.1 (Codename: Dawu)\n";
            });

    router.dispatch(argc, argv);

    return 0;
}
