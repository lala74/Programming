# Linux <!-- omit in toc -->

- [1. Apps](#1-apps)
- [2. Configuration](#2-configuration)
  - [2.1. Change theme in ubuntu](#21-change-theme-in-ubuntu)
  - [2.2. Change lock screen background](#22-change-lock-screen-background)
  - [2.3. Git](#23-git)
- [3. Useful command](#3-useful-command)
  - [3.1. Display all ports](#31-display-all-ports)
  - [3.2. Add architecture 32 bits](#32-add-architecture-32-bits)
- [4. Error](#4-error)
  - [4.1. Can't open terminal after modifying locale](#41-cant-open-terminal-after-modifying-locale)
    - [4.1.1. Command](#411-command)
    - [4.1.2. Solution](#412-solution)
  - [4.2. Add necessaire libraries for C++ dev](#42-add-necessaire-libraries-for-c-dev)

## 1. Apps

- Chrome
- Unikey
- VLC
- Spotify
- VS Code
- Python
- Git
- Wireshark

## 2. Configuration 

### 2.1. Change theme in ubuntu 
<https://www.cyberciti.biz/faq/change-theme-in-ubuntu/>

```sh
$ sudo apt update
$ sudo apt install gnome-tweak-tool
```

### 2.2. Change lock screen background
[Change lock screen](https://vitux.com/how-to-change-login-lock-screen-background-in-ubuntu/)

### 2.3. Git
A better git log

```bash
git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
```


## 3. Useful command

### 3.1. Display all ports
We use this command to verifie if an USB device can be recognize by computer and find COM Port (attyCM0) for minicom to display debug message

```bash
dmesg
```

### 3.2. Add architecture 32 bits
```bash
dpkg --add -architecture i386
```

## 4. Error

### 4.1. Can't open terminal after modifying locale
#### 4.1.1. Command

```bash
locale                              display all language locale - see for error
locale -a                           all package used
sudo update-locale                  update locale
sudo locale-gen                     generate missing package
sudo dpkg-reconfigure locales       configure locale with package-generated
```

#### 4.1.2. Solution
1. Commenting out `SendEnv LANG LC_*` line in  `/etc/ssh/ssh_config` file -> reload `service ssh reload`
2. export LC_....=en_US.UTF-8
3. modifie `etc/locale.gen` file and `sudo locale-gen` to generate all missing package
4. set variale in `etc/default/locale` like :

```bash
LANGUAGE=en_US.UTF-8
LC_ALL=en_US.UTF-8
LANG=en_US.UTF-8
LC_TYPE=en_US.UTF-8
```

ATTENTION!!! : setting variable in `etc/environment` doesn't work because it's deprecated


### 4.2. Add necessaire libraries for C++ dev

```bash
sudo apt-get install make
sudo apt-get install g++

# Install library
apt-cache search `Library name` | grep dev          # get dev version
sudo apt-get install `Library name found`
# GLib
libglib2.0-dev
```
