#include "Output.h"
#include "cl_base.h"
#include <iostream>
#include <string>

using namespace std;
//=================конструктор================================
Output::Output(cl_base *p_head, string name):cl_base(p_head, name)
{

}
//========================вывод===============================
void Output::handler_print(string text)
{
    cout << text;
}
//==============================================================
