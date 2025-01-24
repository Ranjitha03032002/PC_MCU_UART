| Supported Targets | ESP32-C3 |
| ----------------- | -------- | 

# EMX_BLE_

Note:

This is code is for TESTing only. The I2C bus is not active.

Change the main code to run I2C

# For Flashing (Compile Method)

1.  Install esp idf
2.  Download the main,CMakeLists, partitions.csv and sdk config to a New Project Folder 
3.  Select a correct Com port
4.  Build flash monitor

# ERROR

Have to run menuconfig

Changes

    -   Serial flasher config -> Flash size-> 4MB

    -   Partition Table -> Partition Table = Custom partition table csv

    -   Enable Bluetooth

    -   Enable BLE 4.2 features

    -   Disable BLE 5.0 features


