/**************************************************

Diamant --> Dans PrinterScanner, Scanner et Printer
partagent le même id

class Device{
  int getId(){return id;}
private:
  int id;
};

class Printer: public Device{
  void Print(){}
};

class Scanner: public Device{

};

class PrinterScanner: public Printer, public Scanner{
  void Print(){}
};

**************************************************/


/**************************************************

By Default case ---> Diamant where in Transmetter :
Receiver and Sender DOESN'T HAVE THE SAME id

class Buffer{
  int getId(){return id;}
private:
  int id;
};

class Receiver: public Buffer{
  void Print(){}
};

class Sender: public Buffer{

};

class Transmetter: public Printer, public Scanner{
  void Print(){}
};

**************************************************/


///////////////////////////////////////////////////
//HOW
///////////////////////////////////////////////////
/**************************************************

class Printer: virtual public Device{} To have a id

**************************************************/
