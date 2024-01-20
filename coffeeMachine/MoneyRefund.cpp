#include "MoneyRefund.h"

#include <iostream>
using namespace std;
//=================конструктор================================
MoneyRefund::MoneyRefund(cl_base* p_head, string name) : cl_base(p_head, name)
{

}
//==============преобразование=данных=о=сдаче=================
void MoneyRefund::handler_set_coins(string _coins)
{
    vector <string> temp_coins = split(_coins);
    for (int i = 0; i < temp_coins.size(); i++){
        coins.push_back(stoi(temp_coins[i]));
    }
    sum = 5*coins[0] + 10*coins[1];

}
//======================выдача=сдачи===========================
void MoneyRefund::handler_give_refund(string refund)
{
    int Refund = stoi(refund);
    if(Refund != 0 && Refund < sum)
    {
        vector <int> amount_of_coins = {0, 0};
        vector <int> weights = {5, 10};
        for (int i = 0; i < coins.size(); i++)
        {
            if (Refund != 0)
            {
                int koef = Refund/weights[coins.size()-i-1];
                if(koef <= coins[coins.size()-i-1])
                {
                    amount_of_coins[i] = koef;
                    coins[coins.size()-i-1] -= koef;
                    Refund -= koef*weights[coins.size()-i-1];
                }
                else
                {
                    amount_of_coins[i] = coins[coins.size()-i-1];
                    Refund -= coins[coins.size()-i-1]*weights[coins.size()-i-1];
                    coins[coins.size()-i-1] = 0;
                }
            }
            else
            {
                break;
            }

        }
        MoneyAccepting* accept = (MoneyAccepting*)path_coord("/Money_accepting");
        accept->set_sum();
        string message = "Take the change: 10 * " + to_string(amount_of_coins[0]) + " rub.,  5 * " + to_string(amount_of_coins[1]) + " rub.";
        emit_signal(SIGNAL_D(MoneyRefund::signal_print), message);
        cout << endl;
    }
}
//=============================хранение=сдачи==================================
void MoneyRefund::handler_refund(string _sum)
{
    int Refund = stoi(_sum);
    if(Refund != 0 && Refund < sum)
    {
        vector <int> amount_of_coins = {0, 0};
        vector <int> weights = {5, 10};
        for (int i = 0; i < coins.size(); i++)
        {
            if (Refund != 0)
            {
                int koef = Refund/weights[coins.size()-i-1];
                if(koef <= coins[coins.size()-i-1]){
                    amount_of_coins[i] = koef;
                    coins[coins.size()-i-1] -= koef;
                    Refund -= koef*weights[coins.size()-i-1];
                } else
                {
                    amount_of_coins[i] = coins[coins.size()-i-1];
                    Refund -= coins[coins.size()-i-1]*weights[coins.size()-i-1];
                    coins[coins.size()-i] = 0;
                }

            } else
            {
                break;
            }

        }
        MoneyAccepting* accept = (MoneyAccepting*)path_coord("/Money_accepting");
        accept->set_sum();
        string message = "Take the money: 10 * " + to_string(amount_of_coins[0]) + " rub.,  5 * " + to_string(amount_of_coins[1]) + " rub.";
        emit_signal(SIGNAL_D(MoneyRefund::signal_print), message);
        cout << endl;
    }
}
//==========================метод=возврата=суммы===============================
int MoneyRefund::get_sum()
{
    return sum;
}
//=======================сигналы=устройства=выдачи=сдачи=======================
void MoneyRefund::signal_print(string& text){}
//==============================================================================
