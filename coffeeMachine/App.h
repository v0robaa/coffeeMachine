#ifndef COFFEEMACHINE_APP_H
#define COFFEEMACHINE_APP_H
#include "cl_base.h"
using namespace std;
class App : public cl_base{
private:
    bool turn_off = false;
public:
    App(cl_base* parent, string name = "");
    void build_tree();
    int exec_app();
    void signal_reader(string& text);
    void signal_print(string& text);
    void handler_end(string text);

};


#endif //COFFEEMACHINE_APP_H
