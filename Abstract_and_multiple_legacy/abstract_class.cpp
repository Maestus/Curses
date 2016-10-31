// -*- coding: utf-8 -*-

#include <iostream>

using namespace std;

/******************************************************
B an abstract class ==> at least one virtual pur method

class B{
  virtual void g();
  virtual void f() = 0; // Méthode virtual pure
private:
  int a = 0;
};

void B::g(){}

******************************************************/

/****************************************************************************
Using B for a class D => Legacy of f() and g()
One way to not be abstract for D is to define f() which was virtual pur in B
If D define all method abstract of B then it's called a concret class

class D: public B{
  virtual void f(){}
};

****************************************************************************/

/////////////////////////////////////////////////////////////////////////////
//EXEMPLE
/////////////////////////////////////////////////////////////////////////////


// Fully abstract class for sequences of numbers viewed as iterators
class Sequence {
public:
  // Return current value
  virtual double operator*() = 0;
  // Prefix ++ operator: move to next value
  virtual Sequence& operator++() = 0;
};

// Sequences of the form u_n = map(n) for some function map
// Several calls to operator* (without call to operator++ in between)
// compute the same value several times.
// This can be optimized using CachedSequence.
class MapSequence : public Sequence {
public:
  // Return current value map(n)
  double operator*() { return map(n); }
  // Increment index n to move to next value
  Sequence& operator++() {  ++n; return *this; }
protected:
  // Virtual method to compute the current value from the index n
  virtual double map(int n) = 0;
private:
  int n = 0;			// Index
};

// Sequence of squares: 0, 1, 4, 9, 16, ...
// Sequence of cubes is left as a (very easy) exercice
class Squares : public MapSequence {
 protected:
  double map(int n) { return n*n; }
};

// Sequence of Fibonacci numbers
// F_0 = F_1 = 1
// F_{n+2} = F_{n+1} + F_n
class Fibonacci : public Sequence {
public:
  // Return F_n
  double operator*() { return j; }
  // Update F_{n-1} and F_n
  // A temporary variable is needed to make the parallel assignment
  // (i,j) = (j,i+j)
  Fibonacci& operator++() { long int t = i+j; i = j; j = t; return *this; }
private:
  long int i = 0;		// F_{n-1}
  long int j = 1;		// F_n
};

// Sequence of factorial numbers: 1, 2, 3, 6, 120, 720, ...
class Factorial : public Sequence {
public:
  // Return n!
  double operator*() { return f; }
  // Update f and n
  Factorial& operator++() { f *= ++n; return *this; }
private:
  long int f = 1;		// 1 x 2 x ... x n
  long int n = 1;		// n
};

// Sequence made of the sum of values of another sequence
// The first value is always 0.
// From a_0, a_1, a_2, ...
// 0, a_0, a_0+a_1, a_0+a_+a_2, ...
class Sum : public Sequence {
public:
  // Construct from another sequence called the source.
  // This contructor overloads the copy constructor
  // which is still provided by the compiler.
  Sum(Sequence& s) : source(s) {}
  // Return current sum
  double operator*() { return sum; }
  // Add the current value of the source and move source to next value
  Sum& operator++() { sum += *source; ++source; return *this; }
private:
  Sequence& source;		// Source
  double sum = 0;		// Current sum
};

// Buffered sequence
// Several calls to the operator* of this class calls only once
// the operator* of its source.
class CachedSequence : public Sequence {
public:
  // Construct from another sequence called the source.
  // This contructor overloads the copy constructor
  // which is still provided by the compiler.
  CachedSequence(Sequence& s) : source(s) {}
  // Return current sum
  double operator*() {
    if (!uptodate) {
      val = *source;		// Current value
      uptodate = true;		// is up-to-date
    }
    return val;
  }
  // Move source to next value and mark value as not up-to-date
  CachedSequence& operator++() { ++source; uptodate = false; return *this; }
private:
  Sequence& source;		// Source
  double val;			// Cache for *source
  bool uptodate = false;	// true if val == *source
};



/////////////////////////////////////////////////////////////////////////////
//END
/////////////////////////////////////////////////////////////////////////////


int main(){
  /**********************************

  Fobidden uses of abstract class B

    B b;
    new B();
    new B[10];
    f(B b);
    B::f();
    attribute of type B;

  Authorized uses of abstract class B

    B *p;
    B &ref;

  ***********************************/
  /**********************************
  D allow to use

    D d;
    B *p = new D();
    D *q = new D();
    B &r = * new D();
    B *t = new D[10];
  ***********************************/
  ////////////////////////////////////
  //EXEMPLE MAIN
  ////////////////////////////////////

  Squares sq;			// Squares
  Sum sum(sq);			// Sum of squares
  // The cast is necessary to call the constructor Sum(Sequence&)
  // and not the copy constructor Sum(Sum&)
  Sum sumsum((Sequence&) sum);	// Sum of sum of squares

  for (int i = 0; i < 10; ++i) {
    cout << *sq << ' ' << *sum << ' ' << *sumsum << endl;
    ++sumsum;
  }

  ////////////////////////////////////
  //END
  ////////////////////////////////////
  return 0;
}
