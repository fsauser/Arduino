#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
main.py
"""
__author__      = "FSA"
__copyright__   = "Copyright 2023, HE-ARC"
__date__        = "01 juin 2023"

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import time
import serial
import matplotlib.animation as animation

PORT = 'COM16'


SerialObj = serial.Serial(
  port=PORT,
  baudrate=115200,
  parity=serial.PARITY_NONE,
  stopbits=serial.STOPBITS_ONE,
  bytesize=serial.EIGHTBITS,
  timeout=None,
)


NUMBER_X: int = 1
NUMBER_Y: int = 1

CANVAS_WIDTH:  int = 32
CANVAS_HEIGHT: int = 24

def heatmap_animation1(): 
  fig, ax_lst = plt.subplots(NUMBER_X, NUMBER_Y)
  #ax_lst = ax_lst.ravel()

  def plot(data):
    expected_header = bytes([0xfe, 0x01, 0xfe, 0x01])
    SerialObj.flush()
    SerialObj.read_until(expected_header)
    dataRaw = SerialObj.read(768*6-1)
    dataFloat = dataRaw.decode('utf-8').split(",")
    
    dataArray = [float(x) for x in dataFloat]
    data = np.array(dataArray).reshape(24, 32)
    print('min:{0:.2f}; max:{1:.2f}\n'.format(np.min(data), np.max(data)))
    heatmap = ax_lst.pcolor(data, vmin=15., vmax=40.0)

  ani = animation.FuncAnimation(fig, plot, interval=1000)
  plt.show()

def heatmap_animation2():
    fig, ax_lst = plt.subplots(NUMBER_X, NUMBER_Y)
    ax_lst = ax_lst.ravel()

    data = np.random.rand(CANVAS_WIDTH, CANVAS_HEIGHT)
    im = ax_lst[0].imshow(data)

    while True:
        t_start = time.time()
        data = np.random.rand(CANVAS_WIDTH, CANVAS_HEIGHT)
        im.set_data(data) 
        plt.pause(0.001)
        t_end = time.time()
        print("fps = {0}".format(999 if t_end == t_start else 1/(t_end-t_start)))

def heatmap_animation3():
    fig, ax_lst = plt.subplots(NUMBER_X, NUMBER_Y)
    #ax_lst = ax_lst.ravel()

    data = np.random.rand(CANVAS_WIDTH, CANVAS_HEIGHT)
    heatmap = ax_lst[0].pcolor(data)
    fig.canvas.draw()
    fig.show()

    while True:
        data = np.random.rand(CANVAS_WIDTH, CANVAS_HEIGHT)
        t_start = time.time()
        heatmap = ax_lst[0].pcolor(data)
        ax_lst[0].draw_artist(ax_lst[0].patch)
        ax_lst[0].draw_artist(heatmap)
        fig.canvas.blit(ax_lst[0].bbox)
        fig.canvas.flush_events()
        t_end = time.time()
        print("fps = {0}".format(999 if t_end == t_start else 1/(t_end-t_start)))


def main():
  SerialObj.close()

  try:
    SerialObj.open()
    time.sleep(0.1)
  except serial.SerialException as var : # var contains details of issue
    print('An Exception Occured')
    print('Exception Details-> ', var)
      
  else:
    print('Serial Port Opened')   
    heatmap_animation1()



if __name__ == '__main__':
    main()

