import os
import asyncio
import sys
from bleak import BleakClient
from bleak import BleakScanner
from functools import partial
from sty import fg, bg, ef, rs

CHAR_UUID_ALCOHOL = 'beb5483e-36e1-4688-b7f5-ea07361b26a8'
TIME_TO_RUN = 20.0  # secondes
listDev = {}

def move (y, x):
  print("\033[%d;%dH" % (y, x))

def charAlcohol_callback(client: BleakClient, sender: int, data: bytearray):
  value = {i for i in listDev if listDev[i]==client.address}
  if min(listDev.keys()) == ', '.join(value):
    move(0,0)

  str1 = bg.blue + str(value) + bg.rs
  str2 = bg.red + f'{(float(data)):0.3f}' + ' PPM '+ bg.rs
  print(f'Notification from device {str1} --> characteristic : {str2}', flush=True)

async def BLEscan(devName='None'):
  #listDev = {}
  devices = await BleakScanner.discover()
  for dev in devices:
    if (devName =='None'): 
      print(dev)
    elif str(dev.name).find(devName) != -1:
      listDev[dev.name] = dev.address
  
  return listDev

async def main(addresses):
  group_task = asyncio.gather(*(connect_to_device(address) for address in addresses))
  await asyncio.sleep(TIME_TO_RUN+5.0)
  try:
    await asyncio.wait_for(group_task, len(addresses))
  except asyncio.TimeoutError:
    print("Time's up!")

  try:
    result = await group_task
  except asyncio.CancelledError:
    print("Gather was cancelled")

async def connect_to_device(address):
  async with BleakClient(address, timeout=10) as client:
    if (not client.is_connected):
      raise "client not connected"

    services = client.get_services
    for service in client.services:
      print(f'service {service.handle:02d} - UUID: {service.uuid} - {service.description}')
 
      characteristics = service.characteristics
      for char in characteristics:
        print('  characteristic', char.handle, char.uuid, char.description, char.properties)

        descriptors = char.descriptors
        for desc in descriptors:
          print('    descriptor', desc)
    
    os.system('cls')
    await client.start_notify(CHAR_UUID_ALCOHOL, partial(charAlcohol_callback, client))
    print('Start notification:')
    await asyncio.sleep(TIME_TO_RUN)
    await client.stop_notify(CHAR_UUID_ALCOHOL)

if __name__ == "__main__":
  dictDev = asyncio.run(BLEscan("ESP32"))
  if len(dictDev) > 1:
    dictDev = dict(sorted(dictDev.items(), key=lambda item:item[1]))
    print(dictDev)
    asyncio.run(main(list(dictDev.values())))
  else:
    print("No devices found.")

  move(3, 1)
  print('Finish')
