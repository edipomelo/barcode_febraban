# barcode_febraban - uma biblioteca para Código de Barras FEBRABAN.

Implementação em C++ do padrão FEBRABAN para códigos de barras de boletos bancários (somente texto).

Esta implementação, realizada como trabalho da disciplina DIM0176 - PROGRAMAÇÃO I - T02 (2026.2)/ UFRN, consistirá de duas funções principais para codificar dados estruturados em um código de barras e vice-versa.

## O Codificador

O codificador deve ler uma sequencia de registros para os quais devem ser codificados os códigos de barras. Cada registro contém os dados correspondentes a um boleto:

- Código do banco;
- Moeda;
- Data de vencimento (dia/mes/ano, na forma DD/MM/AAAA);
- valor;
- tipo de convenio (04, 05, 07 posiçõees ou livre com 17 posições). Ver [Especificações Técnicas para Confecção de Boleto de Pagamento do Banco do Brasil](https://www.bb.com.br/docs/pub/emp/empl/dwn/Doc5175Bloqueto.pdf);
- Dados específicos para cada tipo de convênio.

A saída consistirá de duas linhas texto, a primeira gerar o um código de barras (44 dígitos), e a segunda sendo a linha digitável do mesmo código (47 dígitos).

## O decodificador

O decodificador fará o caminho inverso do codificador, ou seja, receberá uma sequencia de 44 dígitos (corresponde ao código de barras), e irá devolver:
- Linha digitável;
- Código do banco;
- Moeda;
- Data de vencimento (dia/mês/ano, na forma DD/MM/AAAA);
- valor;
- tipo de convenio (04, 05, 07 posições ou livre com 17 posições). Ver [Especificações Técnicas para Confecção de Boleto de Pagamento do Banco do Brasil](https://www.bb.com.br/docs/pub/emp/empl/dwn/Doc5175Bloqueto.pdf);
- Dados específicos para cada tipo de convênio.

# Licença de uso

Este projeto é licenciado sob a GNU General Public License (GPL), que permite executar, estudar, modificar e redistribuir o software para qualquer finalidade. Ao redistribuir o programa ou versões modificadas, você deve manter os avisos de copyright e de licença, disponibilizar o código-fonte correspondente e licenciar as obras derivadas sob a mesma GPL, impedindo que se tornem proprietárias. Consulte o arquivo LICENSE para o texto completo da licença.

# Autores

|                 | Édipo Melo | Vinicius Cavalcanti |
|-----------------|------------|---------------------|
| % implementação |          - |                   - | 
