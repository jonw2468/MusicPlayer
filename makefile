CXX = g++
CXXFLAGS = -Wall -g

proj3: MusicPlayer.o Song.o main.cpp Playlist.o
	$(CXX) $(CXXFLAGS) MusicPlayer.o Song.o Playlist.o main.cpp -o proj3

MusicPlayer.o: MusicPlayer.cpp  MusicPlayer.h Playlist.o Song.o
	$(CXX) $(CXXFLAGS) -c MusicPlayer.cpp

Playlist.o: Playlist.h Playlist.cpp
	$(CXX) $(CXXFLAGS) -c Playlist.cpp

Song.o: Song.cpp Song.h
	$(CXX) $(CXXFLAGS) -c Song.cpp

run:
	./proj3

run1:
	./proj3 music.txt

val1:
	valgrind ./proj3 music.txt

clean: 
	rm *~
	rm *.o
