# game-client

Install SDL 2.0

* https://www.libsdl.org/download-2.0.php

Install RapidJSON

* https://github.com/miloyip/rapidjson/

FakeNetworkClient is merely to test updating GameState in GameController without
having the actual NetworkClient running yet.  When our actual NetworkClient is
finished, FakeNetworkClient should be deleted and any calls to FakeNetworkClient
should be replaced with the real NetworkClient.  They should functionally work the
same however from the perspective of GameController.