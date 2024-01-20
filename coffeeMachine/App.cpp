#include "App.h"
#include "Reader.h"
#include "ControlPanel.h"
#include "MoneyAccepting.h"
#include "MoneyRefund.h"
#include "CoffeeDispenser.h"
#include "Output.h"
#include "cl_base.h"
#include <iostream>
#include <vector>
using namespace std;

//=================конструктор======================================
App::App(cl_base* p_head, string name) : cl_base(p_head, name)
{

}
//============метод=построения=дерева=иерархии=объектов=============
void App::build_tree()
{
    //=изменение=наименования=корневого=объекта
    set_name("Coffee_machine");

    //=====cоздание=объектов-устройств=кофемашины===================
    Reader* ob_reader = new Reader(this, "Data_reader");
    Output* ob_output = new Output(this, "Data_output");
    ControlPanel* ob_panel = new ControlPanel(this, "Control_panel");
    MoneyAccepting* ob_accepting = new MoneyAccepting(this, "Money_accepting");
    CoffeeDispenser* ob_dispencer = new CoffeeDispenser(this, "Coffee_dispencer");
    MoneyRefund* ob_refund = new MoneyRefund(this, "Money_refund");

    //====================установка=связей==========================
    set_connection(SIGNAL_D(App::signal_reader), ob_reader, HANDLER_D(Reader::handler_read));
    set_connection(SIGNAL_D(App::signal_print), ob_output, HANDLER_D(Output::handler_print));

    ob_reader->set_connection(SIGNAL_D(Reader::signal_panel), ob_panel, HANDLER_D(ControlPanel::handler_from_reader));

    ob_panel->set_connection(SIGNAL_D(ControlPanel::signal_assortment), ob_dispencer, HANDLER_D(CoffeeDispenser::handler_assortment));
    ob_panel->set_connection(SIGNAL_D(ControlPanel::signal_set_prices), ob_dispencer, HANDLER_D(CoffeeDispenser::handler_set_prices));
    ob_panel->set_connection(SIGNAL_D(ControlPanel::signal_set_coins), ob_refund, HANDLER_D(MoneyRefund::handler_set_coins));
    ob_panel->set_connection(SIGNAL_D(ControlPanel::signal_refund), ob_refund, HANDLER_D(MoneyRefund::handler_refund));
    ob_panel->set_connection(SIGNAL_D(ControlPanel::signal_end), this, HANDLER_D(App::handler_end));
    ob_panel->set_connection(SIGNAL_D(ControlPanel::signal_input_money), ob_accepting, HANDLER_D(MoneyAccepting::handler_input_money));
    ob_panel->set_connection(SIGNAL_D(ControlPanel::signal_select_coffee), ob_dispencer, HANDLER_D(CoffeeDispenser::handler_select_coffee));
    ob_panel->set_connection(SIGNAL_D(ControlPanel::signal_print), ob_output, HANDLER_D(Output::handler_print));

    ob_dispencer->set_connection(SIGNAL_D(CoffeeDispenser::signal_check_money), ob_accepting, HANDLER_D(MoneyAccepting::handler_check_money));
    ob_dispencer->set_connection(SIGNAL_D(CoffeeDispenser::signal_print), ob_output, HANDLER_D(Output::handler_print));
    ob_dispencer->set_connection(SIGNAL_D(CoffeeDispenser::signal_give_refund), ob_refund, HANDLER_D(MoneyRefund::handler_give_refund));

    ob_accepting->set_connection(SIGNAL_D(MoneyAccepting::signal_print), ob_output, HANDLER_D(Output::handler_print));
    ob_accepting->set_connection(SIGNAL_D(MoneyAccepting::signal_give_coffee), ob_dispencer, HANDLER_D(CoffeeDispenser::handler_give_coffee));

    ob_refund->set_connection(SIGNAL_D(MoneyRefund::signal_print), ob_output, HANDLER_D(Output::handler_print));
}

//========================метод=запуска=приложения==========================
int App::exec_app()
{
    set_all_states();
    string ready = "Ready to work";
    emit_signal(SIGNAL_D(App::signal_print), ready );
    cout << endl;
    while(turn_off == false){
        string text = "";
        emit_signal(SIGNAL_D(App::signal_reader), text);
    }
    return 0;
}
//==============обработчик=завершения=работы=устройства=====================
void App::handler_end(string text)
{
    turn_off = true;
}
//===========================сигналы=объекта-системы========================
void App::signal_reader(string& text){}

void App::signal_print(string& text){}
//==========================================================================
