/*******
 ** File:    MusicPlayer.cpp
 ** Project: Project 3 - UMBC Music Player
 ** Author:  Jon Woods
 ** Date:    11/3/2022
 ** Section: 20/22
 ** Email: jwoods6@umbc.edu
 **
 ** This file contains the syntax for all functions involving MusicPlayer objects. In this case, a
 ** MusicPlayer consists of a vector of Song pointers and a Playlist pointer that those songs can be
 ** added to. Alongside the constructor and deconstructor, the other functions fill the Song catalog
 ** vector using a file input, display menus for the program, receive user inputs, and call the
 ** Playlist functions.
*******/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include "Song.h"
#include "Playlist.h"
#include "MusicPlayer.h"
using namespace std;

// MusicPlayer()
// Default constructor for a MusicPlayer object. Addresses the Playlist pointer to an empty playlist.
MusicPlayer::MusicPlayer() {
  m_playList = new Playlist();
}

// ~MusicPlayer()
// Default destructor for a MusicPlayer object. Replaces the catalog vector and Playlist pointer
// with empty ones.
MusicPlayer::~MusicPlayer() {
  m_playList = new Playlist();
  vector<Song*> emptyCatalog;
  m_songCatalog.swap(emptyCatalog);
}

// LoadCatalog()
// Given the name of a music file, reads that music file, converts the data into Songs, and adds
// them to the catalog vector.
void MusicPlayer::LoadCatalog(string filename) {
  fstream reader;
  reader.open(FILE_NAME);
  string title, artist, year, rank;
  // Check every statement in the file, as separated using "|"
  while (getline(reader, title, DELIMITER) && getline(reader, artist, DELIMITER)) {
    getline(reader, year, DELIMITER);
    getline(reader, rank);
    m_songCatalog.push_back(new Song(title, artist, stoi(year), stoi(rank)));
  }
  cout << "Songs loaded: " << m_songCatalog.size() << endl;
}

// MainMenu()
// Displays the main menu of the program and calls other functions based on user input.
void MusicPlayer::MainMenu() {
  int choice;
  do {
    // User input with validation loop
    do {
      cout << "What would you like to do?\n1. Display Songs by Year\n2. Add Song\n3. Display Playlist\n4. Play Song\n5. Quit" << endl;
      cin >> choice;
    } while (choice < 1 || choice > 5);
    switch (choice) {
    case 1: DisplaySongs(); break;
    case 2: AddSong(); break;
    case 3: DisplayPlaylist(); break;
    case 4: PlaySong(); break;
    }
  } while (choice != 5); // If user chooses 5 on the main menu, the program ends
  cout << "Thank you for using the UMBC Music Player." << endl;
}

void MusicPlayer::DisplaySongs() {
  int year;
  do {
    cout << "Which year would you like to display? (" << LOW_YEAR << "-" << HIGH_YEAR << ")"  << endl;
    cin >> year;
  } while (year < LOW_YEAR || year > HIGH_YEAR);
  // Songs are sorted in groups of 100 per year
  int firstLocation = (year - LOW_YEAR) * 100;
  int LastLocation = firstLocation + 99;
  
  cout << "*****" << year << "*****" << endl;
  // Check every element in the vector between firstLocation and lastLocation
  for (int i = firstLocation; i <= LastLocation; i++) {
    cout << i+1 << ". " << *m_songCatalog.at(i) << endl;
  }
}

// AddSong()
// Chooses an index of m_SongCatalog based on user input and adds the Song pointer at that index to
// the end of m_playList.
void MusicPlayer::AddSong() {
  DisplayPlaylist();
  cout << "Choose the songs you would like to add to the playlist." << endl;
  DisplaySongs();
  int numSong;
  // User input with validation loop
  do {
    cout << "Enter the number of the song you would like to add:" << endl;
    cin >> numSong;
  } while (numSong < 1 || numSong > int(m_songCatalog.size()));
  Song* newSong = m_songCatalog.at(numSong-1);
  m_playList->AddSong(newSong->GetTitle(), newSong->GetArtist(), newSong->GetYear(), newSong->GetRank());
}

// DisplayPlaylist()
// Dereferences m_playList and calls GetPlaylistDetails at every node.
void MusicPlayer::DisplayPlaylist() {
  if (m_playList->Size() == 0) {
    // Notify user if no songs have been added to m_playList
    cout << "***Current Playlist is Empty***" << endl;
  } else {
    cout << "Your Playlist:" << endl;
    int i = 0;
    // check every node in m_playList
    while (i < m_playList->Size()) {
      cout << i+1 << ". " << *m_playList->GetPlaylistDetails(i) << endl;
      i++;
    }
  }
}

// PlaySong()
// Dereferences m_playList and calls PlayAt at a location given by user input.
void MusicPlayer::PlaySong() {
  DisplayPlaylist();
  int size = m_playList->Size();
  if (size == 0) {
    // Nothing happens if the playlist is empty
    cout << "No songs to be played." << endl;
    return;
  }
  int track;
  // User input with validation loop
  do {
    cout << "Which song would you like to play?" << endl;
    cin >> track;
  } while (track < 1 || track > size);
  // Display which Song node is playing and remove it from m_playList
  cout << "Played: " << *m_playList->GetPlaylistDetails(track-1) << endl;
  m_playList->PlayAt(track-1);
}
