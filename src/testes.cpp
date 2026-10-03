#include <iostream>
#include "funcoes_boleto.h"

using namespace std;

int main(int argc, char const *argv[])
{
    string data = "31/12/2007";
    cout << data <<  " = " << fator_vencimento(data) << endl;;
    return 0;
}
