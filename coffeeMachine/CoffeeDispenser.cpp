#include "CoffeeDispenser.h"

#include <iostream>
using namespace std;
//=================конструктор============================================
CoffeeDispenser::CoffeeDispenser(cl_base* p_head, string name) : cl_base(p_head, name)
{

}
//===============обработчик=вводимого=ассортимента========================
void CoffeeDispenser::handler_assortment(string _assortment)
{
    vector <string> information = split(_assortment);
    amount_of_coffee = stoi(information[0]);
    for (int i = 1; i < amount_of_coffee+1; i++){
        assortment.push_back(information[i]);
    }
}
//=====================установка=цен=на=кофе===============================
void CoffeeDispenser::handler_set_prices(string _prices)
{
    vector <string> temp_prices = split(_prices);
    for (int i = 0; i < amount_of_coffee; i++){
        prices.push_back(stoi(temp_prices[i]));
    }

}
//==========================выбор=кофе=========================================
void CoffeeDispenser::handler_select_coffee(string name)
{
    for (int i = 0; i < amount_of_coffee; i++){
        if (name == assortment[i]){
            selected_coffee_num = i;
            string price = to_string(prices[i]);
            emit_signal(SIGNAL_D(CoffeeDispenser::signal_check_money), price);
        }
    }
}
//===============================выдача=кофе====================================
void CoffeeDispenser::handler_give_coffee(string refund)
{
    string take_coffee = "Take the coffee " + assortment[selected_coffee_num];
    emit_signal(SIGNAL_D(CoffeeDispenser::signal_print), take_coffee);
    cout << endl;
    emit_signal(SIGNAL_D(CoffeeDispenser::signal_give_refund), refund);
}
//=======================сигналы=устройства=выдачи=кофе=========================
void CoffeeDispenser::signal_check_money(){}

void CoffeeDispenser::signal_print(string& text){}

void CoffeeDispenser::signal_give_refund(string& text){}
//==============================================================================
