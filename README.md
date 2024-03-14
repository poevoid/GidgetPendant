# GidgetPendant
Fun and cute electronic pendant wearable! Falling hearts! Rainbows! Audio Spectrums! WiFi!

Made with a qtpy esp32s3, the pendant briefly connects to wifi to grab time from an NTP server and starts keeping track of time from there. Once connected, the SH1106 screen will change from the default framebuffer to a horizontal line that visualizes the signal from the small electret mic connected to it. If the capacitive touch button is pressed, the screen will switch modes. Currently there are four to choose from:

1. Audio spectrum visualizer/oscilloscope
2. Watch or clock, this just displays the time bouncing around the screen. (Yes, it will eventually hit a corner lol it's satisfactory.'=
3. temperature & humidity from connected sensors
4. Cute hearts fall from the scren while the back of the pendant glows in a fading rainbow, from one color to the next 
