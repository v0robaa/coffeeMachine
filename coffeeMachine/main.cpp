#include <iostream>
#include "App.h"
#include "cl_base.h"
using namespace std;

int main()
{
    App testing(nullptr);
    testing.build_tree();
    return testing.exec_app();
}
