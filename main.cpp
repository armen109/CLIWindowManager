#include "CLIWindowManager.h"

int main() {
    WindowManager wm;

    cout << "Available commands:\n";
    cout << "  add_window <id> <rowCount> <colCount> [parentWindowId=-1] [row=-1] [col=-1]\n";
    cout << "  add_text <id> <text> <parentWindowId> <row> <col>\n";
    cout << "  add_table <id> <rowCount> <colCount> <parentWindowId> <row> <col>\n";
    cout << "  add_button <id> <text> <parentWindowId> <row> <col>\n";
    cout << "  printAll\n";
    cout << "  break\n\n";

    string cmd;
    while (true) {
        cout << "> ";
        cin >> cmd;

        if (cmd == "break") {
            break;
        } 
        else if (cmd == "add_window") {
            int id, rows, cols, parent=-1, row=-1, col=-1;
            cin >> id >> rows >> cols;
            if (cin.peek() != '\n') cin >> parent >> row >> col;
            wm.addWindow(id, rows, cols, parent, row, col);
        }
        else if (cmd == "add_table") {
            int id, rows, cols, parent, row, col;
            cin >> id >> rows >> cols >> parent >> row >> col;
            wm.addTable(id, rows, cols, parent, row, col);
        }
        else if (cmd == "add_text") {
            int id, parent, row, col;
            string text;
            cin >> id;
            cin.ignore();
            getline(cin, text, '"'); 
            getline(cin, text, '"'); 
            cin >> parent >> row >> col;
            wm.addText(id, text, parent, row, col);
        }
        else if (cmd == "add_button") {
            int id, parent, row, col;
            string text;
            cin >> id;
            cin.ignore();
            getline(cin, text, '"');
            getline(cin, text, '"');
            cin >> parent >> row >> col;
            wm.addButton(id, text, parent, row, col);
        }
        else if (cmd == "printAll") {
            wm.printAll();
        }
        else {
            cout << "Unknown command.\n";
        }
    }

    return 0;
}
