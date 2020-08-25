## CREATE SOC-EMPTY BLE
https://www.silabs.com/community/wireless/bluetooth/knowledge-base.entry.html/2018/12/12/bluetooth_soc-empty-wk3r
***
#	Add Debug Function using USART
### Install Minicom
https://www.cyberciti.biz/tips/connect-soekris-single-board-computer-using-minicom.html
Use "dmesg" to figure out name of port to configure in "Serial Port Setup" of Minicom

### Add printLog() function to Project | RECOMMENDED !!!
Modifie variable in app.c
```
#define DEBUG_LEVEL 1
```
### Add Write_Usart function to Project
https://www.silabs.com/community/wireless/bluetooth/knowledge-base.entry.html/2018/08/28/using_virtual_compo-IYYh
Include stdio.h / retargetserialhalconfig.h / retargetserial.h / em_usart.h / stdarg.h to your project
Add 2 functions (in old project) 
```
void send_string(char * string)
void Write_Usart(const char* format, ...)
```
to your app.c

**Init USART communication before first call Write_Usart();**
```
RETARGET_SerialInit();
```
**Modifine in hall-config.h**
```
#define HAL_VCOM_ENABLE                   (1)
```

**********************************************
#	Add GRAPHIC to display on LCD
https://www.silabs.com/community/wireless/bluetooth/knowledge-base.entry.html/2017/04/26/enable_lcd_screenon-oHEL

**Add lcd-graphics folder to your project**

**Follow the link but add an extra path to the include paths**
"${StudioSdkPath}/hardware/kit/common/drivers"

**and modified the 4th path to :**
"${StudioSdkPath}/hardware/kit/BOARD_NAME/config"
Ex: BGM13_BRD4306A

**Add define for "spidisplay frequency" in hal-config.h**
```
#define HAL_SPIDISPLAY_FREQUENCY                      (1000000)
```
**Include graphics.h in your project**
```
#include "graphics.h"
```
**Initialize GRAPHICS before the first write to LCD**
```
GRAPHICS_Clear();
GRAPHICS_AppendString("Hello World!\n");
GRAPHICS_Update();
```
*********************************************
# Add Energy Profilter (live)
https://www.silabs.com/community/software/simplicity-studio/forum.topic.html/no_functions_display-KJgm

#### Instruction in Simplicity
[Help] > [Contents] > [Energy Profile Guide] > [Starting an Energy Analysis Session] > [Customer Design Information] > [Software Configuration]

add `BSP_TraceSwoSetup();` after initApp();

#### Run:
Rignt click on project -> Profile As -> Energy Profiler
![Imgur](https://i.imgur.com/XQz0kgm.png)
**Attention !!!**
 When using the GCC ARM toolchain the code optimizations have to be set to "None" in the project properties for the code correlation to work correctly
 (right click the project folder, select "Properties" and then [C/C++ Build] > [Settings] > [GNU ARM C Compiler] > [Optimization] > [Optimization Level].

**********************************************
#	Added library for app.c
```
/**** Library to write string to USART - Display on the screen ****/
#include "stdio.h"
#include "retargetserialhalconfig.h"
#include "retargetserial.h"
#include "em_usart.h"
#include "stdarg.h"

/**** Library to display on the LCD ****/
#include "graphics.h"

/**** Library to configation GPIO pin ****/
#include "gpio.h"

/**** Library to turn on Sleep Mode ****/
#include "sleep.h"

// BSP for code correlation
#include "bsp.h"
#include "bsp_trace.h"
```
**********************************************
#   ERROR : 
## In build project :
`arm-none-eabi-gcc: error: : No such file or directory`
For this error, the problem here is the files `.a` in these folder :
```
~/PROJECT_FOLDER/platform/radio/rail_lib/autogen
~/PROJECT_FOLDER/protocol/bluetooth/lib
```
is missing or not belong to your computer

Normally, in .gitignore, we ignore file .a (because these files are depend to your computer - that means they are particulier for your computer) but Simplicity Studio doesn't automatic generate these files so it causes the error no such file or dictory

**Solution :** We create an another soc-empty project and go to these folder, copy and paste the missing file .a to your current project.
Good luck !!
.
.
.
.
.
.
.
..
.
.
.
.

.
.
.










