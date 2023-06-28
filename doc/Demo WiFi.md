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
  <img src="img\IR.jpg" alt="Carte caméra thermique" style="display: block; margin: 0 auto" width="80%" height="80%"/>
  <p style="text-align: center;">Figure 2: Carte caméra thermique"</p>
</figure>

### Lien utile: 

- [Datasheet de la caméra thermique](https://www.farnell.com/datasheets/3759206.pdf)


# Code source MLX1
La première démo avec ce capteur permet de récupérer l'image IR et de l'envoyer (via RS232) vers un PC.
Un script python va récupérer les données sur le port de communication et les afficher.
Pour cela il faut :
- Télécharger le code source zippé [lien]()
- Télécharger et installer l'[Arduino IDE 2.1.0](https://www.arduino.cc/en/software), la version "Windows Win 10 and newer, 64 bits"
- Lancer IDE Arduino et aller dans le menu : File --> Preferences [onglet "Setting"] (voir Figure 3)
- Entrer le répertoire de travail (dans mon cas : c:\Users\florian.sauser\Documents\Arduino)
- Entrer le lien ci-dessous dans le champ "Additional boards manager URL:s" et valider
```
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

<figure>
  <img src="img\hw.jpg" alt="Menu: File --> Preferences" style="display: block; margin: 0 auto" width="80%" height="80%"/>
  <p style="text-align: center;">Figure 3: Menu: File --> Preferences"</p>
</figure>

Vous pouvez à présent charger les outils pour la carte ESP32-S3.
Pour cela, il faut aller sur le "Board Manager" et sélectioner "esp32 by Espressif Systems" (voir Figure 4).

<figure>
  <img src="img\board.jpg" alt="Board Manager" style="display: block; margin: 0 auto" width="50%" height="50%"/>
  <p style="text-align: center;">Figure 4: Board Manager"</p>
</figure>

Pour tester votre Installation, vous pouvez ouvrir le un "Sketch" d'exemple: 

File --> Exemples --> ESP32 --> GPIO --> BlinkRGB

Brancher la carte (connecteur "USP Port" de la carte) à votre PC et sélectionner la carte "ESP32S3 Dev Module" (voir Figure 5)et le port de connexion.

<figure>
  <img src="img\Select.jpg" alt="Select Other Board and Port" style="display: block; margin: 0 auto" width="80%" height="80%"/>
  <p style="text-align: center;">Figure 5: Select Other Board and Port"</p>
</figure>

A présent, vous pouvez compiler et télécharger le code sur la carte.

Vous pouvez également modifier le code pour envoyer un message de bienvenue (Serial) qui peut être lu via un terminal (par ex. [Putty](https://www.putty.org/) ou [Docklight](https://docklight.de/downloads/)).
Utiliser le connecteur "USB-to-UART Port" de la carte pour la communication sérielle.

### Liens utiles: 

- [Arduino core for the ESP32, ESP32-S2, ESP32-S3 and ESP32-C3](https://github.com/espressif/arduino-esp32)
- [Supported Peripherals](https://docs.espressif.com/projects/arduino-esp32/en/latest/libraries.html#supported-peripherals) 

Pour les démonstrations, il faut également avoir Python insatllé sur votre PC.
Si cela n'est pas déjà le cas, vous pouvez télécharger la dernière version sur le ce site suivant : 
[Python Releases for Windows](https://www.python.org/downloads/windows/)

Pour écrire les scripts Python il est possible d'utiliser l'outil IDLE (compris dans l'installation) ou [Visual Studio Code](https://code.visualstudio.com/).

</font>