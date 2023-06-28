<font size=1>

Démo WiFi
===================

### 27-06-2023: v1.2
---------------------

# Connexion du capteur à la carte
La petite caméra IR (32x24) communique avec la carte '**ESP32S3-DevKitC1** via le protocole I2C.

La connexion entre la carte (voir Figure 1) et le capteur (voir Figure 2) est :

| Capteur IR         | ESP32S3-DevKitC1  |
| ------------------ | ----------------- |
| `VCC (fil rouge)`  | `3V3`             |
| `GND (fil noir)`   | `GND`             |
| `SDA (fil blanc)`  | `pin 17`          |
| `SCL (fil jaune)`  | `pin 18`          |


<figure>
  <img src="img\Pin-Layout.jpg" alt="Pin-Layout <ESP32-S3-DevKitC-1>" style="display: block; margin: 0 auto" width="80%" height="80%"/>
  <p style="text-align: center;">Figure 1: Pin-Layout "ESP32-S3-DevKitC-1"</p>
</figure>

<figure>
  <img src="img\IR.jpg" alt="Carte caméra thermique" style="display: block; margin: 0 auto" width="40%" height="40%"/>
  <p style="text-align: center;">Figure 2: Carte caméra thermique"</p>
</figure>

### Lien utile: 

- [Datasheet de la caméra thermique](https://www.farnell.com/datasheets/3759206.pdf)


# Code source MLX1
La première démo avec ce capteur permet de récupérer l'image IR et de l'envoyer (via RS232) vers un PC.
Un script python va récupérer les données sur le port de communication et les afficher.
Pour cela il faut :
- Télécharger le code source zippé ([lien](https://github.com/fsauser/Arduino/blob/94559d6414b82fe3562bcfb0607d46180584b5ba/zip/MLX1.zip)) et le dézippé dans le répertoire de travail (Arduino)
- Télécharger le script python ([lien](https://github.com/fsauser/Arduino/blob/94559d6414b82fe3562bcfb0607d46180584b5ba/python/MLX.py))
- Dans l'IDE Arduino, ouvrir le "Library Manager" (menu sur la gauche) et installer la librairue "NeoPixelBus"
- Compiler et télécharger le code sur la carte
- Lancer le script python (il est possible qu'il vous manque quelques librairies, utiliser "pip install " pour les installer).

# Code source MLX2
La deuxième démo avec ce capteur permet de récupérer l'image IR et de lancer un server Web permettant de récupérer les images via un navigateur sur le PC.

Pour cela il faut :
- Télécharger le code source zippé ([lien](https://github.com/fsauser/Arduino/blob/94559d6414b82fe3562bcfb0607d46180584b5ba/zip/MLX2.zip)) et le dézippé dans le répertoire de travail (Arduino)
- Dans l'IDE Arduino, ouvrir le "Library Manager" (menu sur la gauche) et installer la librairue "ESPAsyncWebSrv" et ses dépendances
- Modifier le code pour permettre une connexion WiFi (SSID & password)
- Compiler et télécharger le code sur la carte
- Récupérer l'adresse IP de la carte via la connexion série (avec Putty par ex.) 
- Lancer le navigateur et entrer l'adresse IP de la carte


</font>