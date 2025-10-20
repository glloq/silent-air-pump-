/*
 * Contrôle de pompe à air par capteur de distance VL53L0X
 * avec seuil ajustable par potentiomètre
 */

#include <Wire.h>
#include <VL53L0X.h>

// ===== CONFIGURATION PINS =====
const int PIN_POTENTIOMETRE = A0;  // Entrée analogique potentiomètre
const int PIN_RELAIS = 7;           // Sortie relais pompe

// ===== PARAMÈTRES SYSTÈME =====
const int DISTANCE_MAX = 1000;      // Distance max en mm (1m)
const int DISTANCE_MIN = 200;       // Distance min en mm (20cm)
const float HYSTERESIS = 0.75;      // 75% pour réactivation

// ===== VARIABLES GLOBALES =====
VL53L0X capteurLaser;
int distanceMesuree = 0;
int seuilCoupure = 0;
int seuilReactivation = 0;
bool pompeActive = false;

// ===== SETUP =====
void setup() {
  // Initialisation communication série (debug)
  Serial.begin(9600);
  
  // Configuration des pins
  pinMode(PIN_RELAIS, OUTPUT);
  pinMode(PIN_POTENTIOMETRE, INPUT);
  digitalWrite(PIN_RELAIS, LOW);  // Pompe éteinte au démarrage
  
  // Initialisation I2C et capteur VL53L0X
  Wire.begin();
  capteurLaser.init();
  capteurLaser.setTimeout(500);
  
  // Configuration du capteur pour mesures rapides
  capteurLaser.setMeasurementTimingBudget(20000);
  
  Serial.println("Système initialisé");
}

// ===== BOUCLE PRINCIPALE =====
void loop() {
  // Lecture du potentiomètre (0-1023)
  int valeurPot = analogRead(PIN_POTENTIOMETRE);
  
  // Vérification interrupteur (si <50, considéré comme ouvert/OFF)
  if (valeurPot < 50) {
    couperPompe();
    Serial.println("Interrupteur ouvert - Système désactivé");
    delay(500);
    return;
  }
  
  // Calcul des seuils en fonction du potentiomètre
  calculerSeuils(valeurPot);
  
  // Lecture de la distance
  distanceMesuree = capteurLaser.readRangeSingleMillimeters();
  
  // Vérification erreur de lecture
  if (capteurLaser.timeoutOccurred()) {
    Serial.println("TIMEOUT capteur!");
    return;
  }
  
  // Logique de contrôle de la pompe
  controlerPompe();
  
  // Affichage debug
  afficherEtatSysteme();
  
  delay(100);  // Délai entre mesures
}

// ===== FONCTIONS =====

/**
 * Calcule les seuils de coupure et réactivation
 * basés sur la position du potentiomètre
 */
void calculerSeuils(int valeurPot) {
  // Interpolation linéaire entre MIN et MAX
  // valeurPot varie de 50 à 1023
  float ratio = (valeurPot - 50) / 973.0;  // Normalisation 0-1
  
  seuilCoupure = DISTANCE_MIN + (DISTANCE_MAX - DISTANCE_MIN) * ratio;
  seuilReactivation = seuilCoupure * HYSTERESIS;
}

/**
 * Logique de contrôle avec hystérésis
 */
void controlerPompe() {
  if (pompeActive) {
    // Pompe active : vérifier si on doit couper
    if (distanceMesuree >= seuilCoupure) {
      couperPompe();
    }
  } else {
    // Pompe inactive : vérifier si on doit réactiver
    if (distanceMesuree <= seuilReactivation) {
      activerPompe();
    }
  }
}

/**
 * Active la pompe
 */
void activerPompe() {
  digitalWrite(PIN_RELAIS, HIGH);
  pompeActive = true;
  Serial.println(">>> POMPE ACTIVÉE");
}

/**
 * Coupe la pompe
 */
void couperPompe() {
  digitalWrite(PIN_RELAIS, LOW);
  pompeActive = false;
  Serial.println(">>> POMPE COUPÉE");
}

/**
 * Affiche l'état du système (debug)
 */
void afficherEtatSysteme() {
  Serial.print("Distance: ");
  Serial.print(distanceMesuree);
  Serial.print(" mm | Seuil coupure: ");
  Serial.print(seuilCoupure);
  Serial.print(" mm | Seuil réactivation: ");
  Serial.print(seuilReactivation);
  Serial.print(" mm | Pompe: ");
  Serial.println(pompeActive ? "ON" : "OFF");
}