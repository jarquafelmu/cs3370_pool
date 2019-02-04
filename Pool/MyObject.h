// Project: Deque
// Name: Sam Terrazas
// File: Pool.h
// Created: 01/28/2019 2:49 PM
// Updated: 01/28/2019 2:49 PM
// 
// I declare that the following source code was written by me, or provided
// by the instructor for this project. I understand that copying source
// code from any other source, providing source code to another student, 
// or leaving my code on a public web site constitutes cheating.
// I acknowledge that  If I am found in violation of this policy this may result
// in a zero grade, a permanent record on file and possibly immediate failure of the class. 

#ifndef MY_OBJECT_H
#define MY_OBJECT_H

#include <string>
#include <utility>
#include "Pool.h"

using std::string;
using std::ostream;

class MyObject {
  // data members
  int id_;
  string name_;
  static Pool Pool_;

  // private constructor so that users are forced 
  // to use our Create factory function
  MyObject( int const& i, string nm );
public:
  // constructors / deconstructors
  ~MyObject () = default; // TODO: define ~MyObject()
  MyObject ( MyObject const& other ) = delete;
  MyObject ( MyObject&& other ) noexcept = delete;

  // overloaded operators
  auto operator=( MyObject const& other )->MyObject& = delete;
  auto operator=( MyObject&& other ) noexcept->MyObject& = delete;

  auto operator new( size_t size ) -> void*;
  auto operator delete( void* ) -> void;
  friend auto operator<<( ostream& out, MyObject const& my_object )->ostream&;

  // methods
  static MyObject* Create ( const int& id, const string& name );
  static auto Profile() -> void;
};
#endif // MY_OBJECT_H
