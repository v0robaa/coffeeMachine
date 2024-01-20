#ifndef COFFEEMACHINE_MONEYREFUND_H
#define COFFEEMACHINE_MONEYREFUND_H
#include "cl_base.h"
#include "MoneyAccepting.h"
using namespace std;

class MoneyRefund : public cl_base
{
private:
    int sum = 0;
    vector <int> coins;
public:
    MoneyRefund(cl_base* p_head, string name);
    void handler_set_coins(string _coins);
    void handler_give_refund(string refund);
    void handler_refund(string text);
    int get_sum();

    void signal_print(string& text);


};

#endif //COFFEEMACHINE_MONEYREFUND_H
