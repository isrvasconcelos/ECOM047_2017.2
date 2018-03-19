# Comando AT

## Descrição

Nesta atividade vamos implementar uma biblioteca capaz de realizar a comunicação entre um computador e um 
microcontrolador, através do padrão Comando AT.

O comando AT é um padrão simples que permite o envio de comandos com, ou sem, parâmetros. O formato desse padrão é 
descrito a seguir:

* AT
* AT+<Comando>
* AT+<Comando>=<Parâmetro1>,<Parâmetro2>,...,<ParâmetroN>

O primeiro item é um comando utilizado para testar a comunicação com o microcontrolador;
O segundo item é um comando sem parâmetros. Sendo <Comando> uma string qualquer representando um comando.
O terceiro item é um comando com parâmetros. Sendo <Comando> uma string qualquer representando um comando e <ParâmetroX> 
representando o x-ésimo parâmetro do comando <Comando>.

Como convenção, <Comando> é composto por letras maiúscula. Os parâmetros podem ser de dois tipos: numérico ou string. 
Os parâmetros do tipo string devem estar começar e terminar com aspas duplas.

Cada comando enviado para o microcontrolador possui dois tipos de resposta. A primeira resposta é OK, quando o comando 
segue um dos formatos descritos acima e está registrado no microcontrolador. A segunda resposta possível é FAIL, quando 
as o formato descrito acima não é respeitado, ou o comando não está registrado no microcontrolador. 

O registro de um comando na biblioteca é feito através do:

* Nome do comando;
* Callback, que será invocado quando a biblioteca receber o comando;
* Quantidade de parâmetros;
* Os tipos de cada parâmetros.

Para testar esta biblioteca, podem ser utilizadas os arquivos de teste ‘ICLEDMatrix’, disponibilizados na pasta 
‘05_ATCommand’, no GitHub da disciplina. __Este código deve ser implementado na microbit, utilizando zephyr__.

## Entregáveis

O código fonte contendo:

* O nome do aluno (comentado)
* A implementação do Comando AT

A entrega deve ser feita no classroom através de: uma pasta zipada (com o nome do aluno), ou um link para um 
repositório do GitHub.

## Anulação da Atividade

* Cópia de outro aluno
* Falta do nome do aluno no código fonte
* Código que não estiver compilando
