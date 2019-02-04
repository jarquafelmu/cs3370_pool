// Project: Pool
// Name: Sam Terrazas
// File: MyObject.cpp
// Created: 01/28/2019 3:04 PM
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

#include "MyObject.h"
#include "Pool.h"

#include <ostream>
#include <string>

using namespace std;

/// <summary>
/// Initializes the Pool_ member with the size of this class.
/// </summary>
Pool MyObject::Pool_ {
  sizeof ( MyObject )
};

/// <summary>
/// Initializes a new instance of the <see cref="MyObject"/> class.
/// </summary>
/// <param name="i">The id of the object.</param>
/// <param name="nm">The name of the object.</param>
MyObject::MyObject( int const& i, string nm ) : name_ { std::move ( nm ) } { id_ = i; }

/// <summary>
/// Creates the specified identifier.
/// </summary>
/// <param name="id">The identifier of the object.</param>
/// <param name="name">The name of the object.</param>
/// <returns>A pointer to a new MyObject object.</returns>
MyObject* MyObject::create( const int& id, const string& name ) { return new MyObject ( id, name ); }

/// <summary>
/// Implements the operator new.
/// </summary>
/// <param name="size">The size.</param>
/// <returns>
/// The result of the operator.
/// </returns>
void* MyObject::operator new( size_t size ) { return Pool_.allocate (); }

/// <summary>
/// Implements the operator delete.
/// </summary>
/// <param name="p">The p.</param>
void MyObject::operator delete( void* p ) { Pool_.deallocate ( p ); }

/// <summary>
/// Profiles this instance.
/// </summary>
void MyObject::profile() { Pool_.profile (); }

/// <summary>
/// Operators the specified insertion operator.
/// </summary>
/// <param name="out">The out stream.</param>
/// <param name="my_object">MyObject object.</param>
/// <returns>An out stream reference.</returns>
ostream& operator<<( ostream& out, MyObject const& my_object ) {
  out << "{" << my_object.id_ << "," << my_object.name_ << "}";
  return out;
}
