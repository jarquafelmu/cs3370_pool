#include "Pool.h"
#include <algorithm>
#include <sstream>

using namespace std;

Pool::Pool ( size_t const& elem_size, size_t const& block_size ) : elem_size_ { elem_size }, block_size_ { block_size} {
  cout << "Initializing a pool with element size " << elem_size_ << " and block size " << block_size_ << endl;
  grow ();
}

Pool::~Pool() {
  // clear up all used memory back to the heap
}

void* Pool::allocate() {
  // allocate new space for our block
  if (free_list_ == nullptr)
    grow ();

  // save a copy of free_list_
  auto const retVal = free_list_;

  // report which cell was allocated
  cout << "Cell allocated at " << format_address ( retVal ) << endl;

  // move free_list_ to the next spot to the right   
  free_list_ = *reinterpret_cast<char**> (free_list_ );

  ++live_cells_;

  // provide the location of where free_list_ used to reside
  return retVal;
}

void Pool::deallocate( void* p ) { 
  // free up the allocated blocks of memory 

  // report which cell was deallocated
  
  cout << "Cell deallocated at " << format_address ( p ) << endl;
  
  new ( p ) char* { free_list_ };

  free_list_ = static_cast<char*> (p);

  --live_cells_;
  ++free_cells_;
}
auto Pool::profile() -> void {
  // for each node in the pool, output it's address and then go to it's neighbor and repeat until the end of the block

  // tell the user how many live and free cells exist
  // report the address of free_list_
  cout << endl << "Live Cells: " << live_cells_ << ", Free Cells: " << free_cells_ << endl;
  cout << "Free list:" << endl;
  if ( free_list_ != nullptr )
    cout << format_address ( free_list_ );
  cout << endl << endl;
}

auto Pool::format_address( void* p ) -> string  {
  stringstream ss;
  ss << "0x" << hex << p;
  return ss.str ();
}

void Pool::grow() {
  // grow the pool linked list
  cout << "Expanding pool..." << endl;

  auto const new_size = size_ + 1;

  // Create a new pool with size + 1 compared to the current pool
  auto const temp = new char* [new_size];

  // don't copy if the pool is empty, just Create it
  if ( size_ > 0 ) {
    std::copy ( pool_list_, pool_list_ + size_, temp );
  
    // delete the old pool
    delete [] pool_list_;
  }
  
  // assign the new pool to our pool data member
  pool_list_ = temp;

  // update the pool size now that we are past the volatile stages of the grow method.
  size_ = new_size;

  auto const block = pool_list_ [size_ - 1] = new char [elem_size_ * block_size_];
  link ( block );

  free_list_ = block;
}

void Pool::link( char* p ) const {
  // break the block into chunks that are linked together
  
  // report which address the linking will begin from
  cout << "Linking cells starting at " << format_address ( p ) << endl;

  for ( size_t i = 0; i < block_size_ - 1; ++i ) {
    new ( p ) char* { p + elem_size_ };
    p += elem_size_;
  }

  new ( p ) char* { nullptr };
}

