#include "Pool.h"
Pool::Pool ( size_t const& elem_size, size_t const& block_size ) : elem_size_ { elem_size }, block_size_ { block_size} {}

Pool::~Pool() {
  // clear up all used memory back to the heap
}

auto Pool::allocate() -> void*  {
  // allocate blocks of memory
  return nullptr;
}

auto Pool::deallocate( void* ) -> void { 
  // free up the allocated blocks of memory 
}
auto Pool::profile() -> void {
  // for each node in the pool, output it's address and then go to it's neighbor and repeat until the end of the block
}

auto Pool::grow () -> void {
  // grow the pool linked list

  // create a new pool with size + 1 compared to the current pool
  // move the contents of the new pool over to the new pool
  // delete the old pool
  // assign the new pool to our pool data member
}

auto Pool::link ( char* ) -> void {
  // break the block into chunks that are linked together

  // 
}
