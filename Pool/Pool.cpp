// Project: Pool
// Name: Sam Terrazas
// File: Pool.cpp
// Created: 01/28/2019 3:03 PM
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

#include "Pool.h"
#include <algorithm>
#include <sstream>
#include <cassert>

using namespace std;

/// <summary>
/// Initializes a new instance of the <see cref="Pool"/> class.
/// </summary>
/// <param name="elem_size">Size of an individual blob in the block.</param>
/// <param name="block_size">The number of blobs that a block can hold.</param>
Pool::Pool( size_t const& elem_size, size_t const& block_size ) : elem_size_ { elem_size }, block_size_ { block_size } {
  cout << "Initializing a pool with element size " << elem_size_ << " and block size " << block_size_ << endl;
}

/// <summary>
/// Finalizes an instance of the <see cref="Pool"/> class.
/// </summary>
Pool::~Pool() {
  cout << "Deleting " << size_ << " blocks." << endl;

  // delete the blocks
  for ( size_t i {}; i < size_; ++i ) { delete [] pool_list_[i]; }

  // delete the pool
  delete [] pool_list_;
}

/// <summary>
/// Allocates a location to be used.
/// </summary>
/// <returns>A pointer to the memory space that should be used.</returns>
void* Pool::allocate() {
  if ( free_list_ == nullptr )
    grow ();

  // save a copy of free_list_
  auto const retVal = free_list_;

  // report which cell was allocated
  cout << "Cell allocated at " << format_address ( retVal ) << endl;

  // move free_list_ to the next spot to the right   
  assert ( free_list_ != nullptr );
  free_list_ = *reinterpret_cast<char**> ( free_list_ );

  ++live_cells_;
  if ( free_cells_ > 0 ) --free_cells_;

  // provide the location of where free_list_ used to reside
  return retVal;
}

/// <summary>
/// Deallocates the specified p.
/// </summary>
/// <param name="p">The pointer that should be freed up.</param>
void Pool::deallocate( void* p ) {
  assert ( p != nullptr );

  cout << "Cell deallocated at " << format_address ( p ) << endl;

  new ( p ) char* { free_list_ };

  free_list_ = reinterpret_cast<char*> ( p );

  if ( live_cells_ > 0 ) --live_cells_;
  ++free_cells_;
}

/// <summary>
/// Profiles this instance.
/// </summary>
void Pool::profile() const {
  assert ( live_cells_ >= 0 );
  assert ( free_cells_ >= 0 );

  // tell the user how many live and free cells exist
  cout << endl << "Live Cells: " << live_cells_ << ", Free Cells: " << free_cells_ << endl;

  // walk the free_list_ chain and show each address
  cout << "Free list:" << endl;

  auto iterator = free_list_;
  while ( iterator != nullptr ) {
    cout << format_address ( iterator ) << endl;
    iterator = *reinterpret_cast<char**> ( iterator );
  }
  cout << endl;
}

/// <summary>
/// Formats the pointer address for output.
/// </summary>
/// <param name="p">The pointer which will have its address displayed.</param>
/// <returns>A string representing the address of the pointer.</returns>
string Pool::format_address( void* p ) {
  stringstream ss;
  ss << "0x" << hex << p;
  return ss.str ();
}

/// <summary>
/// Grows the pool.
/// </summary>
void Pool::grow() {
  cout << "Expanding pool..." << endl;

  auto const new_size = size_ + 1;

  // create a new pool with size + 1 compared to the current pool
  auto const new_pool = new char* [new_size];

  // don't copy if the pool is empty, just create it
  if ( size_ > 0 ) {
    std::copy ( pool_list_, pool_list_ + size_, new_pool );

    // delete the old pool
    delete [] pool_list_;
  }

  // assign the new pool to our pool data member
  pool_list_ = new_pool;

  // update the pool size now that we are past the volatile stages of the grow method.
  size_ = new_size;

  auto const block = pool_list_[size_ - 1] = new char [elem_size_ * block_size_];
  link ( block );

  free_list_ = block;
}

/// <summary>
/// Divides the block into blob sized chunks and links them together.
/// </summary>
/// <param name="p">A pointer to the block of memory that should be divided and linked.</param>
void Pool::link( char* p ) {
  // report which address the linking will begin from
  cout << "Linking cells starting at " << format_address ( p ) << endl;

  // break the block into blobs and assign each blob the address of the next blob
  for ( size_t i {}; i < block_size_ - 1; ++i ) {
    new ( p ) char* { p + elem_size_ };
    p += elem_size_;
  }

  // attach a nullptr to the end of the block
  new ( p ) char* { nullptr };

  free_cells_ += block_size_;
}
