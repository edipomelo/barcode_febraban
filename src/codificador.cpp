#include <iostream>
#include "funcoes_boleto.h"

using namespace std;

int codigo_banco;
int codigo_moeda;
string data_vencimento;
string valor;
string campo_livre;

int main(int argc, char **argv) {
	// cout << "Informe os parâmetros para gerar o código de barras:" << endl;
	// // 01 a 03 - Código do Banco na Câmara de Compensação = '001'
	// cout << "Código do banco: ";
	// cin >> codigo_banco;
	// // 04 a 04 - Código da Moeda = 9 (Real) - FIXO
	// cout << "\nCódigo da moeda (9 - Real):";
	// cin >> codigo_moeda;
    // // 05 a 05 - Digito Verificador (DV) do código de Barras - CALCULADO
	// // 06 a 09 - Fator de Vencimento
	// cout << "\nData de vencimento (DD/MM/AAAA): ";
	// cin >> data_vencimento;
	// // 10 a 19 - Valor
	// cout << "\nValor a ser pago (casa decimal separada por vírgula): ";
	// cin >> valor;
	// // 20 a 44 - Campo Livre
	// cout << "\nCampo livre (somente dígitos): ";
	// cin >> campo_livre;

	// dados para teste
	codigo_banco = 1;
	codigo_moeda = 9;
	data_vencimento = "31/12/2007";
	valor = "1,00";
	campo_livre = "0500940144816060680935031";

	// funções para gerar o código de barras
	cout << "\nCódigo de barras gerado: " 
		 << codigo_barras(codigo_banco, codigo_moeda, data_vencimento, valor, campo_livre) 
		 << endl;

	cout << "Esperado:              : 00193373700000001000500940144816060680935031" << endl;
	return 0;
}
