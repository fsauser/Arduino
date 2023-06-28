<font size=1>

Démo BLE
===================

### 27-06-2023: v1.1
---------------------

# Connexion du capteur à la carte
Le capteur d'alcool communique avec la carte '**ESP32S3-DevKitC1** via le protocole I2C.

La connexion entre la carte (voir Figure 1) et le capteur (voir Figure 2) est :

| capteur d'alcool   | ESP32S3-DevKitC1  |
| ------------------ | ----------------- |
| `VCC (fil rouge)`  | `3V3`             |
| `GND (fil noir)`   | `GND`             |
| `D/T (fil vert)`   | `pin 17`          |
| `SCL (fil bleu)`   | `pin 18`          |


<figure>
  <img src="img\Pin-Layout.jpg" alt="Pin-Layout <ESP32-S3-DevKitC-1>" style="display: block; margin: 0 auto" width="80%" height="80%"/>
  <p style="text-align: center;">Figure 1: Pin-Layout "ESP32-S3-DevKitC-1"</p>
</figure>

<figure>
  <img src="img\alcohol.jpg" alt="Capteur d'alcool" style="display: block; margin: 0 auto" width="40%" height="40%"/>
  <p style="text-align: center;">Figure 2: Capteur d'alcool"</p>
</figure>

### Lien utile: 

- [Datasheet du capteur d'alcool](https://www.farnell.com/datasheets/3216115.pdf)


# Code source BLE
La démo avec ce capteur permet de récupérer le taux d'alcool et de permettre de le récupérer via bluetooth.
Un script python va lister les cartes avec le BLE et afficher le taux de chaque carte.
Pour cela il faut :
- Télécharger le code source zippé ([lien](https://github.com/fsauser/Arduino/blob/94559d6414b82fe3562bcfb0607d46180584b5ba/zip/Alcohol.zip)) et le dézippé dans le répertoire de travail (Arduino)
- Télécharger le script python ([lien](https://github.com/fsauser/Arduino/blob/94559d6414b82fe3562bcfb0607d46180584b5ba/python/BLE.py))
- Dans l'IDE Arduino, ouvrir le "Library Manager" (menu sur la gauche) et installer la librairue "DFRobot_Alcohol"
- Modifier le ficher "libraries\DFRobot_Alcohol\DFRobot_Alcohol.cpp" et remplacer la fonction "DFRobot_Alcohol_I2C::begin()" par le code suivant :

```console
bool DFRobot_Alcohol_I2C::begin()
{
  _pWire->setPins(17, 18);  
  _pWire->begin();
  _pWire->beginTransmission(_I2C_addr);
  if(_pWire->endTransmission() == 0){
    return true;
  }else{
    return false;
  }
}
```
- Renommer le nom de la carte (par ex. ESP-M3)
- Compiler et télécharger le code sur la carte
- Vérifier avec l'outil "nRF Connect" (Android ou iPhone) si votre carte est visible et que vous pouvez récupérer les données
- Lancer le script python (ne pas oublier d'activer le bluetooth sur votre PC).

Remarque : Avec le script Python, il est possible qu'il vous manque quelques librairies, utiliser "pip install " pour les installer.

Actuellement le code envoi une notification à chaque lecture, il serait intéressant de notifier uniquement lorseque l'on a un changement de taux.

</font>