# Estação de Monitoramento de Temperatura, Umidade e Luminosidade

Projeto desenvolvido para monitorar em tempo real as condições ambientais (temperatura, umidade e luminosidade) e registrar os dados em um banco de dados. O sistema utiliza o Arduino Uno R3 para processar as leituras dos sensores e enviar os dados para armazenamento e análise.

## Materiais Utilizados
- **Arduino Uno R3** – Microcontrolador utilizado no projeto.
- **Sensor DHT11** – Responsável pela medição de temperatura e umidade.
- **Sensor LDR (Fotoresistor)** – Utilizado para captar o nível de luminosidade.
- **Resistor de 10kΩ** – Usado no divisor de tensão junto ao LDR.
- **Protoboard e Jumpers** – Componentes para montagem e realização das conexões do circuito.

## Descrição do Projeto
Esta estação de monitoramento foi criada com o objetivo de:
- Capturar e monitorar em tempo real os dados de **temperatura**, **umidade** e **luminosidade**.
- Registrar as medições em um **banco de dados** para análises futuras.
- Oferecer uma solução acessível e simples para projetos de automação e monitoramento ambiental.

O projeto pode ser adaptado para diversas aplicações, como monitoramento de estufas, laboratórios ou ambientes residenciais, contribuindo para a análise e controle das condições ambientais.

## Funcionalidades
- **Leitura dos Sensores:** Coleta contínua dos dados do DHT11 e LDR.
- **Registro em Banco de Dados:** Armazenamento das medições para análise histórica e geração de gráficos.
- **Monitoramento em Tempo Real:** Atualização imediata dos dados medidos, possibilitando o acompanhamento ao vivo das condições ambientais.

## Esquema de Conexões

### Conexões do DHT11:
- **VCC:** Conectar ao pino de 5V do Arduino.
- **GND:** Conectar ao GND do Arduino.
- **Data:** Conectar a um pino digital (configurável via código).

### Conexões do LDR:
- **LDR e Resistor de 10kΩ:** Montados em um divisor de tensão.
  - Conectar uma extremidade do LDR aos 5V.
  - Conectar a outra extremidade do LDR à entrada analógica do Arduino através do resistor de 10kΩ.
  - O outro terminal do resistor deve ser conectado ao GND.
  
