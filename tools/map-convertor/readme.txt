  Requires python2 and TeeworldsMapLib !!!

    download from:
https://github.com/erdbeere/tml/



  Usage example:
    from png to teeworlds map:
python2 map.py sample.png sample.map

    from txt to teeworlds map:
python2 map.py maze.txt maze.map


  * See color codes and symbol codes in map.py source.




  Generating mazes (may not work):

g++ dfs-maze.cpp -o generator && ./generator
python2 map.py maze.txt maze.map
