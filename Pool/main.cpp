#ifdef NDEBUG
#undef NDEBUG
#endif

#include <iostream>
#include <string>
#include "MyObject.h"
using namespace std;


int main() {
    MyObject::Profile();
    // Create an array of MyObject heap objects
    const int MAXOBJS{10};
    MyObject* objs[MAXOBJS];
    for (int i{0}; i < MAXOBJS; ++i)
        objs[i] = MyObject::Create(i, "\"" + to_string(i) + "\"");
    cout << "Object 5 == " << *objs[5] << endl;
    delete objs[5];
    objs[5] = nullptr;
    MyObject::Profile();

    cout << "Creating another object:\n";
    MyObject* anotherObject = MyObject::Create(100, "anotherObject");
    cout << "anotherObject == " << *anotherObject << endl;

    cout << "Creating yet another object:\n";
    MyObject* yetAnotherObject = MyObject::Create(120, "yetAnotherObject");
    cout << "yetAnotherObject == " << *yetAnotherObject << endl;

    // Delete everything
    MyObject::Profile();
    delete anotherObject;
    delete yetAnotherObject;
    for (size_t i{0}; i < MAXOBJS; ++i)
        delete objs[i];
    MyObject::Profile();
}
