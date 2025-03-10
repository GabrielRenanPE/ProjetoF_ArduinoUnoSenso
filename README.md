# Estação de Monitoramento de Temperatura, Umidade e Luminosidade

Projeto desenvolvido para monitorar em tempo real as condições ambientais (temperatura, umidade e luminosidade) e registrar os dados em um banco de dados. O sistema utiliza o Arduino Uno R3 para processar as leituras dos sensores e enviar os dados para armazenamento e análise.

## Materiais Utilizados
- **Arduino Uno R3** – Microcontrolador utilizado no projeto.
- **Sensor DHT11** – Responsável pela medição de temperatura e umidade.
- **Sensor LDR (Fotoresistor)** – Utilizado para captar o nível de luminosidade.
- **Resistor de 10kΩ** – Usado no divisor de tensão junto ao LDR.
- **Protoboard e Jumpers** – Componentes para montagem e realização das conexões do circuito.

## Links dos Arquivos
- **Código Python:** [ProgramaPython](https://github.com/GabrielRenanPE/ProjetoF_ArduinoUnoSenso/blob/main/ProgramaPython)
- **Código Arduino:** [CodigoArduino](https://github.com/GabrielRenanPE/ProjetoF_ArduinoUnoSenso/blob/main/CodigoArduino)

## Descrição do Projeto
Esta estação de monitoramento foi criada com o objetivo de:
- Capturar e monitorar em tempo real os dados de **temperatura**, **umidade** e **luminosidade**.
- Registrar as medições em um **banco de dados** para análises futuras.
- Oferecer uma solução acessível e simples para projetos de automação e monitoramento ambiental.

O projeto pode ser adaptado para diversas aplicações, como monitoramento de estufas, laboratórios ou ambientes residenciais, contribuindo para a análise e controle das condições ambientais.

## Instruções de Uso

### Instalação de Dependências

bash
Copy
pip install pyserial
Executar o Sistema:

Conecte o Arduino

Execute o script Python

Os dados serão armazenados em:

Banco de dados: sensor_data.db

Configurações: sensor_config.json

Visualizar Dados:
Use o DB Browser for SQLite ou execute:

python
Copy
import sqlite3

con = sqlite3.connect('sensor_data.db')
cur = con.cursor()
cur.execute("SELECT * FROM leituras")
for linha in cur.fetchall():
    print(linha)
con.close()
Principais Melhorias:
Sistema Modular:

Classes separadas para gestão de dados e comunicação serial

Tratamento de erros robusto

Persistência de Dados:

Configurações mantidas entre reinicializações

Histórico completo de leituras

Protocolo de Comunicação:

Identificadores claros (DATA,, CONFIG_LUM:, ARDUINO_STARTED)

Sincronização automática de configurações

Interface de Log:

Mensagens explicativas no console

Timestamps precisos nos registros
