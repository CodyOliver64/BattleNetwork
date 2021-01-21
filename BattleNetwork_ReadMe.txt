Battle network is a recent project where I attempt to recreate the battle system from one of my childhood classics, Megaman Battle Network.

The game is written in C++ using the SFML library to handle high level system resources as well as graphics. This was my first game project without the assistance
of a game engine, and through it I learned about the convenience provided by these engines. Having to write everything from scratch gave me a new appreciation
for these tools and opened my mind to their development.

The Battle Network project is still largely a work in progress, and over time I hope add to it fleshing out the game in many of the areas below:

- Fix frame based timing (if while playing the game it seems slow, it may be due to the specific frame based timing used. I plan to implement a more sophisticated way to 
  control the flow of the game to allow for support on older devices, as well as to increase the scalability of things like animations and attack patterns)
- Add more enemy types with dynamic spawning (continue to expand the Enemy class system)
- Add Battle Abilities/Chip Menu Selection
- Add Boss Encounters
- Begin to develop the overworld adventure mode (stretch goal)


To download the zip file, use the Google Drive link below:
https://drive.google.com/file/d/1EYnqUP-c4GBXJUZrE0TRH5vqk0DRX-Zk/view?usp=sharing

Zipped in this file is all of the source code and assets, along with an executable to run the game. Navigate to the executable by following the steps below:

Battle Network -> Battle Network -> Run the Battle Netwok.exe application

If you are missing any dll files after running the application, you may have to install the latest SDK for windows 10.
Installing Visual Studios will also correct the issue by giving you the latest redistributable for Visual C++
Use the link below to locate the necessary package:
https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk/



Battle Network runs on Windows platforms, to play the game use W,A,S,D to move and Space to shoot

If there are any issues with running the game, or for quick access, be sure to check out my website at https://olivercody64.wixsite.com/game-dev/fiea-portfolio