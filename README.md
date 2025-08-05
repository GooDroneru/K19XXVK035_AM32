# AM32 Port for [К1946ВК035/К1921ВК035] 
<p align="left">
  <a href="/LICENSE"><img src="https://img.shields.io/badge/license-GPL--3.0-brightgreen" alt="GitHub license" /></a>
</p>

## 📜 **Лицензия**  
Этот проект является портом [AM32](https://github.com/AlkaMotors/AM32) и распространяется под **GNU GPL v3.0**, как и оригинальный код.  
Полный текст лицензии: [LICENSE](LICENSE).  

> ⚠ **Важно**: Любые производные работы должны соблюдать условия GPL-3.0, включая открытие исходного кода.  

> **Важно**: Это **неофициальный порт** [AM32](https://github.com/AlkaMotors/AM32) для [К1946ВК035/К1921ВК035].  
> Основной репозиторий: [AM32](https://github.com/AlkaMotors/AM32).  

## 🔍 **Отличия от оригинального AM32**  
- Поддержка **К1946ВК035/К1921ВК035**.  
- Изменения в драйверах периферии.  
- Адаптация под другую периферию: иные таймеры управления мотором, иные таймеры для обработки входных сигналов управления, иная модель управления flash-памятью.  
- Сокращённый функционал: пока доступен только Dshot300.  

## 📥 **Установка и сборка**  
### Требования  
- Компилятор: [ARM-GCC](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads/12-2-mpacbti-rel1)
- Инструменты: [Cmake](https://cmake.org/download/), [ninja](https://ninja-build.org/), [openocd-k1921vk](https://github.com/DCVostok/openocd-k1921vk/releases)
- IDE: [VScode](https://code.visualstudio.com/download)
- SDK: [K1921VKx_SDK](https://gitflic.ru/project/niiet/k1921vkx_sdk) (уже в проекте)

## ⚙️ Поддерживаемые платы

GD80V1	✅ Работает
GD100V1	✅ Работает
https://goodroneru.ru/

## 📜 Принципиальная схема ESC (упрощённая версия)

![схема](images/Scheme.png)

PB7, PB6, PB5 - принимают сигналы внешних компараторов сравнивающих обратный ЭДС свободной фазы с напряжением общей точки всех фаз. [Более подробно](https://github.com/vladBaciu/Sensorless-BLDC-controller).

PB0, PB1, PB2 - измерение напряжение батареи через делитель, измерение тока через диф усилитель, измерение температуры через NTC термистор.

PA5 - входной сигнал управления тягой.

PB10 - выход телеметрии.

## 🐛 Известные проблемы

Не работает DSHOT выше DSHOT300 (связано с отсутствием DMA для ECAP).

## 🤝 Как помочь проекту

Тестирование на других платах.


## Hardware
AM32 currently has support for STSPIN32F0, STM32F051, STM32G071, GD32E230, AT32F415 and AT32F421.
The CKS32F051 is not recommended due to too many random issues.
Target compatibility List can be found [here](https://github.com/am32-firmware/AM32/blob/main/Inc/targets.h)


## Installation & Bootloader

To use AM32 firmware on a blank ESC, a bootloader must first be installed using an ST-LINK, GD-LINK , CMIS-DAP or AT-LINK.  THe bootloader will be dependant on the MCU used ont he esc . Choose the bootloader that matches the MCU type and signal input pin of the ESC.
The compatibility chart has the bootloader pinouts listed.
Current bootloaders can be found [here](https://github.com/am32-firmware/AM32-bootloader).

After the bootloader has been installed the main firmware from can be installed either with the configuration tools and a Betaflight flight controller or a direct connection with a usb serial adapter modified for one wire.

To update an existing AM32 bootloader an update tool can be found [here](https://github.com/am32-firmware/AM32-unlocker).

## Support and Developers Channel
There are two ways you can get support or participate in improving am32.
We have a discord server here:

https://discord.gg/h7ddYMmEVV

Etiquette: Please wait around long enough for a reply - sometimes people are out flying, asleep or at work and can't answer immediately. 

If you wish to support the project please join the Patreon.

https://www.patreon.com/user?u=44228479


## Sponsors
The AM32 project would not have made this far without help from the following sponsors:

Holmes Hobbies - https://holmeshobbies.com/ - The project would not be where it is today without the support of HH. Check out the Crawlmaster V2 for the best am32 experience!

Repeat Robotics - https://repeat-robotics.com/ - Bringing Am32 esc's to the fighting robot community!

Quaternium - https://www.quaternium.com/ - Firmware development support and hardware donations

Airbot - Many hardware donations

NeutronRC - For hardware, am32 promotion and schematics 

Aikon - Hardware donations and schematics\
Skystars  - For hardware and taking a chance on the first commercial am32 esc's\
Diatone - Hardware donations\
T-motor - Motor and Hardware donations\
HLGRC  - Hardaware donations


## Contributors
A big thanks to all those who contributed time, advice and code to the AM32 project.\
Un!t\
Hugo Chiang (Dusking)\
Micheal Keller (Mikeller)\
ColinNiu\
Jacob Walser

And for feedback from pilots and drivers:\
Jye Smith\
Markus Gritsch\
Voodoobrew

(and many more)

