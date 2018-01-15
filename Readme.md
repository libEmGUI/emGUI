# emGUI library

This C library stands for creating simple windows-like **User Interfaces** with **Touch** capability
on embedded and other platforms, that has basic C runtime environment.

Key features
* **ModalDialog** system
* **WindowManager** system
* Rich **Callback** and **Event** subsystem
* flexible porting layer 
* independency from fonts and images
* small memory footprint

## Ports

This library was ported to

* [Arduino](https://github.com/libEmGUI/emGUI-arduino) (tested on esp8266)
* [Windows desktop](https://github.com/libEmGUI/emGUI-example)
* Cortex M family processors

## Widgets

At the moment we support several base widgets components

* **Widget** - a base component for the UI that is used as building block for other. It provides a
hierarchy for embedding widgets into each other. It also 
* **Label** - all-in-one solution for text output. It supports
  * **Single line** mode
  * **Multi line** mode with paging
  * **Word wrapping** by word
* **Plot** - for simple graph plotting
* **Button** - supports
  * **Text Mode** - simple font-based button 
  * **Picture Mode** - add an icon to the button
  * **Picture+Text Mode** - add an icon + description under the icon
  
Components that was introduced in 1.0.0, but disabled at the moment due to unresolved dependencies

* **Console** - a window that shows *linux-like boot console* - depends on `freeRTOS queues`
* **Keyboard** and **KeyboardRow** - depends on generic int types and 320*240 screen resolution
* **PictureStack** - just a list of pictures. Provides convenient picture storage place. Depends on **C-Array pictures**
* **ProgressBar** - Acts as standalone widget and as a part of **ModalDialogs**. Depends on generic int types.
  
## Windowing system

Library provides windowing system for making UI implementation more intuitive and simple

We support

* **Window** - a widget-based container for other components
* **WindowManager** - operates **Window** instances and allows to **open** **close** 
and pass **Touch** events to windows.
It also supports a **Window list** - an instance that holds a history of opened windows, 
and allows you to get to the previous opened windows if you close active one.
* **StatusBar** - an instance that shows current window title and provides close button to close current active window.
* **ModalDialog** - a convenient subsystem that allows popping windows-like modal dialogs

## Future plans

* Port disabled widgets
* **Touchless** interfaces - add some kind of focus marker and add an API to move focus around
* Add more **Widgets**
* **C+ bindings** or a separate fork