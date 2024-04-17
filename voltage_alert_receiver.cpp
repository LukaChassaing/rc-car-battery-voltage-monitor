#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// Structure des données reçues
typedef struct struct_message {
  float cellVoltage;
  bool voltageAlert;
} struct_message;

struct_message voltageData;

// Callback de réception des données
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&voltageData, incomingData, sizeof(voltageData));
  Serial.print("Tension par cellule reçue : ");
  Serial.println(voltageData.cellVoltage);
  Serial.print("Alerte de tension : ");
  Serial.println(voltageData.voltageAlert ? "Oui" : "Non");
}

void setup() {
  Serial.begin(115200);
  
  // Initialisation WiFi
  WiFi.mode(WIFI_STA);
  
  // Initialisation ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur d'initialisation ESP-NOW");
    return;
  }
  
  // Enregistrement du callback de réception
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Vérification de l'alerte de tension
  if (voltageData.voltageAlert) {
    Serial.println("Alerte de tension reçue !");
    // Ici, tu peux ajouter du code pour déclencher une alarme ou afficher un message sur l'écran de la radio Taranis QX7
  }
  
  delay(100);  // Attente de 100 ms
}
