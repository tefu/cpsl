#ifndef CPSL_TYPE_HPP
#define CPSL_TYPE_HPP
#include <string>

struct Type {
  enum Basic
  {
    BOOL,
    STRING,
    INTEGER,
    CHAR
  };


  virtual std::string write_out(int register)=0;
  virtual Basic type()=0;
};

struct Integer : Type {
  std::string write_out(int);
  Basic type();
};

struct Character : Type {
  std::string write_out(int);
  Basic type();
};

struct StringConstant : Type {
  std::string write_out(int);
  Basic type();
};

struct Boolean : Type {
  std::string write_out(int);
  Basic type();
};

#endif //CPSL_TYPE_HPP
