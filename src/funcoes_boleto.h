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
	string DV_principal = codigo_barras.substr(4, 1); // extrai o DV do código de barras

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

	// Data usada para referência de datas de vencimento que sucedem a data de 22/02/2025. De acordo com a Febraban, o fator de vencimento será reiniciado a partir desta data.
	year_month_day ref{year{2025}, month{2}, day{23}};
	sys_days dataref = ref;

	// calcula a data de vencimento a partir do fator de vencimento
	sys_days DataCerta = dataref + days{fatorvencimento - 1001};

	year_month_day data{DataCerta};

	// Passa as de sys_days para string e formata a data no formato DD/MM/AAAA
	string dia = to_string((unsigned)data.day());
	string mes = to_string((unsigned)data.month());
	if (mes.size() < 2)
		mes = "0" + mes;
	if (dia.size() < 2)
		dia = "0" + dia;
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

// ajustado para o padrão POSICS (a versão anterior no MacOS não compila com clang sem erro)
bool is_data_valida(string data)
{
	    struct tm tm = {};
    // strptime retorna NULL se o formato não casar
    if (strptime(data.c_str(), "%d/%m/%Y", &tm) == NULL)
    {
        cout << "Data inválida!" << endl;
        return false;
    }

    // Verifica se a data existe de fato (ex.: rejeita 31/02/2024)
    tm.tm_isdst = -1;
    time_t t = mktime(&tm);
    if (t == -1)
        return false;

    // mktime normaliza campos inválidos; se mudou, a data era inexistente
    struct tm *v = localtime(&t);
    if (v->tm_mday != tm.tm_mday || v->tm_mon != tm.tm_mon || v->tm_year != tm.tm_year)
    {
        cout << "Data inexistente!" << endl;
        return false;
    }

    return true;
}

bool valida_dados_conveio(int tipo_convenio, string numero_convenio, string nosso_numero, 
	string carteira, string agencia, string numero_conta, string campo_livre) {
	bool result = true;
	// campo livre: somente dígitos
	for (char c : campo_livre) {
		if (!isdigit(c)) {
			cout << "Campo livre inválido. Deve conter apenas dígitos." << endl;
			result = false;
		}
	}
	// comum para todos, exceto convênio 17: [nosso número 11][carteira 2][agência 4]
	if (tipo_convenio != 17) {
		if (nosso_numero.length() == 0 || nosso_numero.length() > 11) {
			cout << "Nosso número inválido. Deve ter, no máximo, 11 dígitos." << endl;
			result = false;
		}
		if (carteira.length() == 0 || carteira.length() > 2) {
			cout << "Carteira inválida. Deve ter, no máximo, 2 dígitos." << endl;
			result = false;
		}
		if (agencia.length() == 0 || agencia.length() > 4) {
			cout << "Agência inválida. Deve ter, no máximo, 4 dígitos." << endl;
			result = false;
		}
	}
	switch (tipo_convenio) { 
		//Convênio 04: [convênio 4][conta 4] 
		case 4: 
			if (numero_convenio.length() == 0 || numero_convenio.length() > 4) {
				cout << "Convênio inválido. Deve ter, no máximo, 4 dígitos." << endl;
				result = false;
			}
			if (numero_conta.length() == 0 || numero_conta.length() > 4) {
				cout << "Número da conta inválido. Deve ter, no máximo, 4 dígitos." << endl;
				result = false;
			}
			break;
		//Convênio 05: [convênio 5][conta 3] → soma 25
		case 5:
			if (numero_convenio.length() == 0 || numero_convenio.length() > 5) {
				cout << "Convênio inválido. Deve ter, no máximo, 5 dígitos." << endl;
				result = false;
			}
			if (numero_conta.length() == 0 || numero_conta.length() > 3) {
				cout << "Número da conta inválido. Deve ter, no máximo, 3 dígitos." << endl;
				result = false;
			}
			break;
		// Convênio 07: [convênio 7][conta 1] → soma 25
		case 7:
			if (numero_convenio.length() == 0 || numero_convenio.length() > 7) {
				cout << "Convênio inválido. Deve ter, no máximo, 7 dígitos." << endl;
				result = false;
			}
			if (numero_conta.length() != 1) {
				cout << "Número da conta inválido. Deve ter 1 dígito." << endl;
				result = false;
			}
			break;
		// 	Livre 17: [convênio 17][nosso número 8]
		case 17:
			if (numero_convenio.length() == 0 || numero_convenio.length() > 17) {
				cout << "Convênio inválido. Deve ter, no máximo, 17 dígitos." << endl;
				result = false;
			}
			if (nosso_numero.length() == 0 || nosso_numero.length() > 8) {
				cout << "Nosso número inválido. Deve ter, no máximo, 8 dígitos." << endl;
				result = false;
			}
			break;
	}
	return result;
}

bool valida_dados(int cod_banco, int cod_moeda, string data_vencimento, string valor_boleto)
{
	bool result = true;
	// código do banco: 3 dígitos
	if (cod_banco < 1 || cod_banco > 999)
	{
		cout << "Código do banco inválido. Deve ser um número entre 1 e 999." << endl;
		result = false;
	}
	// código da moeda: 1 dígito
	if (cod_moeda < 1 || cod_moeda > 9)
	{
		cout << "Código da moeda inválido. Deve ser um número entre 1 e 9." << endl;
		result = false;
	}
	// data de vencimento: formato DD/MM/AAAA
	cout << "\nValidando data de vencimento: " << data_vencimento << endl;
	if (data_vencimento.length() != 10 || data_vencimento[2] != '/' || data_vencimento[5] != '/')
	{
		cout << "Data de vencimento inválida. Deve estar no formato DD/MM/AAAA." << endl;
		result = false;
	}
	else if (!is_data_valida(data_vencimento))
	{
		cout << "Data de vencimento inexistente." << endl;
		result = false;
	}
	// valor do boleto: formato XXXXX,XX
	if (valor_boleto.length() < 3 || valor_boleto.length() > 11 || valor_boleto[valor_boleto.length() - 3] != ',')
	{
		cout << "Valor do boleto inválido. Deve estar no formato XXXXX,XX e ter, no máximo 11 caracteres." << endl;
		result = false;
	}
	return result;
}

	// Gera o campo livre (25 dígitos) do código de barras a partir dos dados do convênio.
	// tipo_convenio: 4, 5, 7 (tamanho do número do convênio) ou 17 (livre).
	// Retorna string vazia se o tipo for inválido.
string gera_campo_livre(int tipo_convenio, string numero_convenio,
                        string nosso_numero, string carteira,
                        string agencia, string numero_conta) {
    switch (tipo_convenio) {
		case 4:
			return format("{:0>4}",  numero_convenio)
				+ format("{:0>11}", nosso_numero)
				+ format("{:0>2}",  carteira)
				+ format("{:0>4}",  agencia)
				+ format("{:0>4}",  numero_conta);   // 4+11+2+4+4 = 25
		case 5:
			return format("{:0>5}",  numero_convenio)
				+ format("{:0>11}", nosso_numero)
				+ format("{:0>2}",  carteira)
				+ format("{:0>4}",  agencia)
				+ format("{:0>3}",  numero_conta);   // 5+11+2+4+3 = 25
		case 7:
			return format("{:0>7}",  numero_convenio)
				+ format("{:0>11}", nosso_numero)
				+ format("{:0>2}",  carteira)
				+ format("{:0>4}",  agencia)
				+ format("{:0>1}",  numero_conta);   // 7+11+2+4+1 = 25
		case 17:
			return format("{:0>17}", numero_convenio)
				+ format("{:0>8}",  nosso_numero);    // 17+8 = 25	
    }
	throw invalid_argument("Tipo de convênio inválido. Deve ser 4, 5, 7 ou 17.");
}

string gera_codigo_barras(int cod_banco, int cod_moeda, string data_vencimento, string valor_boleto, string campo_livre)
{
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
	// valor_boleto = valor_boleto.replace(",", "").replace(".", ""); // remove vírgula ou ponto
	erase(valor_boleto, ',');
	erase(valor_boleto, '.');				   // remove vírgula e ponto
	result += format("{:0>10}", valor_boleto); // preenche com zero a esquerda
	// 20 a 44 | 03      | 9(03)     | Campo Livre ***
	result += format("{:0>25}", campo_livre); // de 20 a 44 são 25
	int dv = modulo11(result);
	// monta o código de barras com o DV
	result = result.substr(0, 4) + to_string(dv) + result.substr(4, 43);
	return result;
}