//FirmeWare: Receptor ESP-NOW com NodeMCU
//Autor: Elismar Silva.
//Data: 13-01-2024
//Ciência da Computação - UDF

#include <ESP8266WiFi.h>
#include <espnow.h>

typedef struct struct_message {
  char command; // Comando do botão pressionado ('F', 'E', 'D', 'T', 'P')
} struct_message;

#define pino_led 2

struct_message myData;

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));

  Serial.println();
  Serial.print("Bytes recebidos: ");
  Serial.println(len);
  Serial.print("Comando recebido: ");
  Serial.println(myData.command);

  // Executa ação com base no comando recebido
  switch (myData.command) {
    case 'F':
      digitalWrite(pino_led,0);
      Serial.println("Recebido comando: Frente!");
      // Adicione a lógica para avançar
      break;
    case 'E':
      Serial.println("Recebido comando: Esquerda!");
       //digitalWrite(pino_led,1);
      // Adicione a lógica para girar à esquerda
      break;
    case 'D':
      Serial.println("Recebido comando: Direita!");
      // Adicione a lógica para girar à direita
      break;
    case 'T':
      Serial.println("Recebido comando: Trás!");
      // Adicione a lógica para recuar
      break;
    case 'P':
      Serial.println("Recebido comando: Parado!");
      digitalWrite(pino_led,1);
      // Adicione a lógica para parar
      break;
    default:
      Serial.println("Comando desconhecido!");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(pino_led, OUTPUT);
  digitalWrite(pino_led, HIGH);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Erro ao inicializar o ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Neste programa, não temos comandos no loop
}
