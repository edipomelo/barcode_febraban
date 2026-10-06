// funcoes utilizadas na codificacao / decodificacao
#include <iostream>
#include <string>
#include <format>
#include <chrono>

using namespace std;

int somardigitos(int n) // faz as somas dos dois algarismos caso seja maior que 10
{
	int dezena = n / 10;
	int unidade = n % 10;
	return dezena + unidade;
}

string tirarponto(string campo) // tira o ponto da linha digitável
{
	string resultado = "";
	for (char c : campo)
		if (c != '.')
			resultado += c;
	return resultado;
}

string conversao(string codedebarras) // converte o codigo de barras na linha digitavel sem os DV's
{
	string semDV = "";

	string codInsti = codedebarras.substr(0, 3);		// codigo da instituição
	string codMoed = codedebarras.substr(3, 1);			// codigo da moeda (9)
	string pos2024 = codedebarras.substr(19, 5);		// posições de 20 a 24 do codigo de barras
	string pos2534 = codedebarras.substr(24, 10);		// posições de 25 a 34 do codigo de barras
	string pos3544 = codedebarras.substr(34, 10);		// posições de 35 a 44 do codigo de barras
	string fatorvencimento = codedebarras.substr(5, 4); // fator vencimento
	string valorboleto = codedebarras.substr(9, 10);	// vaalorboleto

	semDV += codInsti;
	semDV += codMoed;
	semDV += pos2024;
	semDV += pos2534;
	semDV += pos3544;
	semDV += fatorvencimento;
	semDV += valorboleto;

	return semDV;
}

int calcmod10(string camposemponto)
{
	int soma = 0, multiplicador = 2;

	for (int i = (int)camposemponto.length() - 1; i >= 0; i--)
	{
		int valornovo, valor;							  // por multiplicador agora, estava com problemas no campo 2
		valor = (camposemponto[i] - '0') * multiplicador; // a primeira casa é multiplicada por 2
		if (valor >= 10)
		{
			valornovo = somardigitos(valor); // usa a função para somar os algarismos caso passe de 9
		}
		else
		{
			valornovo = valor;
		}
		soma += valornovo;							  // adiciona o valor na soma
		multiplicador = (multiplicador == 2) ? 1 : 2; // verifica se o ultimo valor multiplicado foi por 2
	}
	int resto = soma % 10;
	return (resto > 0) ? 10 - resto : 0; // caso o resto seja = 0, retorna 0, caso não faz 10 - resto
}

// calcula o dígito verificador de um número (MÓDULO 11)
int modulo11(string codigodebarras)
{
	// std::string cadigodebarrasNODV = codigodebarras.substr(0, 4) + codigodebarras.substr(5); // retira o digito verificador do módulo de 11
	//  OBS: a linha acima será removida, pois o código de barras vem sem o DV.
	int soma = 0;
	int multiplicador = 2; // começa no 2

	// for (int i = (int)cadigodebarrasNODV.length() - 1; i >= 0; i--) // percorre todo o codigo sem o DV
	for (int i = (int)codigodebarras.length() - 1; i >= 0; i--)
	{
		// int n = cadigodebarrasNODV[i] - '0'; // transforma em int
		int n = codigodebarras[i] - '0';
		soma += n * multiplicador;
		multiplicador++;
		if (multiplicador > 9) // impede do multiplicador passar de 9
			multiplicador = 2;
	}

	int resto = soma % 11;
	int dv = 11 - resto;

	return (dv == 0 || dv == 10 || dv == 11) ? 1 : dv; // caso dv seja igual a 0, 10 ou 11, retorna 1, caso não, 11 - resto
}

// calcula o dígito verificador de um número (MÓDULO 10)
int modulo10(std::string linhadigi, int campo)
{
	string linhasemponto = tirarponto(linhadigi); // tira todos os pontos da linha digitável sem os DV's

	switch (campo)
	{
	case 1:
	{
		string campo1 = linhasemponto.substr(0, 9); // Faz a fatiamento dos números do primeiro DV
		return calcmod10(campo1);
	}
	case 2:
	{
		string campo2 = linhasemponto.substr(9, 10); // Faz a fatiamento dos números do segundo DV
		return calcmod10(campo2);
	}
	case 3:
	{
		string campo3 = linhasemponto.substr(19, 10); // Faz a fatiamento dos números do terceiro DV
		return calcmod10(campo3);
	}
	default:
		return -1;
	}
}

string formatarlinhadigitavel(string codigo_barras)
{
	string linha_digitavel_semDV = conversao(codigo_barras);
	string DV_campo1 = to_string(modulo10(linha_digitavel_semDV, 1));
	string DV_campo2 = to_string(modulo10(linha_digitavel_semDV, 2));
	string DV_campo3 = to_string(modulo10(linha_digitavel_semDV, 3));
	string DV_principal = to_string(modulo11(codigo_barras));

	string linha_digitavel = linha_digitavel_semDV.substr(0, 5) + "." + linha_digitavel_semDV.substr(5, 4) + DV_campo1 + " " +
							 linha_digitavel_semDV.substr(9, 5) + "." + linha_digitavel_semDV.substr(14, 5) + DV_campo2 + " " +
							 linha_digitavel_semDV.substr(19, 5) + "." + linha_digitavel_semDV.substr(24, 5) + DV_campo3 + " " +
							 DV_principal + " " + linha_digitavel_semDV.substr(29, 4) + linha_digitavel_semDV.substr(33, 10);

	return linha_digitavel;
}

int fator_vencimento(string data_vencimento)
{
	// usando a biblioteca chrono para calcular a diferença de dias
	// baseado em exemplo encontrado via Google
	using namespace std::chrono;
	// divide a string em partes
	unsigned int dia = stoi(data_vencimento.substr(0, 2));
	unsigned int mes = stoi(data_vencimento.substr(3, 2));
	int ano = stoi(data_vencimento.substr(6, 4));

	// data de referência
	year_month_day ref{year{1997}, month{10}, day{7}};
	// vencimento
	year_month_day venc{year{ano}, month{mes}, day{dia}};

	// sys_days é um time_point baseado em dias desde 1970-01-01
	sys_days tp1 = ref;
	sys_days tp2 = venc;

	// diferença de dias
	auto diff = tp2 - tp1;
	// se > 9999, retorna para 1000
	if (diff.count() > 9999)
		return 1000 + diff.count() % 10000;
	else
		return diff.count() % 10000;
}

string data_vencimento_formatada(string codigo_barras) // retorna a data de vencimento no formato DD/MM/AAAA
{
	using namespace std::chrono;

	// copia o fator de vencimento do código de barras
	int fatorvencimento = stoi(codigo_barras.substr(5, 4));

	// data de referência
	year_month_day ref{year{1997}, month{10}, day{7}};
	sys_days tp1 = ref;

	// dia atual
	sys_days hoje = floor<days>(system_clock::now());

	// data do primeiro cliclo
	sys_days ciclo = tp1 + days{fatorvencimento};

	// enquanto a data estiver mais de 4500 dias (metade do ciclo)
	// no passado, pula para o próximo ciclo.
	while (ciclo < hoje - days{4500})
	{
		ciclo += days{9000};
	}

	year_month_day data{ciclo};

	string dia = to_string((unsigned)data.day());
	string mes = to_string((unsigned)data.month());
	if (mes.size() < 2)
		mes = "0" + mes;
	string ano = to_string((int)data.year());

	return dia + "/" + mes + "/" + ano;
}

string valor_formatado(string codigobarras) // retorna o valor no formato XXXXX,XX
{
	long long centavos = stoll(codigobarras.substr(9, 10));
	string reais = to_string(centavos / 100);
	string cents = to_string(centavos % 100);
	if (cents.size() < 2)
		cents = "0" + cents;
	return reais + "," + cents;
}

// retirado de: https://en.cppreference.com/cpp/chrono/parse
bool is_data_valida(string data) {
	istringstream is(data);
	std::chrono::year_month_day ymd;
    is >> std::chrono::parse("%d/%m/%Y", ymd);
	if (is.fail()) {
		cout << "Data inválida!" << endl;
		return false;
	}
	return true;
}

bool valida_dados(int cod_banco, int cod_moeda, string data_vencimento, string valor_boleto, string campo_livre) {
	bool result = true;
	// código do banco: 3 dígitos
	if (cod_banco < 1 || cod_banco > 999) {
		cout << "Código do banco inválido. Deve ser um número entre 1 e 999." << endl;
		result = false;
	}
	// código da moeda: 1 dígito
	if (cod_moeda < 1 || cod_moeda > 9) {
		cout << "Código da moeda inválido. Deve ser um número entre 1 e 9." << endl;
		result = false;
	}
	// data de vencimento: formato DD/MM/AAAA
	cout << "validando data de vencimento: " << data_vencimento << endl;
	if (data_vencimento.length() != 10 || data_vencimento[2] != '/' || data_vencimento[5] != '/') {
		cout << "Data de vencimento inválida. Deve estar no formato DD/MM/AAAA." << endl;
		result = false;
	} else if (!is_data_valida(data_vencimento)) {
			cout << "Data de vencimento inexistente." << endl;
			result = false;
		}
	// valor do boleto: formato XXXXX,XX
	if (valor_boleto.length() > 11 || valor_boleto[valor_boleto.length() - 3] != ',') {
		cout << "Valor do boleto inválido. Deve estar no formato XXXXX,XX e ter, no máximo 11 caracteres." << endl;
		result = false;
	}
	if (campo_livre.length() > 25) {
		cout << "Campo livre inválido. Deve ter, no máximo, 25 dígitos." << endl;
		result = false;
	}
	// campo livre: somente dígitos
	for (char c : campo_livre) {
		if (!isdigit(c)) {
			cout << "Campo livre inválido. Deve conter apenas dígitos." << endl;
			result = false;
		}
	}
	return result;
}

string gera_codigo_barras(int cod_banco, int cod_moeda, string data_vencimento, string valor_boleto, string campo_livre) {
	string result = "";
	// Posição | Tamanho | Picture   | Conteúdo
	// 01 a 03 | 03      | 9(03)     | Código do Banco na Câmara de Compensação = '001'
	result += format("{:03d}", cod_banco);
	// 04 a 04 | 01      | 9(01)     | Código da Moeda = 9 (Real)
	result += to_string(cod_moeda);
	// 05 a 05 | 01      | 9(01)     | Digito Verificador (DV) do código de Barras*
	// 06 a 09 | 04      | 9(04)     | Fator de Vencimento **
	result += format("{:04d}", fator_vencimento(data_vencimento));
	// 10 a 19 | 10      | 9(08)V(2) | Valor
	//valor_boleto = valor_boleto.replace(",", "").replace(".", ""); // remove vírgula ou ponto
	erase(valor_boleto, ',');
	erase(valor_boleto, '.'); // remove vírgula e ponto
	result += format("{:0>10}", valor_boleto); // preenche com zero a esquerda
	// 20 a 44 | 03      | 9(03)     | Campo Livre ***
	result += format("{:0>25}", campo_livre); // de 20 a 44 são 25
	int dv = modulo11(result);
	// monta o código de barras com o DV
	result = result.substr(0, 4) + to_string(dv) + result.substr(4,43);
	return result;
}