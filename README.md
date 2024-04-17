# Système de surveillance de tension de batterie pour voiture RC avec alerte via ESP-NOW

Ce projet est un système de surveillance de tension de batterie conçu spécifiquement pour les voitures radiocommandées (RC). Il utilise deux modules ESP32 communicant via le protocole ESP-NOW pour surveiller la tension de la batterie et envoyer des alertes en cas de problème.

## Fonctionnalités

- Mesure en temps réel de la tension de la batterie de la voiture RC
- Détection des seuils de tension minimale et maximale configurables
- Envoi d'alertes via ESP-NOW à un second module ESP32 connecté à une radio Taranis QX7
- Coupure automatique de l'alimentation de la voiture RC en cas de tension hors limites
- Affichage des informations de tension et des alertes sur le moniteur série

## Composants requis

- 2 modules ESP32
- 1 voiture RC avec une batterie lithium
- 1 radio Taranis QX7
- Des résistances et des câbles pour le circuit de mesure de tension

## Installation

1. Clonez ce dépôt sur votre machine locale.
   ```
   git clone https://github.com/votre-nom/rc-car-battery-voltage-monitor.git
   ```

2. Ouvrez les fichiers `battery_voltage_controller.cpp` et `voltage_alert_receiver.cpp` dans l'IDE Arduino.

3. Configurez les paramètres suivants dans le fichier `battery_voltage_controller.cpp` :
   - `batteryPin` : Broche de lecture de tension de la batterie
   - `powerPin` : Broche de commande de l'alimentation de la voiture RC
   - `minVoltage` : Tension minimale par cellule (seuil d'alerte)
   - `maxVoltage` : Tension maximale par cellule (seuil de charge)
   - `numCells` : Nombre de cellules de la batterie lithium en série
   - `receiverAddress` : Adresse MAC du module ESP32 récepteur

4. Téléversez le code `battery_voltage_controller.cpp` sur le module ESP32 connecté à la batterie de la voiture RC.

5. Téléversez le code `voltage_alert_receiver.cpp` sur le module ESP32 connecté à la radio Taranis QX7.

6. Connectez les composants selon le schéma de câblage fourni (à inclure dans le dépôt).

## Utilisation

1. Mettez sous tension les deux modules ESP32 et la voiture RC.

2. Ouvrez le moniteur série de l'IDE Arduino pour le module ESP32 connecté à la batterie.

3. Vérifiez les informations de tension affichées sur le moniteur série.

4. En cas d'alerte de tension (tension hors limites), le module ESP32 connecté à la batterie coupera automatiquement l'alimentation de la voiture RC et enverra une alerte au module ESP32 connecté à la radio Taranis QX7.

5. Le module ESP32 connecté à la radio Taranis QX7 affichera l'alerte reçue sur le moniteur série.

## Contribution

Les contributions à ce projet sont les bienvenues. Si vous souhaitez apporter des améliorations ou corriger des bogues, veuillez suivre les étapes suivantes :

1. Fork ce dépôt
2. Créez une nouvelle branche (`git checkout -b feature/nouvelle-fonctionnalite`)
3. Effectuez les modifications nécessaires
4. Committez vos modifications (`git commit -m 'Ajouter une nouvelle fonctionnalité'`)
5. Poussez vers la branche (`git push origin feature/nouvelle-fonctionnalite`)
6. Ouvrez une Pull Request

## Licence

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus d'informations.

## Contact

Si vous avez des questions, des suggestions ou des commentaires, n'hésitez pas à me contacter à l'adresse email suivante : contact@luka-chassaing.fr
