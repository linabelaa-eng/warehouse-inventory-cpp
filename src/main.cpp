#include "../include/WarehouseSystem.h"
#include <iostream>
#include <exception>
using namespace std;

int main() {
    WarehouseSystem* app = nullptr;
    try {
        app = new WarehouseSystem();
        app->loadData();
        app->run();
        delete app;
        return 0;
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << "\n";
    } catch (...) {
        cerr << "Fatal error: unknown exception.\n";
    }
    if (app) delete app;
    return 1;
}
