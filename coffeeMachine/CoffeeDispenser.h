#ifndef COFFEEMACHINE_COFFEEDISPENSER_H
#define COFFEEMACHINE_COFFEEDISPENSER_H
#include "cl_base.h"
#include <map>
using namespace std;

class CoffeeDispenser : public cl_base
{
private:
    vector <string> assortment;
    vector <int> prices;
    int amount_of_coffee;
    int selected_coffee_num;
public:
    CoffeeDispenser (cl_base* p_head, string name);
    void handler_assortment(string assortment);
    void handler_set_prices(string _prices);
    void handler_select_coffee(string name);
    void handler_give_coffee(string refund);

    void signal_check_money();
    void signal_print(string& text);
    void signal_give_refund(string& text);
};

#endif //COFFEEMACHINE_COFFEEDISPENSER_H
