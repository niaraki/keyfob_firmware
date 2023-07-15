[![Language](https://img.shields.io/badge/Made%20with-C-blue.svg)](https://shields.io/)
![License](https://camo.githubusercontent.com/890acbdcb87868b382af9a4b1fac507b9659d9bf/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6c6963656e73652d4d49542d626c75652e737667)
# Keyfob Firmware
### NOTE: This firmware is under development and is not for productional purposes
    
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
</ol><br/>

#### Coding Styles

### Authors
- [**Mohammad Niaraki**](https://www.github.com/niaraki)

### License
 This project is licensed under the [MIT License](https://opensource.org/license/mit) - see the [License.md](License.md) file for
details

## Acknowledgments
I present this to all of you with :heart:
