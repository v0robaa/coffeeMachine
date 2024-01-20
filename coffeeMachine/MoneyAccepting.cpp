#include "MoneyAccepting.h"

#include "cl_base.h"
#include <string>
#include <iostream>
using namespace std;
//=================конструктор================================
MoneyAccepting::MoneyAccepting(cl_base* p_head, string name) : cl_base(p_head, name)
{

}
//====================проверка=на=достаточность=средств==============
void MoneyAccepting::handler_check_money(string price)
{
    if (stoi(price)<=sum)
    {
        sum -= stoi(price);
        string refund = to_string(sum);
        emit_signal(SIGNAL_D(MoneyAccepting::signal_give_coffee), refund);
        string str = "Ready to work";
        emit_signal(SIGNAL_D(MoneyAccepting::signal_print), str);
        cout << endl;
    } else {
        string str = "There is not enough money";
        emit_signal(SIGNAL_D(MoneyAccepting::signal_print), str);
        cout << endl;
    }
}
//=========================ввод=денег=и=провреки======================
void MoneyAccepting::handler_input_money(string money)
{
    if (stoi(money) == 5 || stoi(money) == 10)
    {
        sum+=stoi(money);
        string str = "The amount: " +to_string(sum);
        emit_signal(SIGNAL_D(MoneyAccepting::signal_print), str);
        cout << endl;

    }
    else if(stoi(money) == 50 || stoi(money) == 100)
    {
        MoneyRefund* refund = (MoneyRefund*)(path_coord("/Money_refund"));
        int ref_sum = refund->get_sum();
        if (ref_sum>=stoi(money))
        {
            sum+=stoi(money);
            string str = "The amount: " + to_string(sum);
            emit_signal(SIGNAL_D(MoneyAccepting::signal_print), str);
            cout << endl;
        }
        else
        {
            string error = "Take the money back, no change";
            emit_signal(SIGNAL_D(MoneyAccepting::signal_print), error);
            cout << endl;
        }
    }
}
//==========================метод=возврата=суммы===============================
int MoneyAccepting::get_sum()
{
    return sum;
}
//==========================метод=установки=суммы===============================
void MoneyAccepting::set_sum()
{
    sum = 0;
}
//=======================сигналы=устройства=приема=денег========================
void MoneyAccepting::signal_print(string& text){}

void MoneyAccepting::signal_give_coffee(string& refund){}
//==============================================================================
