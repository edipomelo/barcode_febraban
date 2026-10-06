#include <iostream>
#include "funcoes_boleto.h"
#include <string>
using namespace std;

string codigo_banco;
string codigo_moeda;
string data_vencimento;
string valor;
string campo_livre;
string codigo_barras;
string digito_verificador;
string linha_digitavel;

int main(int argc, char **argv)
{
	cout << "Informe o código de barras:" << endl;
	cin >> codigo_barras;

	// Exemplo de codigo de barras: 00193373700000001000500940144816060680935031

	linha_digitavel = formatarlinhadigitavel(codigo_barras);
	codigo_banco = codigo_barras.substr(0, 3);
	codigo_moeda = codigo_barras.substr(3, 1);
	digito_verificador = codigo_barras.substr(4, 1);
	data_vencimento = data_vencimento_formatada(codigo_barras);
	valor = valor_formatado(codigo_barras);
	campo_livre = codigo_barras.substr(19);

	// Linha digitável
	cout << "Linha digitável: " << linha_digitavel << endl;
	// 01 a 03 - Código do Banco na C âmara de Compensação = '001'
	cout << "Código do banco: " << codigo_banco << endl;
	// 04 a 04 - Código da Moeda = 9 (Real) - FIXO
	cout << "Código da moeda (FIXO): " << codigo_moeda << endl;
	// 05 a 05 - Digito Verificador (DV) do código de Barras
	cout << "Dígito verificador: " << digito_verificador << endl;
	// 06 a 09 - Fator de Vencimento
	cout << "Data de vencimento (DD/MM/AAAA): " << data_vencimento << endl;
	// 10 a 19 - Valor
	cout << "Valor a ser pago (casa decimal separada por vírgula): " << valor << endl;
	// 20 a 44 - Campo Livre
	cout << "Campo livre (somente dígitos): " << campo_livre << endl;

	return 0;
}
