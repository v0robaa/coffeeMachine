#ifndef COFFEEMACHINE_CL_BASE_H
#define COFFEEMACHINE_CL_BASE_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class cl_base;
#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define HANDLER_D( handler_f ) ( TYPE_HANDLER ) ( & handler_f )
typedef void ( cl_base :: * TYPE_SIGNAL ) ( string & );
typedef void ( cl_base :: * TYPE_HANDLER ) ( string );

class cl_base{
private:
    cl_base* p_head;
    string name;
    vector <cl_base*> p_sub;
    int state = 0;

    //==сигналы=и=обработчики
    int n_cl;
    struct signals{
        TYPE_SIGNAL signal;
        cl_base* object;
        TYPE_HANDLER handler;
    };
    vector <signals*> connects;

public:
    //-структоры
    cl_base(cl_base* p_head, string name = "Base Object");
    ~cl_base();

    //сеттеры
    bool set_name(string name);
    void set_state(int state);
    void set_all_states();

    //геттеры
    string get_name();
    cl_base* get_head();
    cl_base* get_sub(string name);
    cl_base* get_head_name(string name);
    cl_base* get_sub_name(string name);

//вывод
    void print_tree();
    void print_states();
    void print_sys();

    //координаты
    cl_base* path_coord(string coordinate);
    bool redefine(cl_base* head);
    void deleteSub(string name);

    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    //==сигналы=и=обработчики
    void set_connection(TYPE_SIGNAL signal, cl_base* object, TYPE_HANDLER handler);
    void delete_connection(TYPE_SIGNAL signal, cl_base* object, TYPE_HANDLER handler);
    void emit_signal(TYPE_SIGNAL signal, string &command);

    //сеттеры
    void set_class(int number);
    void set_sub_state(int state);

    //геттеры
    string get_path();
    int get_class();
    int get_state();
    vector<string> split(string str);
};

#endif //COFFEEMACHINE_CL_BASE_H
