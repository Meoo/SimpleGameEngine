SimpleGameEngine
================

Simple game engine using SFML2.
This engine is designed to quickly prototype games, as it was created to be used in Ludum Dare Competition (http://www.ludumdare.com/compo/).
The code is distributed under license GPLv3.


Features
--------

### Screens ###

Different game states are handled using "Screens".


### Sprite animations ###

TBD


### Physics engine ###

Quadtrees

TBD


### Continuous map ###

TBD


### Doxygen documentation ###

TBD


### Asynchronous tasks ###

Run tasks on a secondary thread.


### Resources managing ###

Create resources handles from a manager, and the file will be loaded automatically on a secondary thread.
If the resource is not ready when you need it, the game will freeze until it is


Planned features
----------------

### Networking ###

...maybe


Third party
-----------

SGE use the following libraries and tools :

* Premake4 (http://industriousone.com/premake)
* SFML2 (www.sfml-dev.org)
* Tinythread++ (http://tinythreadpp.bitsnbites.eu/)
* Default font by Rodrigo Fuenzalida (http://www.dafont.com/poetsen-one.font)

To build SGE, you have to download and build SFML2.
You will also need binaries of Premake4.
