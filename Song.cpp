/*******
 ** File:    Song.cpp
 ** Project: Project 3 - UMBC Music Player
 ** Author:  Jon Woods
 ** Date:    11/3/2022
 ** Section: 20/22
 ** Email: jwoods6@umbc.edu
 **
 ** This file contains the syntax for all functions involving Song objects. These functions
 ** initialize, store and call the title, artist(s), and year a song came out as well as its rank
 ** in the Top 100 songs of that year. This file also sets and calls the consecutive Song pointer
 ** of a particular Song object within a linked Playlist.
*******/

#include <iostream>
#include <string>

#include "Song.h"
using namespace std;

// Song()
// Default constructor for a new Song object.
Song::Song() {
  m_title = "New Title";
  m_artist = "New Artist";
  m_year = 0;
  m_rank = 0;
  m_next = nullptr;
}

// Song() overload constructor
// Given the data for a song, creates a new Song object storing that data.
Song::Song(string title, string artist, int year, int rank ) {
  m_title = title;
  m_artist = artist;
  m_year = year;
  m_rank = rank;
  m_next = nullptr;
}

// SetTitle()
// Given a string, replaces the title of a Song object with that string.
void Song::SetTitle(string title) {
  m_title = title;
}

// SetArtist()
// Given a string, replaces the artist of a Song object with that string.
void Song::SetArtist(string artist) {
  m_artist = artist;
}

// SetYear()
// Given an integer between 2010 and 2021, replaces the release year of a Song object with
// that integer.
void Song::SetYear(int year) {
  m_year = year;
}

// SetRank()
// Given an integer between 1 and 100, replaces the Top 100 rank of a Song object with that integer.
void Song::SetRank(int rank) {
  m_rank = rank;
}

// GetTitle()
// Returns the string containing the title of a Song object.
string Song::GetTitle() {
  return m_title;
}

// GetArtist()
// Returns the string containing the artist of a Song object.
string Song::GetArtist() {
  return m_artist;
}

// GetYear()
// Returns the integer containing the release year of a Song object.
int Song::GetYear() {
  return m_year;
}

// GetRank()
// Returns the integer containing the Top 100 rank of a Song object.
int Song::GetRank() {
  return m_rank;
}

// GetNext()
// Returns the Song pointer linked after a Song object.
Song* Song::GetNext() {
  return m_next;
}

// SetNext()
// Given a Song pointer, replaces the linked consecutive pointer of a Song object with that pointer.
void Song::SetNext(Song* nextSong) {
  m_next = nextSong;
}
