**camMovementOsc**  
openFrameworks application to stream horizontal and vertical movement over OSC using OpenCV.

Runs in the command line, reporting feedback.  
Tested with openframeworks 0.10 on macOS 10.12 and RaspberryPi.

##### OSC
Sends 2 float values from -1.0 to 1.0 on both axes.
- The 1st value is the horizontal axis : `/cam/0`.
- The 2nd value is the vertical axis : `/cam/1`.

Upon reception, the values could be smoothed.
- `0` means no movement.
- `-1` means fast movement to the left.
- `+1` means fast movement to the right.

Default OSC address `localhost:12200`.

##### Install
1. Install OpenFrameworks and the ofxCv addon.
2. Use the project generator to setup your build environment.
