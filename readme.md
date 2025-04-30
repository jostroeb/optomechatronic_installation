This project is an opto-mechatronic light installation. (Read below!!)

First test run:

![image](https://github.com/user-attachments/assets/0adff077-f821-480f-be3b-6431396733e1)

It is based on a parabolic mirror originating from a military application.
I designed a mechanics system around it to provide it with an High-Power RGB LASER-beam, which is rotated by a small front surface mirror to create the illusion of a continous beam.

It is powered by a hollow shaft BLDC-motor, which I'm running with an estimator control, since a hollow shaft encoder is expensive.

The full electronics are designed as an Arduino carrier board as the MCU.
The LASER driver is a 3-channel current controller. It is designed to drive the LASERs at 10kHz, with a rise time of about 5us.
For communication the DMX protocol is implemented, the standard for stage lighting applications. It is based on RS485, so a MAX485 UART-RS485 transceiver is used.
The motor driver IC is an TexasInstruments MCF8315 with integrated N-FETs. Its registers for setup and speed are set with I2C. 
The arduino used is an Portenta H7. It provides the PWM signal using it's internal HighResolutionTimers to create a 250kHz 8bit dimmer signal. This is run over low-pass filter with 60kHz cutoff frequency, to create the analog modulation voltage for the LASER driver to ensure full dimming capability.
The board features two step down voltage controllers for power supply.

I fully hand soldered the PCBs.
![3D_rendering](https://github.com/user-attachments/assets/c6055121-f2f6-4842-85f3-933f2f93a59d)

The mechanics feature a part rotating at 2000 rpm holding the mirror. Thus the part is optimized for high Eigenvalues for maximum stiffness. The small mirror is both glued and held by a compliant mechanism. The mechanism is self locking during rotation. 
Most parts were 3D-printed using MJF. Tolerances are on point to center the LASER module in the optical axis of the parabolic mirror.

LASER saftey was the major concern in this project. A lot of parts are redunant in saftey, especially the beam blockers around the LASER module.

Further contents to be added very soon. The prototype is up and running.
The provided documentation is only a 

Documentation is provided in German language and can be supplied in English upon request.

This is 100% my work.

This is a university-only project, Carl Zeiss AG is not invovled commercially in any means. They are mentioned, as they were the sponsor of my studies in the system of co-op studying at DHBW. 
