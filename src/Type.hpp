#ifndef CPSL_TYPE_HPP
#define CPSL_TYPE_HPP
#include <string>

struct Type {
  enum Basic
  {
    BOOL,
    STRING,
    INTEGER,
    CHAR,
    NONE
  };

  virtual std::string write_out(int register) const;
  virtual Basic type() const;
  virtual int word_size() const;
};

struct Integer : Type {
  virtual std::string write_out(int) const;
  virtual Basic type() const;
};

struct Character : Type {
  virtual std::string write_out(int) const;
  virtual Basic type() const;
};

struct StringConstant : Type {
  virtual std::string write_out(int) const;
  virtual Basic type() const;
};

struct Boolean : Type {
  virtual std::string write_out(int) const;
  virtual Basic type() const;
};

#endif //CPSL_TYPE_HPP
