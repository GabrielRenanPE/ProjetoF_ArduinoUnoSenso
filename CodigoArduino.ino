// DHT.h biblioteca para funcionamento do DHT11 - Library used on Arduino IDE:https://github.com/adafruit/DHT-sensor-library
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define LUMIN_PIN A0

DHT dht(DHTPIN, DHTTYPE);

int limiteLuminosidade = 200;
bool novaConfiguracao = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  dht.begin();
  Serial.println("ARDUINO_STARTED");  // Identificador de inicialização
  Serial.println("\nSistema de Monitoramento Iniciado\n");
  Serial.println("Comandos disponíveis:");
  Serial.println("SET LUM <valor> - Ajustar nível de luminosidade");
  Serial.print("Limite atual de luminosidade: ");
  Serial.println(limiteLuminosidade);
}

void loop() {
  verificarComandos();
  
  if (novaConfiguracao) {
    Serial.print("CONFIG_LUM:");  // Envia nova configuração confirmada
    Serial.println(limiteLuminosidade);
    novaConfiguracao = false;
  }

  delay(2000);

  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();
  int luminosidade = analogRead(LUMIN_PIN);

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("ERRO: Leitura do sensor DHT falhou!");
    return;
  }

  // Envia dados
  Serial.print("DATA,");
  Serial.print(temperatura);
  Serial.print(",");
  Serial.print(umidade);
  Serial.print(",");
  Serial.print(luminosidade);
  Serial.print(",");
  Serial.println(limiteLuminosidade);

  // Verificação de luminosidade
  if(luminosidade > limiteLuminosidade) {
    Serial.println("ALERTA: Luz acima do limite!");
  } else {
    Serial.println("STATUS: Luz dentro do normal");
  }
}

void verificarComandos() {
  if(Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    
    if(comando.startsWith("SET LUM")) {
      int novoValor = comando.substring(7).toInt();
      if(novoValor >= 0 && novoValor <= 1023) {
        limiteLuminosidade = novoValor;
        novaConfiguracao = true;
      } else {
        Serial.println("ERRO: Valor deve estar entre 0-1023");
      }
    }
    else {
      Serial.println("ERRO: Comando inválido");
    }
  }
}
