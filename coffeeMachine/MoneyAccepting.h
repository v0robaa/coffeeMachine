#ifndef COFFEEMACHINE_MONEYACCEPTING_H
#define COFFEEMACHINE_MONEYACCEPTING_H
#include "MoneyRefund.h"
#include "cl_base.h"
using namespace std;

class MoneyAccepting : public cl_base
{
    private:
        int sum = 0;

    public:
        MoneyAccepting(cl_base* p_head, string name);
        void handler_check_money(string price);
        void handler_input_money(string money);

        void signal_print(string& text);
        void signal_give_coffee(string& refund);

        int get_sum();
        void set_sum();
};

#endif //COFFEEMACHINE_MONEYACCEPTING_H
