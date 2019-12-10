# ECEN 5823  Smart Warehouse using Bluetooth Mesh

## Project Report Links
Group Report Link: https://drive.google.com/drive/u/0/folders/1ykmPEbFEqN66oZjWkk3bYSzlcuucPcYD
Suraj Thite Report Link: https://drive.google.com/drive/u/0/folders/1BoQd0KOCjRzPxWxYD4BFsDIo3lK3fTrC

### Project Status
1. Configured LCD display with 1Hz screen refreshing rate via software external timer event in the BLE mesh.
2. Implemented state machine model to sample the data from the sensor via I2C interface.
3. Initialized Mesh LPN handled friendship events in BLE mesh stack with friend node.
4. Implemented GPIO interrupts for UI interface to display sensor data on the LCD screen.
5. Configured initialization of LPN and handling of its events in BLE Mesh Stack
6. Integrated CCS811 sensor in polling mode and interrupt mode.
7. Integrated beacon detection functionality by filtering advertising packets.
8. Implemented on off and level model to send fire alarm status and no of beacons to friend node.
9. The highest ppm value and no of beacons since the last boot is stored in the persistent memory and displayed on the screen.
10. Implemented low power functionality by implementing wake pin at CCS811 sensor and state machine model to minimize current consumption at low power node.
11. Establishment of friendship with friend node and publishing data to friend for every 5 seconds.