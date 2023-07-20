/*******
 ** File:    Playlist.cpp
 ** Project: Project 3 - UMBC Music Player
 ** Author:  Jon Woods
 ** Date:    11/3/2022
 ** Section: 20/22
 ** Email:   jwoods6@umbc.edu
 **
 ** This file contains the syntax for all functions involving Playlist objects. In this case,
 ** a Playlist is a linked list of nodes that point to Song objects in an order determined by each
 ** Song's m_next value. The functions here construct and deconstruct the linked list, add new Song
 ** nodes to the list with new Song data stored, call the data within the list, and retain the order
 ** of the list when a Song is "played" or removed from the Playlist.
*******/

#include <string>
#include <fstream>
#include <iostream>
#include "Song.h"
#include "Playlist.h"
using namespace std;

// Playlist()
// Default constructor for a Playlist object. Creates an empty linked list.
Playlist::Playlist() {
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// ~Playlist()
// Default destructor of a Playlist object. Removes all Song pointers from the linked list and
// resets it to an empty one.
Playlist::~Playlist() {
  Song* curr = m_head;
  // check every node in the list
  while (curr->GetNext() != nullptr) {
    m_head = curr->GetNext();
    delete curr;
    curr = curr->GetNext();
  }
  // no head or tail after list has been destructed
  m_head = nullptr;
  m_tail = nullptr;
}

// AddSong()
// Given the data for a Song object, creates a new Song node pointing to that data.
// Adds the node to the end of the linked list and updates the tail node of the list..
void Playlist::AddSong(string newTitle, string newArtist, int newYear, int newRank) {
  Song* newSong = new Song(newTitle, newArtist, newYear, newRank);
  newSong->SetNext(nullptr);
  if (m_size == 0) {
    // First song being added is head as well
    m_head = newSong;
  } else {
    // Place any other song behind the previous tail
    m_tail->SetNext(newSong);
  }
  m_tail = newSong; // Added song becomes the new tail node
  m_size++;
}


// Size()
// Returns the number of song nodes in a Playlist object.
int Playlist::Size() {
  return m_size;
}

// GetPlaylistDetails()
// Given a node location, returns the location-th Song node in a Playlist object.
Song* Playlist::GetPlaylistDetails(int location) {
  Song* curr = m_head;
  // Iterate through the linked list location times
  for (int i = 0; i < location; i++) {
    curr = curr->GetNext();
  }
  return curr;
}

// PlayAt()
// Given a node location, "plays" a song by deleting the location-th Song node in a Playlist object.
// Updates m_head and m_tail as needed.
void Playlist::PlayAt(int location) {
  Song* curr = m_head;
  // Nested if-else where each condition represents a case of which Song node is being deleted
  if (location == 0) {
    // If first song is played, remove the first Song node with the second node as the new head
    m_head = curr->GetNext();
    delete curr;
  } else {
    Song* prev = m_head;
    if (location == m_size-1) {
      // If first song is played, remove the last Song node with the node before it as the new tail
      while (curr->GetNext() != nullptr) {
	prev = curr;
	curr = curr->GetNext();
      }
      delete curr;
      prev->SetNext(nullptr);
      m_tail = prev;
    } else {
      // If any other song is played, remove the corresponding Song node and update the order
      for (int i = 0; i < location; i++) {
	curr = curr->GetNext();
      }
      Song* next = curr->GetNext();
      prev->SetNext(next); // songs before and after curr become adjacent instead
      delete curr;
    }
  }
  m_size--;
}
