[中文](https://github.com/WeCanSTU/Phoenix-AriesSDK/blob/master/README_CN.md) / [English](https://github.com/WeCanSTU/Phoenix-AriesSDK/blob/master/README.md)

# Phoenix-AriesSDK 移植工程

本仓库是基于 **[Phoenix 凤凰座 PY32F002B 核心板](https://GitHub.com/WeCanSTU/Phoenix)** 的 **[AriesSDK](https://GitHub.com/WeCanSTU/AriesSDK) 软件移植**工程，提供了完整的软件框架、BootLoader 和 Application 示例，支持多工具链开发，帮助开发者快速实现嵌入式项目开发、调试及部署。


## 文档结构

1. **功能特性**  
   - 概述本工程的核心功能与支持特性。  

2. **快速入门**  
   - 提供多种开发模式的安装与使用说明。  
   - 覆盖 Keil MDK、VSCode+EIDE 插件、xmake+ARM-GCC 三种开发方式。  

3. **工程结构**  
   - 详细说明项目代码目录及其作用，帮助开发者快速理解工程组织结构。  

4. **构建与烧录**  
   - 详细介绍基于 **xmake + ARM-GCC** 的自动化编译与固件下载方式。

5. **开发与调试**  
   - 简要说明固件位置和调试工具的使用。

6. **资源与支持**  
   - 提供项目所需的工具下载链接，以及技术支持联系方式。

7. **贡献指南**  
   - 提供贡献代码的方式，欢迎社区开发者参与。


## 1. 功能特性

本工程具备以下核心功能：

### 1.1 AriesSDK 支持

- 提供 AriesSDK 的 **I2C 接口移植**，快速适配 Phoenix 核心板。
- 支持多种外设通信协议，便于开发者扩展自己的外设功能。

### 1.2 BootLoader 示例

- **固件升级**：支持通过 **TechSync 工具** 快速进行固件升级。  
- **远程日志调试**：便于实时获取设备运行状态，快速定位问题。

### 1.3 Application 示例

- 提供丰富的外设示例，如 GPIO、I2C、USB-CDC 等，覆盖常见的嵌入式开发需求。
- 示例代码结构清晰，便于开发者快速上手。

### 1.4 多工具链支持

- **Keil MDK**：支持 ARMCC 编译器，适合传统嵌入式开发流程。  
- **VSCode + EIDE 插件**：轻量化开发模式，易于集成任务管理和自动化构建。  
- **xmake + ARM-GCC**：跨平台构建工具链，支持快速编译与导入其他工具链。  



## 2. 快速入门

### 2.1 下载代码与初始化

通过以下命令克隆本仓库，并初始化子模块：

```bash
git clone https://GitHub.com/WeCanSTU/Phoenix-AriesSDK.git
cd Phoenix-AriesSDK
git submodule update --init --recursive
```

### 2.2 开发模式说明

#### 方式一：Keil MDK 开发模式

1. 安装 **Keil MDK**  
   - [点击下载 Keil MDK](https://www.keil.com/download/product/)，推荐使用 **v5 或更高版本**。  

2. 打开 Keil 工程文件  
   - 在工程目录 `PY32F002B/App` 下，找到 `PY32F002B-App.uvprojx` 文件并双击打开。  

3. 编译与烧录  
   - 按 **F7** 进行代码编译，确保无错误。  
   - 点击 **Download** 按钮，将编译后的固件烧录至开发板。  


#### 方式二：VSCode + EIDE 插件开发模式

1. 安装前置工具  
   - **Keil MDK**：同上，确保安装完成。  
   - **TechSync 工具**：安装 [TechSync 工具](https://GitHub.com/WeCanSTU/install)，用于固件烧录和日志调试。  
   - **VSCode**：下载 [VSCode](https://code.visualstudio.com/)，并安装插件 **EIDE（Embedded IDE For VSCode）**。

2. 打开 EIDE 工程  
   - 在 VSCode 中打开本仓库路径下的 `PY32F002B/App` 目录，双击 `App.code-workspace` 文件以工作区方式加载工程。  

3. 编译与下载固件  
   - 在 EIDE 工具栏中，选择 **Build** 指令进行编译。  
   - 选择 **Download**，通过 **TechSync 工具** 将固件烧录到设备中。  


#### 方式三：xmake + ARM-GCC 开发模式

1. 安装工具链  
   - 下载并安装 [ARM GNU 工具链](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)。推荐版本：10.3 或更新版本。  
   - 安装构建工具 [xmake](https://xmake.io/)，运行以下命令快速安装：  
     ```bash
     curl -fsSL https://xmake.io/shget.text | bash
     ```

2. 使用 VSCode 内置任务  
   配置文件 `.vscode/tasks.json` 已预置常用任务，开发者可以快速通过任务面板完成工程的编译与固件下载（详见 [构建与烧录](#4-构建与烧录)）。


## 3. 工程结构

以下是项目的核心目录说明：

```plaintext
.
├── PY32F002B               # Phoenix 核心板相关工程
│   ├── App                 # 应用工程目录
│   │   ├── .eide           # EIDE 工程配置
│   │   └── User            # 用户代码
│   ├── Boot                # BootLoader 工程目录
│   │   └── User            # 用户代码
│   └── Port                # 移植代码目录
├── resource                # 其他相关资源
└── Sdk                     # SDK 及驱动支持
    ├── AriesSDK            # AriesSDK 代码
    └── Py32f002b           # PY32F002B 平台支持包
        ├── Documentation   # 文档资料
        ├── Drivers         # 驱动程序
        ├── Packs           # 工具链包
        └── Projects        # 示例项目
```


## 4. 构建与烧录

本节将详细说明如何使用 **xmake + ARM-GCC** 环境，通过 **VSCode 的任务面板** 或命令行完成工程的编译与固件下载。



### 编译与下载任务

我们提供了基于 **VSCode** 的 `tasks.json` 配置文件，内置了常用的 **编译** 和 **下载** 任务，以下是任务的详细描述及使用方法。

#### 主要任务说明

1. **Build-PY32F002B-APP**  
   - 描述：编译 `App` 工程（应用层）。  
   - 工具：基于 `xmake` 构建工具。  
   - 配置路径：`PY32F002B/App`

2. **Rebuild-PY32F002B-APP**  
   - 描述：清理并重新编译 `App` 工程（应用层）。  
   - 工具：基于 `xmake` 构建工具。  
   - 配置路径：`PY32F002B/App`

3. **Download-PY32F002B-APP**  
   - 描述：下载编译后的 `App` 固件到设备。  
   - 工具：基于 `xmake` 和 Lua 脚本烧录固件。  
   - 配置路径：`PY32F002B/App`

4. **Build-PY32F002B-BOOT-HAL**  
   - 描述：编译 `BootLoader` 工程（引导程序）。  
   - 工具：基于 `xmake` 构建工具。  
   - 配置路径：`PY32F002B/Boot`

5. **Rebuild-PY32F002B-BOOT-HAL**  
   - 描述：清理并重新编译 `BootLoader` 工程。  
   - 工具：基于 `xmake` 构建工具。  
   - 配置路径：`PY32F002B/Boot`

6. **Download-PY32F002B-BOOT**  
   - 描述：使用 JLink 烧录 `BootLoader` 固件到设备。  
   - 工具：JLink CLI 工具。  
   - 配置路径：`.vscode`


### 使用步骤

#### 1. 打开 VSCode

确保 `.vscode/tasks.json` 文件存在，且已正确配置。

#### 2. 打开任务面板

进入 VSCode 菜单栏：  
`Terminal > Run Task`，选择需要执行的任务，例如：

- **Build-PY32F002B-APP**：编译 `App` 工程。  
- **Download-PY32F002B-BOOT**：下载 `BootLoader` 固件。

#### 3. 快捷键运行任务

对于默认任务（如 `Build-PY32F002B-APP`），可以通过以下快捷键直接运行：  
`Ctrl + Shift + B`

#### 4. 手动命令（可选）

如需手动执行，可以参考以下命令：  

- 配置工程：  
   ```bash
   cd PY32F002B/App
   xmake config -p cross -k binary -m release -a cortex-m0plus --sdk={ARMGCC-PATH} --cross=arm-none-eabi- --toolchain=gnu-rm -o ./output -c
   ```
- 编译：  
   ```bash
   xmake
   ```
- 烧录固件：  
   ```bash
   xmake l flash.lua APP-HAL
   ```



## 5. 开发与调试

- 编译后的固件位于 `output` 文件夹中。

- 使用 **TechSync 及 tsc-cli 工具** 进行远程多人实时监控设备的日志

  ```bash
  tsc-cli serial monitor -f -d 
  ```

  - Windows上实时捕获的设备日志

    ![win-log](https://GitHub.com/WeCanSTU/Phoenix-AriesSDK/raw/master/resources/win-log.png)

  - MacOS上实时捕获的设备日志

    ![macos-log](https://GitHub.com/WeCanSTU/Phoenix-AriesSDK/raw/master/resources/macos-log.png)

## 6. 资源与支持

- **论坛**: [AriesSDK Forum](https://forum.umetav.cn/t/aries-sdk) 
  - **开放时间**: 北京时间每日早上8点到凌晨1点。
- **QQ群**: 786239575
- **技术支持邮箱**: [tech@umetav.cn](mailto:tech@umetav.cn)

## 7. 贡献指南

欢迎开发者提交 Issue 或 Pull Request，贡献代码或提出改进建议！

