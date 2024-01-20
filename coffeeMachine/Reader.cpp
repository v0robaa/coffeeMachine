#include "Reader.h"
#include "cl_base.h"
#include <iostream>
using namespace std;
//=================конструктор================================
Reader::Reader(cl_base* p_head, string name) : cl_base(p_head, name){

}
//===============обработчик=вводимых=данных===================
void Reader::handler_read(string text){
    string command;
    getline(cin, command);
    emit_signal(SIGNAL_D(Reader::signal_panel), command);
}
//=================сигнал=устройства=чтения===================
void Reader::signal_panel(string &text){

}
//============================================================
