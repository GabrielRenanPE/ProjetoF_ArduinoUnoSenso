import serial
import sqlite3
import json
from datetime import datetime

# Configurações
CONFIG_FILE = 'sensor_config.json'
DATABASE_FILE = 'sensor_data.db'
SERIAL_PORT = 'COM7'  # Altere para sua porta
BAUD_RATE = 9600

class GerenciadorDados:
    def __init__(self):
        self.conexao = sqlite3.connect(DATABASE_FILE)
        self.criar_tabela()
        self.carregar_config()

    def criar_tabela(self):
        cursor = self.conexao.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS leituras (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            timestamp DATETIME NOT NULL,
                            temperatura REAL NOT NULL,
                            umidade REAL NOT NULL,
                            luminosidade INTEGER NOT NULL,
                            limite_luminosidade INTEGER NOT NULL)''')
        self.conexao.commit()

    def carregar_config(self):
        try:
            with open(CONFIG_FILE, 'r') as f:
                self.config = json.load(f)
        except FileNotFoundError:
            self.config = {'limite_luminosidade': 1000}
            self.salvar_config()

    def salvar_config(self):
        with open(CONFIG_FILE, 'w') as f:
            json.dump(self.config, f)

    def salvar_dados(self, dados):
        cursor = self.conexao.cursor()
        cursor.execute('''INSERT INTO leituras 
                          (timestamp, temperatura, umidade, luminosidade, limite_luminosidade)
                          VALUES (?, ?, ?, ?, ?)''', dados)
        self.conexao.commit()

    def fechar_conexoes(self):
        self.conexao.close()

class InterfaceSerial:
    def __init__(self, gerenciador):
        self.gerenciador = gerenciador
        self.ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)

    def processar_dados(self):
        try:
            while True:
                if self.ser.in_waiting > 0:
                    linha = self.ser.readline().decode().strip()
                    
                    if linha == 'ARDUINO_STARTED':
                        self.enviar_configuracao()
                    
                    elif linha.startswith('CONFIG_LUM:'):
                        self.atualizar_configuracao(linha)
                    
                    elif linha.startswith('DATA,'):
                        self.processar_leituras(linha)
                    
                    elif linha:
                        print(f"Log: {linha}")

        except KeyboardInterrupt:
            self.sair()

    def enviar_configuracao(self):
        comando = f"SET LUM {self.gerenciador.config['limite_luminosidade']}\n"
        self.ser.write(comando.encode())
        print("Configuração enviada ao Arduino")

    def atualizar_configuracao(self, linha):
        novo_limite = int(linha.split(':')[1])
        self.gerenciador.config['limite_luminosidade'] = novo_limite
        self.gerenciador.salvar_config()
        print(f"Novo limite salvo: {novo_limite}")

    def processar_leituras(self, linha):
        partes = linha.split(',')
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        temperatura = float(partes[1])  # Temperatura
        umidade = float(partes[2])      # Umidade
        luminosidade = int(partes[3])   # Luminosidade
        limite = int(partes[4])         # Limite

        dados = (
            timestamp,
            temperatura,
            umidade,
            luminosidade,
            limite
        )
        self.gerenciador.salvar_dados(dados)
    
        # Determinar o status com base nos dados recebidos
        status = "ALERTA: Luz acima do limite!" if luminosidade > limite else "STATUS: Luz dentro do normal"
    
        # Saída formatada
        print(f"Temperatura: {temperatura:.2f} °C\t| Umidade: {umidade:.2f} %\t| Luminosidade: {luminosidade}\t| Limite: {limite}")
        print(f"Status: {status}\n")

    def sair(self):
        self.ser.close()
        self.gerenciador.fechar_conexoes()
        print("Sistema encerrado")

if __name__ == "__main__":
    gerenciador = GerenciadorDados()
    interface = InterfaceSerial(gerenciador)
    print("Monitoramento iniciado...")
    interface.processar_dados()
