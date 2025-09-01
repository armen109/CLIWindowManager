#include "CLIWindowManager.h"

int main() {
    CommandRegistry registry;

    cout << "Available commands:\n";
    cout << "  add_window <id> <rowCount> <colCount> [parent row col]\n";
    cout << "  add_text <id> <text> <parentWindowId> <row> <col>\n";
    cout << "  add_table <id> <rowCount> <colCount> <parentWindowId> <row> <col>\n";
    cout << "  add_button <id> <text> <parentWindowId> <row> <col>\n";
    cout << "  printAll\n";
    cout << "  break\n\n";

    string line;
    while (true) {
        cout << "> ";
        getline(cin, line);
        if (line == "break") break;

        stringstream ss(line);
        string cmd;
        ss >> cmd;

        vector<string> args;
        string token;
        while (ss >> token) {
            args.push_back(token);
        }

        registry.executeCommand(cmd, args);
    }
    return 0;
}
