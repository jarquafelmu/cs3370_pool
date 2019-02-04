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

#ifndef POOL_H
#define POOL_H

#include <cstddef>
#include <iosfwd>
#include <iostream>

class Pool {
  char** pool_list_ { nullptr };
  char* free_list_ { nullptr };

  size_t size_ {};
  size_t live_cells_ {};
  size_t free_cells_ {};

  size_t const elem_size_ {};
  size_t const block_size_ {};
  
  static std::string format_address( void* p );

  void grow();
  void link( char* ) const;
public:
  Pool ( size_t const& elem_size, size_t const& block_size = 5 );
  ~Pool ();
  void* allocate(); // get a pointer inside a pre-allocated block for a new object
  void deallocate( void* ); // free an object's slot (push the address on the "free list")

  void profile();

};
#endif // POOL_H

