#include <iostream>
using namespace std;

/***********************************
Non Virtual

class B1{
public:
  int b;
  int get(){return b;}
};

class B2{
public:
  int b;
  int get(){return b;}
};

class D: public B1, public B2{
  int get(){ return B1::get() + B2::get(); } // Masquage
};

int main(){
  D d;

  Due to same name in B1 and B2

  d.B1::b = 1;
  d.B2::b = 2;
  cout << d.B1::get() << endl;
  cout << d.B2::get();
  return 0;
}

***********************************/

/***********************************
Virtual

class B1{
public:
  int b;
  virtual int get(){return b;}
};

class B2{
public:
  int b;
  virtual int get(){return b;}
};

class D: public B1, public B2{
  int get(){ return B1::get() + B2::get(); } // Redefinition
};



int main(){
  D d;

  Due to same name in B1 and B2

  d.B1::b = 1;
  d.B2::b = 2;
  cout << d.B1::get() << endl;
  cout << d.B2::get();
  return 0;
}


***********************************/
