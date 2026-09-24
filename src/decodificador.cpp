#import <iostream>
#import "funcoes_boleto.h"

using namespace std;

int codigo_banco;
int codigo_moeda;
string data_vencimento;
string valor;
long campo_livre;
string codigo_barras;
int digito_verificador;
string linha_digitavel;

int main(int argc, char **argv) {
	cout << "Informe o código de barras:" << endl;
	cin >> codigo_barras;

	// funções para decodificar o código de barras

	// eixibindo:
	// 01 a 03 - Código do Banco na Câmara de Compensação = '001'
	cout << "Código do banco: " << codigo_banco << endl;
	// 04 a 04 - Código da Moeda = 9 (Real) - FIXO
	cout << "Código da moeda (FIXO): 9" << codigo_moeda << endl;
	// 05 a 05 - Digito Verificador (DV) do código de Barras
	cout << "Dígito verificador: " << digito_verificador << endl;
	// 06 a 09 - Fator de Vencimento
	cout << "Data de vencimento (DD/MM/AAAA): " << data_vencimento << endl;
	// 10 a 19 - Valor
	cout << "Valor a ser pago (casa decimal separada por vírgula): " << valor << endl;
	// 20 a 44 - Campo Livre
	cout << "Campo livre (somente dígitos): " << campo_livre << endl;
	// linha digitável:
	cout << linha_digitavel;
	return 0;
}
