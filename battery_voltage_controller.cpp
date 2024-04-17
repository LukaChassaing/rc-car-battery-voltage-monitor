#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

const int batteryPin = 34;       // Broche de lecture de tension batterie
const int powerPin = 25;         // Broche de commande de l'alimentation
const float minVoltage = 3.0;    // Tension min par cellule (seuil d'alerte)
const float maxVoltage = 4.2;    // Tension max par cellule (seuil de charge)
const int numCells = 2;          // Nombre de cellules lithium en série

// Structure des données à envoyer
typedef struct struct_message {
  float cellVoltage;
  bool voltageAlert;
} struct_message;

struct_message voltageData;

// Adresse MAC de l'ESP32 récepteur (à modifier)
uint8_t receiverAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Callback de transmission des données
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Statut d'envoi : ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Succès" : "Échec");
}

void setup() {
  Serial.begin(115200);
  
  // Configuration des broches
  pinMode(batteryPin, INPUT);
  pinMode(powerPin, OUTPUT);
  
  // Initialisation WiFi
  WiFi.mode(WIFI_STA);
  
  // Initialisation ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur d'initialisation ESP-NOW");
    return;
  }
  
  // Enregistrement du callback de transmission
  esp_now_register_send_cb(OnDataSent);
  
  // Enregistrement de l'ESP32 récepteur
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Erreur d'ajout du récepteur");
    return;
  }
}

void loop() {
  // Lecture de la tension
  int rawValue = analogRead(batteryPin);
  
  // Conversion en millivolts
  float milliVolts = rawValue * (3300.0 / 4095.0);
  
  // Calcul de la tension par cellule
  float cellVoltage = milliVolts / numCells / 1000;
  
  // Affichage du résultat
  Serial.print("Tension par cellule: ");
  Serial.print(cellVoltage);
  Serial.println(" V");
  
  // Vérification des seuils
  bool voltageAlert = false;
  if (cellVoltage < minVoltage || cellVoltage > maxVoltage) {
    voltageAlert = true;
    Serial.println("Alerte de tension !");
    
    // Coupure de l'alimentation
    digitalWrite(powerPin, LOW);
    Serial.println("Alimentation coupée !");
  }
  else {
    // Maintien de l'alimentation
    digitalWrite(powerPin, HIGH);
  }
  
  // Préparation des données à envoyer
  voltageData.cellVoltage = cellVoltage;
  voltageData.voltageAlert = voltageAlert;
  
  // Envoi des données via ESP-NOW
  esp_err_t result = esp_now_send(receiverAddress, (uint8_t *) &voltageData, sizeof(voltageData));
  
  if (result == ESP_OK) {
    Serial.println("Données envoyées avec succès");
  }
  else {
    Serial.println("Erreur d'envoi des données");
  }
  
  delay(1000);  // Attente de 1 seconde
}
