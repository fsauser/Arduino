<font size=1>

Installation des outils
===================

### 27-06-2023: v1.1
---------------------

# Carte ESP32S3 - partie "matériel"
La carte utilisée pour les démonstrations est l'**ESP32S3-DevKitC1**.

<figure>
  <img src="img\ESP32S3 - DevKitC1.jpg" alt="Carte ESP32-S3-DevKitC-1" style="display: block; margin: 0 auto" width="80%" height="80%"/>
  <p style="text-align: center;">Figure 1: Carte "ESP32-S3-DevKitC-1"</p>
</figure>

<figure>
  <img src="img\Pin-Layout.jpg" alt="Pin-Layout <ESP32-S3-DevKitC-1>" style="display: block; margin: 0 auto" width="80%" height="80%"/>
  <p style="text-align: center;">Figure 2: Pin-Layout "ESP32-S3-DevKitC-1"</p>
</figure>
### Liens utiles: 

- [Get Started : ESP32-S3-DevKitC-1 v1.1](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/hw-reference/esp32s3/user-guide-devkitc-1.html)
- [Datasheet du SoC ESP32S3](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf) 

# Carte ESP32S3 - partie "logiciel"
Il est possible d'utiliser un SDK (toolchain) avec l'OS "FreeRTOS" mais, dans notre cas, nous allons plutôt utiliser l'outil "Arduino-ESP32".
Pour cela, il faut suivre les étapes suivantes:
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

### Liens utiles: 

- [Arduino core for the ESP32, ESP32-S2, ESP32-S3 and ESP32-C3](https://github.com/espressif/arduino-esp32)
- [Supported Peripherals](https://docs.espressif.com/projects/arduino-esp32/en/latest/libraries.html#supported-peripherals) 

</font>