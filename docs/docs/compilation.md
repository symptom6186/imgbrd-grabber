---
title: Compilation
---


## Introduction

Tired of waiting for the next update? Want to get the latest developer version? Want to help on the program's development? You'll need to compile the program yourself.


## Windows

### Dependencies

!!! note

    Note that the compiler used for official builds is Visual Studio 2019. You can use MinGW or a more recent version of MSVC if it works for you. However, know that this is the one used in official releases.

Bullets marked with `*` are mandatory, other are optional.

* `*` Qt 6.6 or higher
* `*` A C++ compiler such as MSVC 2019
* `*` CMake 3.2 or higher
* `*` Node.js (for building images sources)
* QScintilla2 (for syntax highlighting in JavaScript filename window)
* Google Breakpad (to handle crash and show a nice-looking crash window and backup traces)

### Instructions

#### Qt
You can find the Qt installer here:  
<https://www.qt.io/download-qt-installer>

Just download and install.

#### MSVC
You can use the free Visual Studio Community version to compile (note that only the compiler is required). You can find it here: <https://www.visualstudio.com/downloads/>

Just download and install.

#### Node.js
You can find it here: <https://nodejs.org/en/download/>

Just download and install.

#### QScintilla
If you don't want to use QScintilla, edit the "src/gui/CMakeLists.txt" file and change the line `set(USE_QSCINTILLA 1)` into `set(USE_QSCINTILLA 0)`.

Otherwise, you can find it here: <http://www.riverbankcomputing.com/software/qscintilla/download>

1. Download
2. Open the Qt command prompt (you can find it in the start menu)
3. Add Visual Studio compiler to the path by typing "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" (with quotes, else it will give you an error message on "C:\Program") in the prompt
4. Browse to where you extracted QScintilla using the `cd` command (for example, `cd C:\Users\Bionus\Desktop\QScintilla-gpl-2.7.2`). If it's on another hard drive, use the `cd /D` command
5. Type `cd src`
6. Type `qmake qscintilla.pro`
7. Type `nmake`
8. Type `nmake install`
9. The DLL files should now have been installed and the headers added to Qt

#### Google Breakpad
If you don't want to use Google Breakpad, edit the "src/gui/CMakeLists.txt" file and change the line `set(USE_BREAKPAD 1)` into `set(USE_BREAKPAD 0)`.

If you want to use it, I won't explain here how to configure it to work with Qt, as it's a pretty complicated task.

1. Open "src/gui/CMakeLists.txt"
2. Edit the `set(BREAKPAD "D:/bin/google-breakpad")` line to match where you cloned Google Breakpad


## Linux

!!! info

    You can just run `./build.sh` at the root of the repository, and it will build everything for you.

### Dependencies

Bullets marked with `*` are mandatory, other are optional.

* `*` Qt 6.6 or higher
* `*` A C++ compiler such as g++
* `*` CMake 3.2 or higher
* `*` Node.js (for building images sources)
* OpenSSL (for HTTPS websites)
* QScintilla2 (for syntax highlighting in JavaScript filename window)
* Google Breakpad (to handle crash and show a nice-looking crash window and backup traces)

### Instructions

#### Qt
Most Linux package managers do not provide up-to-date Qt packages. As such, it is recommended to either use [aqtinstall](https://github.com/miurahr/aqtinstall), or a third-party repository.

```bash
pip install aqtinstall
aqt install-qt linux desktop 6.6.3 gcc_64 -m qtmultimedia qtimageformats qtnetworkauth qtshadertools
```

#### Compiler
You can use the g++ compiler to compile the program. If it's not already installed, the process may vary depending on your Linux distribution. Note that you can also replace g++ with clang if you want, but make sure to use the proper Qt version for your compiler.

You'll also need `cmake` for the makefile generation, and `make` for executing it.

You can install both using a package manager, such as `apt`:
```bash
sudo apt install -y "g++" "cmake" "make"
```

Or if you're using Fedora:
```bash
sudo dnf install -y "gcc-c++" "cmake" "make" --best
```

#### Node.js
Usually found in packages managers by the name `node` or `nodejs`. You can refer to the official docs:

<https://nodejs.org/en/download/package-manager/>

#### OpenSSL
If you want to access HTTPS websites, you'll need the OpenSSL libraries.

They're usually found in packages managers by the name `libssl-dev`.

#### QScintilla
If you don't want to use QScintilla, edit the "src/gui/CMakeLists.txt" file and change the line `set(USE_QSCINTILLA 1)` into `set(USE_QSCINTILLA 0)`.

Otherwise, you can find it here: <http://www.riverbankcomputing.com/software/qscintilla/download>

1. Download
2. Open a terminal
3. Browse to where you extracted QScintilla using the `cd` command (for example, `cd /home/Bionus/QScintilla-gpl-2.7.2`).
4. Type `cd src`
5. Type `qmake qscintilla.pro`
6. Type `make`
7. Type `make install`
8. The shared libraries should now have been installed and the headers added to Qt

#### Google Breakpad
If you don't want to use Google Breakpad, edit the "src/gui/CMakeLists.txt" file and change the line `set(USE_BREAKPAD 1)` into `set(USE_BREAKPAD 0)`.

If you want to use it, I won't explain here how to configure it to work with Qt, as it's a pretty complicated task.

1. Open "src/gui/CMakeLists.txt"
2. Edit the `set(BREAKPAD "D:/bin/google-breakpad")` line to match where you cloned Google Breakpad

#### Building
```bash
mkdir build
cd build
cmake ../src
make
cd ..

mv "build/gui/Grabber" "release/"
touch "release/settings.ini"
```

#### Troubleshooting
If you compile the program and run it as-is, it may say something like "no sources found". The program requires to have a few files located at a specific place to run. Since this location depends on your system (usually ~/.Grabber), you can also just make the program portable by putting the binary alongside the following files/folders, all found in the "release" folder :

* sites/
* languages/
* words.txt (not required, used for tag autocompletion)
* settings.ini (if it doesn't exist, create it using `touch settings.ini`

Another option would be to simply move the binary to the "release" folder after the compilation.


## Raspberry Pi (Raspbian)

### Preparations
Make sure that you are running Raspbian Stretch or newer on a Raspberry Pi 2 or Raspberry Pi 3. The compilation requires a lot of memory so make sure that you stop all unnecessary processes (i.e. Apache, MySQL, php-fpm) before starting the compilation. You may need to set memory-split to 16MB in _raspi-config_ or increase your swap partition size. You only need to do this for the compilation and can switch back to the old values.

You can choose between two different versions of Grabber. One is the release version, the other one the developer version. Simply download the one that suits your taste best.

### Download files
Release version:
```bash
git clone https://github.com/Bionus/imgbrd-grabber.git
```

Developer version:
```bash
git clone https://github.com/Bionus/imgbrd-grabber.git --single-branch -b develop
```

### Compilation
```bash
cd imgbrd-grabber
./build.sh
```

You can now run your program from `/home/pi/imgbrd-grabber/release`.

If you want to use the database-support of grabber, install one or all of these packages.

```bash
sudo apt install libqt5sql5-mysql
sudo apt install libqt5sql5-odbc
sudo apt install libqt5sql5-psql
```


## macOS

### Instructions

#### Qt
1. Install Xcode (https://itunes.apple.com/us/app/xcode/id497799835?mt=12).
2. Open Terminal and run this code to install Homebrew, a package manager:

    ```bash
    ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    ```

3. Install QT5 with brew.

    ```bash
    brew install qt6
    ```

4. Edit `~/.bash_profile` and add the following line: 

    ```bash
    export PATH="/usr/local/Cellar/qt6/6.6.3/bin"
    ```
    This is the default path to your QT installation. **Be sure to update the version number, or it won't work!**

#### Compiler
You can use the g++ compiler to compile the program. If it's not already installed, you can easily do so using the Homebrew package manager.

```bash
brew install gcc
```

#### Running

If you compile the program and run it as-is, it may say something like "no sources found". The program requires to have a few files located at a specific place to run. You can make the program portable by moving the following files/folders to `Grabber.app/contents/MacOS/`. Each of these items can be found in the "release" folder:

* sites/
* languages/
* words.txt (not required, used for tag autocompletion)
* settings.ini (if it doesn't exist, create it using `touch settings.ini`

#### All commands

```bash
appDir=./gui/build/release/Grabber.app/Contents/MacOS

ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
brew install qt6
brew install gcc
brew install cmake

mkdir build
cd build
cmake ..
make
cd ..

mv build/gui/gui.app release/Grabber.app
cp -r ./release/* $appDir
touch $appDir/settings.ini
```
