# game-client

Install SDL 2.0
* https://www.libsdl.org/download-2.0.php

Install RapidJSON
* https://github.com/miloyip/rapidjson/

Install the following on Linux (fixes issue where some glut libraries can't be found by CMAKE):
* sudo apt-get install libxmu-dev libxi-dev


RUNNING THE GAME:

A host player must run the game server found here:
* https://github.com/awesomegroupidunno/game-server

Connecting players must change the following line in Main.cpp:
* */ client->connect_to_server("172.31.1.42", "10001"); */

The IP address must match the IP of the host running the game server
