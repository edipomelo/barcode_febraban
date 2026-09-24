#import <iostream>
#import "funcoes_boleto.h"

using namespace std;

int codigo_banco;
int codigo_moeda;
string data_vencimento;
string valor;
long campo_livre;

int main(int argc, char **argv) {
	cout << "Informe os parâmetros para gerar o código de barras:" << endl;
	// 01 a 03 - Código do Banco na Câmara de Compensação = '001'
	cout << "Código do banco: ";
	cin >> codigo_banco;
	// 04 a 04 - Código da Moeda = 9 (Real) - FIXO
	cout << "\nCódigo da moeda (FIXO): 9";
	codigo_moeda = 9;
    // 05 a 05 - Digito Verificador (DV) do código de Barras - CALCULADO
	// 06 a 09 - Fator de Vencimento
	cout << "\nData de vencimento (DD/MM/AAAA): ";
	cin >> data_vencimento;
	// 10 a 19 - Valor
	cout << "\nValor a ser pago (casa decimal separada por vírgula): ";
	cin >> valor;
	// 20 a 44 - Campo Livre
	cout << "\nCampo livre (somente dígitos): ";
	cin >> campo_livre;

	// funções para gerar o código de barras

	return 0;
}
