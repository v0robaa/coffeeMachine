#include "cl_base.h"
#include <iostream>

//=================конструктор==============================
cl_base::cl_base(cl_base* p_head, string name)
{
    this->name = name;
    this->p_head = p_head;
    if (p_head)
    {
        p_head->p_sub.push_back(this);
    }
}
//=======================деструктор=============================
cl_base::~cl_base()
{
    cl_base* head = this;
    while (head->p_head != nullptr)
        head = head->p_head;
    vector <cl_base*> nodes;
    nodes.push_back(head);
    while (nodes.size())
    {
        cl_base *curr = nodes.back();
        nodes.pop_back();
        if (curr != nullptr)
        {
            for (int i = 0; i < curr->connects.size(); i++)
            {
                if (curr->connects[i]->object == this)
                {
                    curr->delete_connection(curr->connects[i]->signal, this, curr->connects[i]->handler);
                    i--;
                }
            }
            for (int i =0; i < curr->p_sub.size(); i++)
            {
                nodes.push_back(curr->p_sub[i]);
            }
        }
    }
    for (unsigned int i=0; i > connects.size(); i++)
        delete connects[i];
    connects.clear();
    for (int i=0; i < p_sub.size(); i++)
    {
        delete p_sub[i];
        p_sub[i] = nullptr;
    }
}
//===================метод=установки=имени===================
bool cl_base::set_name(string name)
{
    if (p_head == nullptr)
    {
        this->name = name;
        return 1;
    }
    if (p_head->get_sub(name) == nullptr)
    {
        this->name = name;
        return 1;
    }
    return 0;
}
//===================метод=установки=состояния===================
void cl_base::set_state(int state)
{
    if (this->state == state) return;
    if (this->p_head != nullptr)
    {
        if (this->p_head->state != 0)
        {
            this->state = state;
            if (state == 0)
            {
                for (int i = 0; i < p_sub.size(); i++)
                {
                    p_sub[i]->set_state(0);
                }
            }
        }
        else
        {
            this->state = 0;
            for (int i = 0; i < p_sub.size(); i++)
            {
                p_sub[i]->set_state(0);
            }
        }
    }
    else
    {
        this->state = state;
        if (state == 0)
        {
            for (int i = 0; i < p_sub.size(); i++)
            {
                p_sub[i]->set_state(0);
            }
        }
    }
}
//===================метод=возврата=имени====================
string cl_base::get_name()
{
    return this->name;
}
//=======метод=возврата=указателя=на=головной=объект=========
cl_base* cl_base::get_head()
{
    return this->p_head;
}
//=======метод=поиска=подчиненного=объекта=по=имени==========
cl_base* cl_base::get_sub(string name)
{
    for (int i = 0; i < p_sub.size(); i++)
    {
        if (this->p_sub[i]->get_name() == name)
        {
            return p_sub[i];
        }
    }
    return nullptr;
}
//==========метод=поиска=объекта=на=ветке=по=имени=========
cl_base* cl_base::get_sub_name(string name)
{
    vector <cl_base*> nodes = {this};
    cl_base *temp, *res = nullptr;
    while (!nodes.empty())
    {
        temp = nodes.back();
        nodes.pop_back();
        if (temp->name == name)
        {
            if (res != nullptr)
            {
                return nullptr;
            }
            res = temp;
        }
        for (int i = 0; i < temp->p_sub.size();i++)
        {
            nodes.push_back(temp->p_sub[i]);
        }
    }
    return res;
}
//==========метод=поиска=объекта=на=дереве=от=текущего========
cl_base* cl_base::get_head_name(string name)
{
    cl_base* curr_node = this;
    while (true)
    {
        if (curr_node->p_head == nullptr)
        {
            return curr_node->get_sub_name(name);
        }
        curr_node = curr_node->p_head;
    }
}
//=======метод=вывода=дерева=иерархии=объектов=от=текущего====
void cl_base::print_tree()
{
    if (p_head == nullptr)
    {
        cout << get_name();
    }
    if (p_sub.size() == 0)
    {
        return;
    }
    cout << endl;
    cout << name;
    for (int i = 0; i < p_sub.size(); i++)
    {
        cout << " " << p_sub[i]->get_name();
    }
    p_sub[p_sub.size()-1]->print_tree();
}
//==============метод=вывода=состояний=объектов==============
void cl_base::print_states()
{
    cl_base* curr_node = this;
    int level = 0;
    while (curr_node->p_head != nullptr)
    {
        level += 1;
        curr_node = curr_node->p_head;
    }
    if (level != 0)
    {
        cout << endl;
    }
    for (int i = 0; i < level; i++)
    {
        cout << "    ";
    }
    cout << this->name;
    if (this->state != 0)
    {
        cout << " is ready";
    }
    else {
        cout << " is not ready";
    }
    for (int i = 0; i < this->p_sub.size(); i++)
    {
        p_sub[i]->print_states();
    }
}
//==========метод=вывода=упорядоченного=дерева=объектов=============
void cl_base::print_sys()
{
    cl_base* curr_node = this;
    int level = 0;
    while (curr_node->p_head != nullptr)
    {
        level += 1;
        curr_node = curr_node->p_head;
    }
    cout << endl;
    for (int i = 0; i < level; i++)
    {
        cout << "    ";
    }
    cout << this->name;
    for (int i = 0; i < this->p_sub.size(); i++)
    {
        p_sub[i]->print_sys();
    }
}
//======метод=получения=указателя=на=любой=объект=согласно=пути======
cl_base* cl_base::path_coord(string coordinate)
{
    if (coordinate == "") return nullptr;
    if (coordinate == ".") return this;
    if (coordinate == "/")
    {
        cl_base* curr = this;
        while (curr->p_head != nullptr)
        {
            curr = curr->p_head;
        }
        return curr;
    }
    if (coordinate.size() < 2) return nullptr;
    if (coordinate.substr(0, 1) == ".") return get_sub_name(coordinate.substr(1, coordinate.size()-1));
    if (coordinate.substr(0, 2) == "//") return get_head_name(coordinate.substr(2, coordinate.size()-2));
    string word = "";
    vector <string> node_names;
    for (int i = 0; i < coordinate.size(); i++)
    {
        if (coordinate[i] == '/')
        {
            node_names.push_back(word);
            word = "";
            continue;
        }
        word += coordinate[i];
    }
    if (word != "") node_names.push_back(word);
    cl_base *curr = nullptr;
    for (int i = 0; i< node_names.size(); i++)
    {
        if (i == 0){
            if (node_names[i] != "")
            {
                curr = this;
            }
            else {
                curr = this;
                while (curr->p_head != nullptr)
                {
                    curr = curr->p_head;
                }
                continue;
            }
        }
        curr = curr->get_sub(node_names[i]);
        if (curr == nullptr)
        {
            return nullptr;
        }
    }
    return curr;
}
//==метод=переопределения=головного=объекта=для=текущего=в=дереве=иерархии==ОСТАЛОСЬ
bool cl_base::redefine(cl_base *head)
{
    if (head == nullptr || !p_head)
    {
        return false;
    }
    cl_base* temp = head;
    while (temp != nullptr)
    {
        temp = temp->p_head;
        if (temp == this)
            return false;
    }
    if (head->get_sub(name) == nullptr && p_head != nullptr)
    {
        for (int i = 0; i < p_head->p_sub.size();i++)
        {
            if (p_head->p_sub[i] == this)
            {
                p_head->p_sub.erase(p_head->p_sub.begin() + i);
                break;
            }
        }
        head->p_sub.push_back(this);
        p_head = head;
        return true;
    }
    return false;
}
//======метод=удаления=подчиненног=объекта=по=наименованию====================
void cl_base::deleteSub(string name)
{
    cl_base* temp = get_head_name(name);
    if (!temp)
        return;
    for (int i = 0; temp->p_head->p_sub.size(); i++)
    {
        if (temp->p_head->p_sub[i] == temp)
        {
            temp->p_head->p_sub.erase(temp->p_head->p_sub.begin() + i);
            break;
        }
    }
    delete temp;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//==метод=установки=связи=между=сигналом=текущего=объекта=и=обработчиком=целевого==
void cl_base::set_connection(TYPE_SIGNAL signal, cl_base* object, TYPE_HANDLER handler)
{
    signals *value;
    for (unsigned int i = 0; i < connects.size(); i ++)
    {
        if (connects[i]->signal == signal && connects[i]->object == p_head &&connects[i]->handler == handler)
            return;
    }
    value = new signals();
    value->signal = signal;
    value->object = object;
    value->handler = handler;
    connects.push_back(value);
}
//==метод=удаления=связи=между=сигналом=текущего=объекта=и=обработчиком=целевого====
void cl_base::delete_connection(TYPE_SIGNAL signal, cl_base*object, TYPE_HANDLER handler)
{
    signals *temp;
    for (unsigned int i = 0; i < connects.size(); i ++)
    {
        if (connects[i]->signal == signal && connects[i]->object == object&&connects[i]->handler == handler)
        {
            temp = connects[i];
            connects.erase(connects.begin()+i);
            delete temp;
            return;
        }
    }
}
//=====метод=выдачи=сигнала=от=текущего=объекта=с=передачей=строковой=переменной====
void cl_base::emit_signal(TYPE_SIGNAL signal, string &command)
{
    if (state == 0)
        return;
    TYPE_HANDLER handler;
    cl_base* p;
    (this->*signal)(command);
    for (unsigned int i=0; i < connects.size();i++)
    {
        if (connects[i]->signal == signal && connects[i]->object->state != 0)
        {
            handler = connects[i]->handler;
            p = connects[i]->object;
            (p->*handler)(command);
        }
    }
}
//==================метод=установки=принадлежности=классу=========================
void cl_base::set_class(int number)
{
    n_cl = number;
}
//==метод=установки=состояний=подчиненных=объектов=как=текущего=головного=========
void cl_base::set_sub_state(int state)
{
    this->set_state(state);
    for (int i=0; i<p_sub.size();i++)
        p_sub[i]->set_sub_state(state);
}
//==========метод=определения=абсолютного=пути=до=текущего=объекта================
string cl_base::get_path()
{
    if (this->p_head == nullptr)
        return "/";
    string path = "";
    cl_base* curr = this;
    while (curr->p_head != nullptr)
    {
        path = '/' + curr->name + path;
        curr = curr->p_head;
    }
    return path;
}
//==================метод=получения=принадлежности=классу=========================
int cl_base::get_class()
{
    return n_cl;
}
//===============метод=получения=состояния=текущего=объекта========================
int cl_base::get_state()
{
    return state;
}
//==============метод=разбиения=на=подстроки=======================================
vector <string> cl_base::split(string str)
{
    string line = str+" ";
    vector <string> temp_arr;
    string word;
    for(int i = 0; i<line.size(); i++){
        if (i == line.size() - 1){
            temp_arr.push_back(word);
        }
        if (str[i] != ' '){
            word+=line[i];
        } else {
            temp_arr.push_back(word);
            word = "";
        }
    }
    return temp_arr;
}
//=============метод=приведения=в=готовность=всех=объектов========================
void cl_base::set_all_states()
{
    set_state(1);
    for (auto p : p_sub){
        p->set_state(1);
    }
}
//===================================================================================


