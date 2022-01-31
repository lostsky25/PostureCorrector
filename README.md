<p align="center">
  <img src="https://user-images.githubusercontent.com/57411317/151821274-4164057d-ee9a-4b8c-9f87-2caa523602cf.png" alt="Logo Posture Corrector V2.0">
</p>
The goal is to study the problem associated with impaired posture. To develop a device that can help in the treatment and prevention of this deviation.
Tasks - to study the physiology of the spinal region, to identify the causes of problems with posture. Develop a device based on the ATmega328 microcontroller that can process data from various modules.

## Circuit scheme
![Schematic_PostureCorrector_2022-01-31](https://user-images.githubusercontent.com/57411317/151808925-d10869ab-f236-4f13-8ec3-32ef9dad5a52.png)

## Orientation angle calculation

Thanks to Earth's gravity, the accelerometer can give "correct" data, that is, the downward direction. It is these data that make it possible to determine the roll and pitch angles (these data will be sufficient for this project). Yaw - this angle (in this case, the magnetic azimuth), is determined with the participation of a magnetometer. The magnetic field induction vector can be obtained from the magnetometer and these data will be used to calculate the yaw angle. Three basic formulas:

![equation](https://user-images.githubusercontent.com/57411317/151813489-9f3156ac-654b-461b-907d-0aea02134e20.png)

## Device Application

This device is designed to control the position in space, as most people forget about it. Posture disorders occur against the background of morphological changes, often they are acquired. Much depends on the environment, insufficient development of the muscular system, which can be caused by frequent sitting at the computer, an ordinary table, or simply little physical activity. Also, do not forget about uncomfortable clothing and poor ergonomics.

This device is supposed to be worn while sitting at a computer or desk, the deviation can be no more than 10°.

<p align="center">
  <img src="https://user-images.githubusercontent.com/57411317/151813742-cf35b4f3-0e02-4dcb-92c4-6b049aadff54.png">
</p>

## Components

![boom_Page_1](https://user-images.githubusercontent.com/57411317/151819519-20cb87ad-2316-4ca7-8bb2-7b32472bcb46.png)
![boom_Page_2](https://user-images.githubusercontent.com/57411317/151819529-049f4372-b08c-48c4-b06c-d4da548a5426.png)

## 3D View


![main_board](https://user-images.githubusercontent.com/57411317/151819686-95333f95-5f06-433c-8dac-b4829655dc22.png)
![assambly_render_2](https://user-images.githubusercontent.com/57411317/151822067-ae28145c-6fc4-4fb8-a39e-9a56d30a36aa.png)
![assambly_render_4](https://user-images.githubusercontent.com/57411317/151819790-fe8962b1-cdc0-4d5f-9b02-8c22d5eb7c43.png)
![assambly_render_6](https://user-images.githubusercontent.com/57411317/151819796-45282091-4b44-4d28-bc96-e930ad322393.png)

## PCB

![image](https://user-images.githubusercontent.com/57411317/151821207-72773bba-7e33-42ce-b143-a2524433a713.png)

## Instructions for use

1. Put the device on your back or chest.
2. Tighten the straps.
3. Straighten up (as much as possible).
4. Press the calibration button.

After these actions, the device will start its work, in case of a deviation of more than 10 °, an audible signal will be turned on, signaling a violation of posture. The beep will stop after returning to the correct position.
