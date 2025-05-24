# 🌤️ Station Météo – Qt & JSON

Projet de station météo réalisé avec Qt Creator en C++, utilisant des données environnementales au format JSON pour l’affichage et le traitement.

---

## 🎯 Objectif du projet

Ce projet a été réalisé dans le cadre de ma formation. Il permet de récupérer la date, traiter et afficher des données météorologiques (température, humidité, pression...) dans une interface graphique développée avec Qt.

---

## 🧰 Technologies utilisées

- **C++** avec Qt Creator (Qt Widgets)
- Lecture et  de fichiers JSON
- Utilisation de **QFile**, **QJsonDocument**, **QJsonObject**, etc.
- Interface graphique interactive

---

## 📦 Fonctionnalités

- 📁 Chargement de fichiers JSON contenant des données météo
- 📊 Affichage des valeurs de température, humidité, pression
- ⚠️ Gestion des erreurs de lecture ou format JSON invalide

---

## 🖥️ Aperçu de l'application

![image](https://github.com/user-attachments/assets/0ffa93c1-5072-4c2d-ab7a-b21a8710bc40)

![image](https://github.com/user-attachments/assets/4d57d6eb-5f8e-4e92-b84d-16bca60e63dc)

---

## 📁 Exemple de fichier JSON

```json
"date": [
    {
      "2019-01-01": {
        "time": {
          "00:00": {
            "temperature": 5,
            "vent-direction": "Nord-est",
            "vent-speed": 11,
            "humidité": 87,
            "pression": 1026
          },
          "00:30": {
            "temperature": 4,
            "vent-direction": "Nord-est",
            "vent-speed": 9,
            "humidité": 87,
            "pression": 1026
          },
          "01:00": {
            "temperature": 5,
            "vent-direction": "Nord-est",
            "vent-speed": 9,
            "humidité": 81,
            "pression": 1026
          },
          }
        }
  }
]
