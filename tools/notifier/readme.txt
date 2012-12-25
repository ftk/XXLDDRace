
This program pops up notification when specified(by wildcard or regexp) player joins the server.

The server should generate text file with players list and give access to it by HTTP.

Client source code is included only.

Requires: Qt 4.8
Building: qmake && make

---
Sample players info file(with commentaries after '#'):

1356460741				# generation time(UNIX timestamp)
2						# amount of servers
2						# amount of players on the first server
test1 server			# server name
dm1						# map name
Vasya Pupkin			# name of player 1
						# clan of player 1
test02					# name of player 2
clan02					# clan of player 2
0						# amount of players on the second server
test2 server			# server name
dm2						# map name
