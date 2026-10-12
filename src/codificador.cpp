#include <iostream>
#include "funcoes_boleto.h"

using namespace std;

int codigo_banco;
int codigo_moeda;
string data_vencimento;
string valor;
string campo_livre;
int tipo_convenio;
string numero_convenio;
string nosso_numero;
string carteira;
string agencia;
string numero_conta;

int main(int argc, char **argv)
{
	cout << "Informe os parâmetros para gerar o código de barras:" << endl;
	// 01 a 03 - Código do Banco na Câmara de Compensação = '001'
	cout << "Código do banco: ";
	cin >> codigo_banco;
	// 04 a 04 - Código da Moeda = 9 (Real) - FIXO
	cout << "\nCódigo da moeda (9 - Real):";
	cin >> codigo_moeda;
	// 05 a 05 - Digito Verificador (DV) do código de Barras - CALCULADO
	// 06 a 09 - Fator de Vencimento
	cout << "\nData de vencimento (DD/MM/AAAA): ";
	cin >> data_vencimento;
	// 10 a 19 - Valor
	cout << "\nValor a ser pago (casa decimal separada por vírgula): ";
	cin >> valor;
	// 20 a 44 - Campo Livre
	cout << "\nTipo do Convênio (somente dígitos): ";
	cin >> tipo_convenio;
	cout << "\nCampo livre (4, 5, 7 ou 17): ";
	if (tipo_convenio != 4 && tipo_convenio != 5 && tipo_convenio != 7 && tipo_convenio != 17) {
		cout << "Convênio inválido. Deve ser 4, 5, 7 ou 17." << endl;
		return 1;
	} else {
		switch (tipo_convenio) {
			case 4:
			case 5:
			case 7:
				cout << "Informe o número do convênio: ";
				cin >> numero_convenio;
				cout << "Informe o número do nosso número: ";
				cin >> nosso_numero;
				cout << "Informe o número da carteira: ";
				cin >> carteira;
				cout << "Informe o número da agência: ";
				cin >> agencia;
				cout << "Informe o número da conta: ";
				cin >> numero_conta;
				break;
			case 17:
				cout << "Informe o convênio (até 17 dígitos): ";
				cin >> numero_convenio;
				cout << "Informe o nosso número (até 8 dígitos): ";
				cin >> nosso_numero;
				break;
		}
		// 45 a 47 - Convênio
		if (valida_dados_conveio(tipo_convenio, numero_convenio, nosso_numero, carteira, agencia, numero_conta, campo_livre)
			&& valida_dados(codigo_banco, codigo_moeda, data_vencimento, valor)) {
			string campo_livre_gerado = gera_campo_livre(tipo_convenio, numero_convenio, nosso_numero, carteira, agencia, numero_conta);
			cout << "\nCódigo de barras gerado: "
				<< gera_codigo_barras(codigo_banco, codigo_moeda, data_vencimento, valor, campo_livre_gerado)
				<< endl;
		} else {
			cout << "Código de barras não foi gerado." << endl;
			return 1;
		}
	}
	return 0;
}
