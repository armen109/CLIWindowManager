#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class WindowBase {
public:
    string type;
    int id;
    int rowCount;
    int colCount;
    int parentId;
    int rowPos;
    int colPos;
    vector<int> objects;

    WindowBase(string t, int i, int r, int c, int parent=-1, int row=-1, int col=-1)
        : type(t), id(i), rowCount(r), colCount(c),
          parentId(parent), rowPos(row), colPos(col) {}

    virtual ~WindowBase() {}

    virtual void print(int indent = 0) const = 0;
};

class Window : public WindowBase {
public:
    Window(int id, int r, int c, int parent=-1, int row=-1, int col=-1)
        : WindowBase("window", id, r, c, parent, row, col) {}

    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "Window(id=" << id
             << ", size=" << rowCount << "x" << colCount << ")\n";
    }
};

class Table : public WindowBase {
public:
    Table(int id, int r, int c, int parent, int row, int col)
        : WindowBase("table", id, r, c, parent, row, col) {}

    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "Table(id=" << id
             << ", size=" << rowCount << "x" << colCount
             << ", pos=" << rowPos << "," << colPos << ")\n";
    }
};

class Text : public WindowBase {
public:
    string text;
    Text(int id, const string& txt, int parent, int row, int col)
        : WindowBase("text", id, 0, 0, parent, row, col), text(txt) {}

    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "Text(id=" << id
             << ", pos=" << rowPos << "," << colPos
             << ", text=\"" << text << "\")\n";
    }
};

class Button : public WindowBase {
public:
    string text;
    Button(int id, const string& txt, int parent, int row, int col)
        : WindowBase("button", id, 0, 0, parent, row, col), text(txt) {}

    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "Button(id=" << id
             << ", pos=" << rowPos << "," << colPos
             << ", text=\"" << text << "\")\n";
    }
};

class WindowManager {
    unordered_map<int, WindowBase*> allObjects;

public:
~WindowManager() {
        for (auto it = allObjects.begin(); it != allObjects.end(); ++it) {
            delete it->second; 
        }
    }

    bool positionFree(int parentId, int row, int col) {
        for (int childId : allObjects[parentId]->objects) {
            WindowBase* child = allObjects[childId];
            if (child->rowPos == row && child->colPos == col) {
                return false;
            }
        }
        return true;
    }

    bool isWindow(int id) {
        return allObjects.count(id) && allObjects[id]->type == "window";
    }

    void addWindow(int id, int rows, int cols, int parent=-1, int row=-1, int col=-1) {
        if (parent != -1) {
            if (!isWindow(parent)) {
                cerr << "Error: Parent must be a window.\n";
                return;
            }
            if (row >= allObjects[parent]->rowCount || col >= allObjects[parent]->colCount) {
                cerr << "Error: Child position out of bounds.\n";
                return;
            }
            if (!positionFree(parent, row, col)) {
                cerr << "Error: Position already occupied.\n";
                return;
            }
        }
        Window* w = new Window(id, rows, cols, parent, row, col);
        allObjects[id] = w;
        if (parent != -1) allObjects[parent]->objects.push_back(id);
    }

    void addTable(int id, int rows, int cols, int parent, int row, int col) {
        if (!isWindow(parent)) {
            cerr << "Error: Parent must be a window.\n";
            return;
        }
        if (row >= allObjects[parent]->rowCount || col >= allObjects[parent]->colCount) {
            cerr << "Error: Child position out of bounds.\n";
            return;
        }
        if (!positionFree(parent, row, col)) {
            cerr << "Error: Position already occupied.\n";
            return;
        }
        Table* t = new Table(id, rows, cols, parent, row, col);
        allObjects[id] = t;
        allObjects[parent]->objects.push_back(id);
    }

    void addText(int id, const string& text, int parent, int row, int col) {
        if (!isWindow(parent)) {
            cerr << "Error: Parent must be a window.\n";
            return;
        }
        if (row >= allObjects[parent]->rowCount || col >= allObjects[parent]->colCount) {
            cerr << "Error: Child position out of bounds.\n";
            return;
        }
        if (!positionFree(parent, row, col)) {
            cerr << "Error: Position already occupied.\n";
            return;
        }
        Text* t = new Text(id, text, parent, row, col);
        allObjects[id] = t;
        allObjects[parent]->objects.push_back(id);
    }

    void addButton(int id, const string& text, int parent, int row, int col) {
        if (!isWindow(parent)) {
            cerr << "Error: Parent must be a window.\n";
            return;
        }
        if (row >= allObjects[parent]->rowCount || col >= allObjects[parent]->colCount) {
            cerr << "Error: Child position out of bounds.\n";
            return;
        }
        if (!positionFree(parent, row, col)) {
            cerr << "Error: Position already occupied.\n";
            return;
        }
        Button* b = new Button(id, text, parent, row, col);
        allObjects[id] = b;
        allObjects[parent]->objects.push_back(id);
    }

    void printAll(int rootId = -1, int indent = 0) {
    if (rootId == -1) {
        for (auto it = allObjects.begin(); it != allObjects.end(); ++it) {
            if (it->second->parentId == -1) {
                printAll(it->first, indent);
            }
        }
    } else {
        WindowBase* obj = allObjects[rootId];
        cout << string(indent, ' ')
             << "Type: " << obj->type
             << ", ID: " << obj->id
             << ", Parent ID: " << obj->parentId
             << ", RowPos: " << obj->rowPos
             << ", ColPos: " << obj->colPos
             << ", RowCount: " << obj->rowCount
             << ", ColCount: " << obj->colCount
             << endl;

        for (int childId : obj->objects) {
            printAll(childId, indent + 4);
        }
    }
}
};
