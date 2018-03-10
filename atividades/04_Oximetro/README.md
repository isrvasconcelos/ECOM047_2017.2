# CaduceOz
![](https://github.com/tenoriomatheus/ECOM047_2017.2/blob/master/atividades/04_Oximetro/logo.png)

Este projeto consiste em um oximetro portátil. Este Oxímetro possui uma bateria recarregável de 1200mAh. Esta bateria pode ser recarregada através de uma entrada micro-USB. Este dispositivo possui alguns meios de intereção com o usuário, tal como:
* **Display** - responsável para mostrar ao usuário os valores de SpO2 (Saturação do Oxigênio no Sangue) e BPM (Batimentos por minutos) amostrados.
* **Botões** - responsáveis por:
    * Iniciar uma nova medição
    * Ativar o Bluetooth
* **Conexão Bluetooth** - responsável por enviar para o usuário os dados amostrados pelo dispositivo.

## Requisitos Funcionais

* Este dispositivo deve operar numa tensão na faixa de 2.8V-3.3V, e entrar no modo _sleep_ sempre que possível.
* O display utilizado deve ser um display com baixo consumo de energia. O display deve possuir no máximo 3.5 polegadas.
    * Este display pode utilizar qualquer tecnologia (e-ink, TFT, OLED, etc)
* Serão utilizados 2 botões, do tipo push-button. Cada um dos botões irá realizar uma das ações descritas acima.
* O dispositivo deve conter um CI com Bluetooth, do tipo BLE.
* O dispositivo deve possuir um CI capaz de medir o nível da bateria.
* O processador deve ser capaz de se comunicar com os CIs descrito nos itens anteriores. Assim, se um CI utilizar I2C, o processador deve possuir esta comunicação disponível.
* Para cada CI escolhido será necessário 2 capacitores de _decoupling_, com capacitâncias igual a 1uF e 0,1uF.
* Para realizar a amostragem dos dados de SpO2 e BPM, será necessário dois LEDs e um photodiodo. Um dos LEDs será vermelho e o outro será Infravermelho (IR).
* O dispositivo deve possuir uma entrada micro-USB, para o carregamento. Assim, deve conter um conector micro-USB, do tipo fêmea.

## Requisitos Não-Funcionais

* O custo máximo de 1 unidade do projeto (produzindo 1 unidade no total, com frete) deve ser de R$351,00
* O custo máximo de 1 unidade do projeto (produzindo 1000 unidade no total, com frete) deve ser de R$340,00
* O consumo máximo de energia do projeto deve ser no máximo 19mA, considerando o dispositivo no modo execução.
* O tempo máximo de entrega deste projeto é de 2 semanas
