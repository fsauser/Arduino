<font size=1>

## Projet "Bluetooth Low Energy"
### Date: 06-06-2023: v1.0
---------------------
Pour utiliser le programme il faut suivre les points suivants:

- Installer la librairie "DFRobot_Alcohol"
- Installer la librairie "NeoPixelBus_by_Makuna"
- Modifier le ficher "libraries\DFRobot_Alcohol\DFRobot_Alcohol.cpp" et remplacer la fonction par le code suivant :

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

</font>