# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

* **Widgets**
  * **Status Bar** is now a widget, not singleton
  * **WindowManager** (former `Interface`) got complete rewrite. It doesn't rely on `xWindow` structs anymore and uses own dynamic list of windows
  * **Button widget** now can be created from **picture**, **text** or both
  * **Button widget** now have release effect emulation
  * **MenuButton** now removed in favor to **Button**
  * **PlotWidget** draft implementation

* **Modal dialogs** 
  * Automatic creation of `ModaDialogWindow` on first use
  * Deprecate separate handlers for every button
  * Automatic dialogs now use **`ID=0`**
  * **Modal dialogs** now can store strings for  header and message inside

* **Pictures**
  * Use pictures filenames instead of C-Array
  * Remove all picture references from library

* **Memory management**
  * Add null-dereference checks
  * Add memsets for mallocs
  * Initial structure for **memory management** added. One can remove widgets from stack and use **`vWidgetDispose`**

* **Code**
  * Use stdint instead of legacy types
  * Add **porting layer**
  * Fix header guards
  * Normalize library defines
  * Normalize library options
  * Improved **code simplicity** and **reliability**
  * A lot of **stability fixes** and logic errors fixes
  * Extern "C" definitions fixed
  * Autoformat code
  
* **Fonts**
  * Remove fonts from library

## [1.0.0] - 2013-03-23
### Added
- Initial library version