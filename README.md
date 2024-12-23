# Phoenix-AreisSDK Porting Project

This repository is a **porting project of the [AreisSDK](https://gitee.com/WeCanSTU/AriesSDK) software** based on the **[Phoenix PY32F002B core board](https://gitee.com/WeCanSTU/Phoenix)**, providing a complete software framework, including BootLoader and Application examples. It supports multiple toolchains, enabling developers to quickly achieve embedded project development, debugging, and deployment.

## Document Structure
1. **Features**  
   - An overview of the core functionalities and supported features of this project.  

2. **Getting Started**  
   - Instructions for installation and usage in various development modes.  
   - Covers three development methods: Keil MDK, VSCode+EIDE Plugin, and xmake+ARM-GCC.  

3. **Project Structure**  
   - A detailed description of the project code directories and their functions to help developers quickly understand the organization of the project.  

4. **Build and Flash**  
   - Detailed instructions for automated compilation and firmware flashing using **xmake + ARM-GCC**.

5. **Development and Debugging**  
   - A brief explanation of firmware location and debugging tools usage.

6. **Resources and Support**  
   - Links for downloading tools required for the project, as well as contact details for technical support.

7. **Contribution Guide**  
   - Guidelines for contributing code, welcoming community developers to participate.



## 1. Features

This project provides the following core functionalities:

### 1.1 AreisSDK Support

- Provides **I2C interface porting** for the AreisSDK, allowing quick adaptation for the Phoenix core board.
- Supports multiple peripheral communication protocols, enabling developers to extend their peripheral functionalities.

### 1.2 BootLoader Example

- **Firmware Upgrade**: Supports quick firmware upgrades using the **TechSync tool**.  
- **Remote Log Debugging**: Provides real-time access to device runtime states for quick issue identification.

### 1.3 Application Example

- Includes rich peripheral examples, such as GPIO, I2C, USB-CDC, and more, covering common embedded development needs.
- Example codes are clearly structured for developers to quickly get started.

### 1.4 Multi-Toolchain Support

- **Keil MDK**: Supports ARMCC compiler, suitable for traditional embedded development workflows.  
- **VSCode + EIDE Plugin**: A lightweight development mode that integrates task management and automated builds.  
- **xmake + ARM-GCC**: A cross-platform build toolchain that supports fast compilation and easy integration with other toolchains.  


## 2. Getting Started

### 2.1 Download Code and Initialize

Clone this repository and initialize the submodules using the following commands:

```bash
git clone https://gitee.com/WeCanSTU/Phoenix-AreisSDK.git
cd Phoenix-AreisSDK
git submodule update --init --recursive
```

### 2.2 Development Methods Overview

#### Method 1: Keil MDK Development Mode

1. Install **Keil MDK**  
   - [Click here to download Keil MDK](https://www.keil.com/download/product/). Version **v5 or higher** is recommended.  

2. Open the Keil project file  
   - Navigate to the `PY32F002B/App` directory, locate the `PY32F002B-App.uvprojx` file, and double-click to open it.  

3. Compile and Flash  
   - Press **F7** to compile the code and ensure there are no errors.  
   - Click the **Download** button to flash the compiled firmware to the development board.  


#### Method 2: VSCode + EIDE Plugin Development Mode

1. Install prerequisites  
   - **Keil MDK**: As mentioned above, ensure it is installed.  
   - **TechSync Tool**: Install the [TechSync tool](https://gitee.com/WeCanSTU/install) to manage firmware flashing and log debugging.  
   - **VSCode**: Download [VSCode](https://code.visualstudio.com/) and install the **EIDE (Embedded IDE For VSCode)** plugin.

2. Open the EIDE project  
   - Open the `PY32F002B/App` directory in VSCode and double-click the `App.code-workspace` file to load the project workspace.  

3. Compile and Flash Firmware  
   - Use the **Build** command in the EIDE toolbar to compile the project.  
   - Use the **Download** command to flash the firmware to the device via the **TechSync tool**.  


#### Method 3: xmake + ARM-GCC Development Mode

1. Install the toolchain  
   - Download and install the [ARM GNU Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm). Version **10.3 or newer** is recommended.  
   - Install the build tool [xmake](https://xmake.io/) by running the following command:  
     ```bash
     curl -fsSL https://xmake.io/shget.text | bash
     ```

2. Use VSCode Built-in Tasks  
   The `.vscode/tasks.json` configuration file contains pre-configured tasks that developers can use to compile and flash the project via the task panel (see [Build and Flash](#4-build-and-flash) for details).


## 3. Project Structure

Below is the explanation of the core project directories:

```plaintext
.
├── PY32F002B               # Phoenix core board-related projects
│   ├── App                 # Application project directory
│   │   ├── .eide           # EIDE project configuration
│   │   └── User            # User code
│   ├── Boot                # BootLoader project directory
│   │   └── User            # User code
│   └── Port                # Ported code directory
├── resource                # Other related resources
└── Sdk                     # SDK and driver support
    ├── AriesSDK            # AreisSDK code
    └── Py32f002b           # PY32F002B platform support files
        ├── Documentation   # Documentation resources
        ├── Drivers         # Drivers
        ├── Packs           # Toolchain packages
        └── Projects        # Example projects
```

---



Below is the translation of the provided content into English:



## 4. Build and Flash

This section provides detailed instructions on how to use the **xmake + ARM-GCC** environment to compile the project and flash firmware via the **VSCode task panel** or command line.



### Compilation and Flash Tasks

We provide a `tasks.json` configuration file for **VSCode**, which includes commonly used **compilation** and **flash** tasks. Below is a detailed description of these tasks and how to use them.

#### Main Task Descriptions

1. **Build-PY32F002B-APP**  
   - **Description**: Compiles the `App` project (application layer).  
   - **Tool**: Built using the `xmake` build tool.  
   - **Configuration Path**: `PY32F002B/App`

2. **Rebuild-PY32F002B-APP**  
   - **Description**: Cleans and recompiles the `App` project (application layer).  
   - **Tool**: Built using the `xmake` build tool.  
   - **Configuration Path**: `PY32F002B/App`

3. **Download-PY32F002B-APP**  
   - **Description**: Downloads the compiled `App` firmware to the device.  
   - **Tool**: Uses `xmake` and Lua scripts to flash the firmware.  
   - **Configuration Path**: `PY32F002B/App`

4. **Build-PY32F002B-BOOT-HAL**  
   - **Description**: Compiles the `BootLoader` project (boot program).  
   - **Tool**: Built using the `xmake` build tool.  
   - **Configuration Path**: `PY32F002B/Boot`

5. **Rebuild-PY32F002B-BOOT-HAL**  
   - **Description**: Cleans and recompiles the `BootLoader` project.  
   - **Tool**: Built using the `xmake` build tool.  
   - **Configuration Path**: `PY32F002B/Boot`

6. **Download-PY32F002B-BOOT**  
   - **Description**: Uses JLink to flash the `BootLoader` firmware to the device.  
   - **Tool**: JLink CLI tool.  
   - **Configuration Path**: `.vscode`

### Steps to Use

#### 1. Open VSCode

Ensure the `.vscode/tasks.json` file exists and is correctly configured.

#### 2. Open the Task Panel

Navigate in the VSCode menu:  
`Terminal > Run Task`, and select the task you want to execute, such as:

- **Build-PY32F002B-APP**: Compile the `App` project.  
- **Download-PY32F002B-BOOT**: Flash the `BootLoader` firmware.

#### 3. Run Tasks with Hotkeys

For default tasks (e.g., `Build-PY32F002B-APP`), you can run them directly using the following hotkey:  
`Ctrl + Shift + B`

#### 4. Manual Commands (Optional)

If you need to execute tasks manually, refer to the following commands:  

- Configure the project:  
   ```bash
   cd PY32F002B/App
   xmake config -p cross -k binary -m release -a cortex-m0plus --sdk={ARMGCC-PATH} --cross=arm-none-eabi- --toolchain=gnu-rm -o ./output -c
   ```
- Compile the project:  
   ```bash
   xmake
   ```
- Flash the firmware:  
   ```bash
   xmake l flash.lua APP-HAL
   ```

## 5. Development and Debugging

- The compiled firmware is located in the `output` folder.

- Use **TechSync and tsc-cli tools** to remotely monitor device logs in real-time.

  ```bash
  tsc-cli serial monitor -f -d 
  ```

  - Real-time device log capture on Windows:

    ![win-log](https://gitee.com/WeCanSTU/Phoenix-AreisSDK/raw/master/resources/win-log.png)

  - Real-time device log capture on macOS:

    ![macos-log](https://gitee.com/WeCanSTU/Phoenix-AreisSDK/raw/master/resources/macos-log.png)

## 6. Resources and Support

- **Forum**: [AriesSDK Forum](https://gitee.com/link?target=https%3A%2F%2Fforum.umetav.cn%2Ft%2Faries-sdk)
  - **Hours**: Open daily from 8:00 AM to 1:00 AM (Beijing Time).
- **QQ Group**: 786239575
- **Technical Support Email**: [tech@umetav.cn](https://gitee.com/link?target=mailto%3Atech@umetav.cn)



## 7. Contribution Guide

We welcome developers to submit Issues or Pull Requests to contribute code or provide improvement suggestions!  
