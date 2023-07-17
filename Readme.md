<h1 align="center">
  Keyfob Firmware
</h1>
<p align="center">
 NOTE: This firmware is under development and is not for productional purposes   
</p>

[![Language](https://img.shields.io/badge/Made%20with-C-blue.svg)](https://shields.io/)
![License](https://camo.githubusercontent.com/890acbdcb87868b382af9a4b1fac507b9659d9bf/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6c6963656e73652d4d49542d626c75652e737667)
[![ClangFormat](https://github.com/niaraki/keyfob_firmware/actions/workflows/clangformat.yml/badge.svg)](https://github.com/niaraki/keyfob_firmware/actions/workflows/clangformat.yml)
[![CppCheck](https://github.com/niaraki/keyfob_firmware/actions/workflows/cppcheck.yml/badge.svg)](https://github.com/niaraki/keyfob_firmware/actions/workflows/cppcheck.yml)
[![Lizard](https://github.com/niaraki/keyfob_firmware/actions/workflows/lizard.yml/badge.svg)](https://github.com/niaraki/keyfob_firmware/actions/workflows/lizard.yml)
[![Flawfinder](https://github.com/niaraki/keyfob_firmware/actions/workflows/flawfinder.yml/badge.svg)](https://github.com/niaraki/keyfob_firmware/actions/workflows/flawfinder.yml)
[![Test](https://github.com/Niaraki/keyfob_firmware/actions/workflows/unit-test.yml/badge.svg)](https://github.com/Niaraki/keyfob_firmware/actions/workflows/unit-test.yml)
[![Doxygen](https://github.com/niaraki/keyfob_firmware/actions/workflows/doxygen.yml/badge.svg)](https://github.com/niaraki/keyfob_firmware/actions/workflows/doxygen.yml)
[![codecov](https://codecov.io/gh/Niaraki/keyfob_firmware/branch/dev/graph/badge.svg)](https://codecov.io/gh/Niaraki/keyfob_firmware)
    
## Summary 
  - [Introduction](#introduction)
  - [Project Structure](#project-structure)
  - [Development Guidlines](#development-guidlines)
  - [Authors](#authors)
  - [License](#license)
  - [Acknowledgments](#acknowledgments)

### Introduction

### Project Structure
The structure of the root folder :

| Folder Name | Description |
|-------------|-------------| 
| / | Root of the project |
| src | Contains all the source codes |
| tests | Contains all the test codes |
| docs | Contains all pages and assets used for documentation |
| external | Contains all thirdparties modules |
| scripts | Contains all scripts used for CI/CD and etc. |
| docker | Contains the dockerfile used as build container in the CI system|
| cmake | Contains all required cmake modules |
| templates | Contains all templates used in the code-base |

The structure of the source folder :

| Folder Name | Description |
|-------------|-------------| 
| app | Contains all business related source codes |
| common | Contains all source codes shared between different system layers|
| bsp | Contains all board-related source codes (Board-Support-Package)|
| middleware | Contains all third-parties source codes like DS, Protocol Stacks and etc |
| drivers | Conaints all high-level source codes as drivers for external chips on the board|
| hal | Contains all source codes for developed Hardware-Abstraction-Layer|
| hll | Contains all source codes for developed Hardware-Low-Layer|


### Development Guidlines 
#### Prerequisites


| App | Description | Version | How to install |
|-----|-------------|---------|----------------|
| arm-none-eabi- | Cross compiler for arm MCU | 10.3.1 | |
| CMake | Build System Generator | 3.26.4 | sudo snap install cmake --clasic |
| GNU-Make | Source builder | 4.2.1 | sudo apt install make |
| Cppcheck | C/C++ static analyzer | 1.90 | sudo apt install cppcheck |
| [Lizard](https://github.com/terryyin/lizard) | Cyclomatic Complexity Analyzer | 1.17.10  | sudo pip install lizard |
| [Flawfinder](https://github.com/david-a-wheeler/flawfinder) | Vulnerabilities scanner | 2.0.19 | pip install flawfinder |
| Clangformat | C/C++ code linter | 10.0.0 | sudo apt-get install clang-format |
| Doxygen | Automatic document generator from source codes | 1.8.17 | sudo apt install doxygen |
| Lcov | Report generator from gcov | 1.14 | sudo apt install lcov |
| Docker | Containerization technology | 24.0.2 | [Installation guide](https://docs.docker.com/engine/install/ubuntu/) |
| STM32CubeProgrammer | STM32 programming suite | 2.13.0 |[Wiki](https://wiki.st.com/stm32mpu/wiki/STM32CubeProgrammer)|
| Google Test | Google test harness | v1.13.0 | - |



#### How To Compile 
#### Commit Message Conventions
<ol>
<li>
The first line of the commit message should be like the below format:<br/>
    <b>[type-icon] [type-name]: [scope*]: [message title] </b><br/> 
Type Table:

| icon | name | description |
|------|----|-------------|
|📦 | NEW | we use this type when we have added something |
|👌 | ENH | we use this type when we have modified or enhance something |
|🐛 | FIX | we use this type when we have fixed a bug |
|🎭 | MRG | we use this type when we want to merge two branches|


<ul>
    <li>
    Scope can be a filename, a module name (*it is and optional field)
    </li>
    <li>
    Use simple present tense for the title - for example <b>add</b> instead of <b>added</b>
    </li>
</ul>
</li>
<li>
After the first line, we have the commit body which explains more about the commit
</li>
<li>
An optional footer part comes after the body and it should be like this:<br/>
resolved #[The specific <b> issue number </b> which is targeted by this commit]
</li>
<li>
Don't use fast-forward merging, because merge commits can show the history of changes better<br/>
You can disable it on your machine by using the following command:<br/>
<b>git config --global merge.ff no</b>
</li>
</ol>

#### Coding Styles
This project uses the c-coding style introduced by [barrgroup](https://barrgroup.com/embedded-systems/books/embedded-c-coding-standard). The configurations are also available [here](https://github.com/petertorelli/clang-format-barr-c).

### Authors
- [**Mohammad Niaraki**](https://www.github.com/niaraki)

### License
 This project is licensed under the [MIT License](https://opensource.org/license/mit) - see the [License.md](License.md) file for
details

## Acknowledgments
I present this to all of you with :heart:
