// Project: Pool
// Name: Sam Terrazas
// File: Pool.h
// Created: 01/28/2019 2:49 PM
// Updated: 02/04/2019 10:51 AM
// 
// I declare that the following source code was written by me, or provided
// by the instructor for this project. I understand that copying source
// code from any other source, providing source code to another student, 
// or leaving my code on a public web site constitutes cheating.
// I acknowledge that  If I am found in violation of this policy this may result
// in a zero grade, a permanent record on file and possibly immediate failure of the class. 

/*
 * Reflection:
 *
 * After doing the readings, looking through my notes, the pdf of of the project
 * and working the code, I can say that this was probably one of the hardest projects that
 * I have ever done.
 *
 * I struggled with it for a while. I know part of the reason why I struggled so much was
 * because I did not complete the design portion. I was so lost by the time the design
 * was due that I had no hope in finishing it for that.
 *
 * I was steadily making progress on the code, but not really having a grasp of it until
 * Sunday. On Saturday evening my Mom had called to talk with me and I explained the trouble
 * I was having with the code. She then very lovingly brow beat me for a bit for not asking
 * my Dad for help.
 *
 * My Dad is a programming instructor for Learning Tree International and in addition to
 * everything else he has done, he was also a member of the C++ Standards Committee. In the
 * past I used to get his help for a lot of projects but then one day I had the thought that
 * if I couldn't do the code by myself then what good of a programmer would I be? So I then
 * went my own way.
 *
 * My Mom reminded me that it was okay to ask for help, that being tutored isn't giving up.
 * So I met with my Dad online for a couple of hours and he was able to explain the concepts
 * to me and help me see where I was going wrong in my code so now I can read the code and
 * actually understand what it is doing.
 *
 * I honestly didn't think I would get to this place but now I am. I am very happy for the
 * learning that I gained while doing this project and it has certainly touched concepts
 * of controlling the memory that I had never conceived before.
 */

#ifndef POOL_H
#define POOL_H

#include <cstddef>
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
  void link( char* );
public:
  explicit Pool( size_t const& elem_size, size_t const& block_size = 5 );
  ~Pool();
  void* allocate(); // get a pointer inside a pre-allocated block for a new object
  void deallocate( void* ); // free an object's slot (push the address on the "free list")

  void profile() const;

};
#endif // POOL_H
