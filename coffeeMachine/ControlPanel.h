#ifndef COFFEEMACHINE_CONTROLPANEL_H
#define COFFEEMACHINE_CONTROLPANEL_H
#include "cl_base.h"
#include "App.h"
#include "MoneyAccepting.h"
using namespace std;

class ControlPanel : public cl_base
{
private:
    bool input_coffees = false;
    bool prices = false;
    bool coins = false;
public:
    ControlPanel (cl_base* p_head, string name);

    void signal_assortment(string& text);
    void signal_set_prices(string& text);
    void signal_set_coins(string& text);
    void signal_refund(string& text);
    void signal_end(string& text);
    void signal_input_money(string& text);
    void signal_select_coffee(string& text);
    void signal_print(string& text);

    void handler_from_reader(string command);
};

#endif //COFFEEMACHINE_CONTROLPANEL_H
