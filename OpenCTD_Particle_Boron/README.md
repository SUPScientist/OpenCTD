# OpenCTD for the Particle Boron
This directory contains code to operate a conductivity, temperature, and pressure (or depth) sensor package for DIY oceanography.

This OpenCTD design is intended to be a near replica of the original OpenCTD (of the OpenCTD_qDuino flavor) from OceanographyforEveryone (https://github.com/OceanographyforEveryone/OpenCTD). I pulled in multiple libraries for the [Particle Boron](https://docs.particle.io/boron/) directly through the Particle library manager.

### Acknowledgments
Of course, this Particle Boron version of the OpenCTD borrows quite heavily from OceanographyforEveryone's so I am indebted to [@SouthernFriedScientist](https://github.com/SouthernFriedScientist) and others. I also received substantial guidance from [@IanTBlack](https://github.com/IanTBlack), creator of the [CTDizzle](https://github.com/IanTBlack/CTDizzle). And a huge thanks to the [Particle for Good](https://www.particle.io/for-good/) program which donated the Particle Borons which I'm using here.

### Instructions
I'll work on filling in my own instructions and bill of materials but, for now, please see how the experts over at OceanographyforEveryone recommend building the instrument: https://github.com/OceanographyforEveryone/OpenCTD/tree/master/OpenCTD_qDuino. Other than using the Particle Boron instead of the qDuino, differences from their design include using what they list as an "Alternate Component" for pressure sensing&mdash;the [SparkFun Pressure Sensor Breakout - MS5803-14BA](https://www.sparkfun.com/products/12909).

I'm using [Particle Workbench/VS Code](https://www.particle.io/workbench/) with local compilation. The code currently calls `SYSTEM_MODE(MANUAL);` before `void(setup)` and then `Cellular.off();` immediately inside of `void(setup)` in order to avoid racking up unwanted cellular bills prior to dialing in the sensor communication protocols.

### Subdirectories
./OpenCTD_complete_noCell/ contains the full script which polls and records data from the sensors. The other subdirectories here contain example code and compiled binaries (for )

### todo
- add .gitignore (.DS_Store and probably lots of the .vscode stuff, not sure, research Particle Workbench best practices)
- utilize cell module for getting real time
- add real time to datalog
- utilize cell module for transferring data after deployment (add a counter to determine how long it's been out of water)
- copy and then edit build instructions from main OpenCTD projects and see if CTDizzle has some additional pointers
- add sensors!
