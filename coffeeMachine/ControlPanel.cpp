#include "ControlPanel.h"

#include <iostream>
using namespace std;
//=================конструктор======================================
ControlPanel::ControlPanel(cl_base* p_head, string name) : cl_base(p_head, name)
{

}
//============обработчик=введенных=команд===========================
void ControlPanel::handler_from_reader(string command)
{
    if(command == "SHOWTREE")
    {
        path_coord("/")->print_states();
        exit(0);
    }
    if(command == "Cancel")
    {
        string end = "Turned off";
        emit_signal(SIGNAL_D(ControlPanel::signal_print), end);
        emit_signal(SIGNAL_D(ControlPanel::signal_end), command);
        return;
    }
    if(!input_coffees && !prices && !coins)
    {
        input_coffees = true;
        emit_signal(SIGNAL_D(ControlPanel::signal_assortment), command);
    } else if(input_coffees && !prices && !coins)
    {
        prices = true;
        emit_signal(SIGNAL_D(ControlPanel::signal_set_prices), command);
    } else if(input_coffees && prices && !coins)
    {
        coins = true;
        emit_signal(SIGNAL_D(ControlPanel::signal_set_coins), command);
    }
    else if (input_coffees && prices && coins)
    {

        if(command == "Refund money")
        {
            MoneyAccepting* accept = (MoneyAccepting*)path_coord("/Money_accepting");
            string refund = to_string(accept->get_sum());
            string ready = "Ready to work";
            emit_signal(SIGNAL_D(ControlPanel::signal_refund), refund);
            emit_signal(SIGNAL_D(ControlPanel::signal_print), ready);
            cout << endl;
        }
        else if(command.substr(0, 6) == "Coffee")
        {
            string temp_command = command.substr(7);
            emit_signal(SIGNAL_D(ControlPanel::signal_select_coffee), temp_command);
            //string ready = "Ready to work";
            //emit_signal(SIGNAL_D(ControlPanel::signal_print), ready);
            //cout << endl;
        }
        else
        {
            emit_signal(SIGNAL_D(ControlPanel::signal_input_money), command);
        }
    }
}
//=========================сигналы=панели=управления===========================
void ControlPanel::signal_assortment(string& text){}

void ControlPanel::signal_set_prices(string& text){}

void ControlPanel::signal_set_coins(string& text){}

void ControlPanel::signal_refund(string& text){}

void ControlPanel::signal_end(string& text){}

void ControlPanel::signal_input_money(string& text){}

void ControlPanel::signal_select_coffee(string& text){}

void ControlPanel::signal_print(string& text){}
//==============================================================================
