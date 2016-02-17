# EFFEX SDK
*Latest API of Effex (for Cinema 4D) *

This is the latest API/SDK for **Effex** *for Cinema 4D* (www.dpit2.de)

It provides third parties with an SDK to access (read & modify) all simulation/framework data in Effex 2.7+.
Furthermore it allows to extent Effex functionality with your own plugin nodes and provides tools for multiprocessor execution of such nodes.

**Plugins for the following node types can currently be created**
- Constraints (CS), Particle Constraints (PCS)
- Grid/Particle/Dual Forces (GF/PF/DF)
- Grid-/Particle Operators (GOP/POP)

Please see the examples in the 'source' folder.

**Requirements**
- Cinema 4D R16 (to link against its api)
- Windows/OSX
- Effex 2.70.60 (or higher)
- Visual Studio 2013 and XCode 5.x (but any C++11 compliant compiler should work)

**How to use**
*(There is a Visual Studio solution file available that is ready to compile but you need to..)*
- add the cinema 4d api project to the VS solution
- Set c4d api as target dependency for the effex sdk project in VS

Alternatively you can add the source files and the api files to an existing C4D SDK project.

*The folders in this repository contain the following files:*
- api: the Effex API
- settings: just for user convenience the C4D API property presets required
- source: project example source code for each possible plugin node type
- res: project example plugins resource description files


**Documentation**

The documentation of all API functions/classes/members can be found in the Effex documentation inside of Cinema 4D itself or in the online documentation (see www.fluidsimulation.de).
Also I have opened up a plugin development subforum in the Navié community forums. 
Feel free to ask any questions in there if the docs don't help.

