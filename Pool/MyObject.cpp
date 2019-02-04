#include "MyObject.h"
#include "Pool.h"

#include <ostream>
#include <string>

using namespace std;

Pool MyObject::Pool_ { 
  // provide pool with the size of the MyObject class  
  sizeof ( MyObject ) 
};

MyObject::MyObject ( int const& i, string nm ) : name_ { std::move ( nm ) } {
  // construct a new object of this class
  id_ = i;
}

MyObject* MyObject::Create( const int& id, const string& name ) {
  // Create a new object of this class
  return new MyObject ( id, name );
}

auto MyObject::operator new( size_t size ) -> void* {
  // calls pool's allocate
  return Pool_.allocate ();
}
auto MyObject::operator delete( void* p ) -> void {
  // calls pool's deallocate
  Pool_.deallocate ( p );
}

auto MyObject::Profile() -> void {
  // call's pool's Profile data member.
 Pool_.profile ();
}

auto operator<<( ostream& out, MyObject const& my_object ) -> ostream& {
  // display's this object's data
  out << "{" << my_object.id_ << "," << my_object.name_ << "}";
  return out;
}
