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
  
Components that has
  
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

* **Touchless** interfaces - add some kind of focus marker and add an API to move focus around
* **C+ bindings** or a separate fork