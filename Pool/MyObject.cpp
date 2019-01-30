#include "MyObject.h"
#include "Pool.h"

#include <ostream>
#include <string>

using namespace std;

Pool MyObject::pool_ { 
  // provide pool with the size of the MyObject class  
  sizeof ( MyObject ) 
};

MyObject::MyObject ( int const& i, string nm ) : name_ { std::move ( nm ) } {
  // construct a new object of this class
  id_ = i;
}

MyObject* MyObject::create( const int& id, const string& name ) {
  // create a new object of this class
  return new MyObject ( id, name );
}

auto MyObject::operator new( size_t size ) -> void* {
  // calls pool's allocate
  return nullptr;
}
auto MyObject::operator delete( void* p ) -> void {
  // calls pool's deallocate
}

auto MyObject::profile() -> void {
  // call's pool's profile data member.
}

auto operator<<( ostream& out, MyObject const& my_object ) -> ostream& {
  // display's this object's data
  return out;
}
