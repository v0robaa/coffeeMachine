#ifndef COFFEEMACHINE_READER_H
#define COFFEEMACHINE_READER_H
#include "cl_base.h"
using namespace std;

class Reader : public cl_base{
public:
    Reader (cl_base* p_head, string name);
    void handler_read(string text);
    void signal_panel(string &text);
};

#endif //COFFEEMACHINE_READER_H
