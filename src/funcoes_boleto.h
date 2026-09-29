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

int calcmod10(string camposemponto)
{
	int soma = 0;

	for (int i = 0; i < (int)camposemponto.length(); i++)
	{
		int valor;
		if (i % 2 == 0) // posição par multiplica por 2
			valor = (camposemponto[i] - '0') * 2;
		else // posição par multiplica por 2
			valor = (camposemponto[i] - '0') * 1;

		int valornovo;
		if (valor >= 10)
		{
			valornovo = somardigitos(valor);
		}
		else
		{
			valornovo = valor;
		}
		soma += valornovo;
	}
	return soma % 10;
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

// calcula o dígito verificador de um número (MÓDULO 10)
int modulo10(string linhadigi, int campo)
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

// calcula o dígito verificador de um número (MÓDULO 11)
int modulo11(string codigodebarras)
{
	int soma = 0;
	int multiplicador = 2;

	for (int i = (int)codigodebarras.length() - 1; i >= 0; i--)
	{
		int n = codigodebarras[i] - '0'; // transforma em int
		soma += n * multiplicador;
		multiplicador++;
		if (multiplicador > 9) // impede do multiplicador passar de 9
			multiplicador = 2;
	}

	int resto = soma % 11;
	int dv = 11 - resto;

	if (dv == 0 || dv == 10 || dv == 11) // regra especial do boleto
		dv = 1;

	return dv;
}

int fator_vencimento(string data_vencimento){
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

