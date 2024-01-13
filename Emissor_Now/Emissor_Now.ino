//FirmeWare: Emissor ESP-NOW com NodeMCU
//Autor: Elismar Silva.
//Data: 13-01-2024
//Ciência da Computação - UDF

#include <ESP8266WiFi.h>
#include <espnow.h>

//Endereço Mac do Receptor Esp8266
uint8_t broadcastAddress[] = {0x08,0x3A,0x8D,0xD3,0x6D,0x39};


typedef struct struct_message {
  char command; // Comando do botão pressionado ('F', 'E', 'D', 'T', 'P')
} struct_message;

#define pino_botao_F D2
#define pino_botao_E D3
#define pino_botao_D D4
#define pino_botao_T D5
#define pino_botao_P D6

struct_message myData;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Status dos dados enviados: ");
  if (sendStatus == 0) {
    Serial.println("Envio ok!");
  } else {
    Serial.println("Falha no envio!");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(pino_botao_F, INPUT_PULLUP);
  pinMode(pino_botao_E, INPUT_PULLUP);
  pinMode(pino_botao_D, INPUT_PULLUP);
  pinMode(pino_botao_T, INPUT_PULLUP);
  pinMode(pino_botao_P, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Erro ao inicializar o ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  if (!digitalRead(pino_botao_F) == HIGH) {
    myData.command = 'F';
  } else if (!digitalRead(pino_botao_E) == HIGH) {
    myData.command = 'E';
  } else if (!digitalRead(pino_botao_D) == HIGH) {
    myData.command = 'D';
  } else if (!digitalRead(pino_botao_T) == HIGH) {
    myData.command = 'T';
  } else if (!digitalRead(pino_botao_P) == HIGH) {
    myData.command = 'P';
  } else {
    // Nenhum botão pressionado, envia um comando de parar por padrão
    myData.command = 'P';
  }

  esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

  delay(50); // Adicione um pequeno atraso entre leituras para evitar leituras falsas devido a oscilações nos botões
}
