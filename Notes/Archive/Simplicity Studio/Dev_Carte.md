__STATIC_INLINE : Skipping the actual function call and return

- code inside #ifdef #endif will be execute depend on the condition
> #ifdef  means "if the following is defined"

*********************************
*********************************
*	SOC-SMARTPHONE		*
*********************************
*********************************




*****************************************
*	Structure of Main program	*	graphics.c of soc-smartPhone
*****************************************
***** Initialization *****
- Initialize device
> initMcu();

- Initialize board
> initBoard();

- Initialize application
> initApp();

- Initialize LEDs
> BSP_LedsInit();


- Initialize Stack
> gecko_init(&config);


***** Main function *****
Using while loop for: 
- Check for stack event
- Handle event
> appHandleEvents(evt);


*****************************************
*	Affiche un string à l'écran	*	graphics.c of soc-smartPhone
*****************************************
***** Initialization *****

- Display module
> DISPLAY_Init();

- Display Driver Module
> DMD_init();

- GLIB context 			(background)
> GLIB_contextInit()


> graphWriteString(string);


***** Afficher *****	graphWrireString(string);

- Clear the background
> GLIB_clear(GLIB_Context_t *pContext);

- Set strWidth, posX, posY for function 
> GLIB_drawString(pContext, pString, len, posX, posY, 0);	// main function pour l'affichage un string

- Update all strings à l'écran
> DMD_updateDisplay();


***** Resume *****

// avant utiliser cette fonction, il faut vérifier que LCD est supporté	
> #ifdef FEATURE_LCD_SUPPORT



*************************************************
*	Lire la valeur d'un pin in GPIO port	*	app-ui.c of soc-smartPhone
*************************************************
***** Initialization *****

> GPIO_PinModeSet(BSP_BUTTON0_PORT, BSP_BUTTON0_PIN, gpioModeInput, 1);
> GPIO_PinModeSet(BSP_LED0_PORT, BSP_LED0_PIN, gpioModePushPull, 1);


***** Lire la valeur *****

> GPIO_PinInGet(BSP_BUTTON0_PORT, BSP_BUTTON0_PIN);




*********************************
*	Set TIMER for event 	*	app-ui.c of soc-smartPhone
*********************************

> gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(APP_RC_DISCHARGE_PERIOD), UI_TIMER, false);
- Set a timer equal to "duration to discharge capacitors in GPIO ports
- UI_TIMER 	is the handle
- false		means timer is repeating


*********************************
*********************************
*	SOC-THERMOMETRE		*
*********************************
*********************************

***** Measure la température *****
- la température est stocké dans un tableau de taille 5 type uint8_t
- la première celllule contient le flag
(les informations pour les données : type de température, time stamp)
- les 4 cellules suivants contient les données de la température
(les données est stocké dans un variable de type uint32_t donc 4 cellules * 8 = 32 bits)

- Ajouter le flag au premier cellule
> UINT8_TO_BITSTREAM(p, flags);		// il faut convertir la type de flags à BITSTREAM

- Lire la température 
> Si7013_MeasureRHAndTemp(I2C0, SI7021_ADDR, &rhData, &tempData)


***** Affichage de la température *****
-

#define HTM_TEMP_VALUE_TEXT                 "\nTemperature:\n%3d.%1d C / %3d.%1d F\n"
#define HTM_TEMP_VALUE_TEXT_DEFAULT         "\nTemperature:\n---.- C / ---.- F\n"
#define HTM_TEMP_VALUE_TEXT_SIZE            (sizeof(HTM_TEMP_VALUE_TEXT_DEFAULT))

char tempString[HTM_TEMP_VALUE_TEXT_SIZE];

snprintf(tempString,
           sizeof(HTM_TEMP_VALUE_TEXT_DEFAULT) + 4,
           HTM_TEMP_VALUE_TEXT,
           (uint8_t)(tempData / 1000),
           (uint8_t)((tempData / 100) % 10),
           (uint8_t)(tempDataF / 1000),
           (uint8_t)((tempDataF / 100) % 10));

appUiWriteString(tempString);























