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
    NULL_TYPE
  };

  virtual std::string write_out(int register) const=0;
  virtual std::string read_in(int register) const=0;
  virtual Basic type() const=0;
  virtual int word_size() const;
};

struct Integer : Type {
  virtual std::string write_out(int) const;
  virtual std::string read_in(int register) const;
  virtual Basic type() const;
};

struct Character : Type {
  virtual std::string write_out(int) const;
  virtual std::string read_in(int register) const;
  virtual Basic type() const;
};

struct StringConstant : Type {
  virtual std::string write_out(int) const;
  virtual std::string read_in(int register) const;
  virtual Basic type() const;
};

struct Boolean : Type {
  virtual std::string write_out(int) const;
  virtual std::string read_in(int register) const;
  virtual Basic type() const;
};

struct Null : Type {
  virtual std::string write_out(int) const;
  virtual std::string read_in(int register) const;
  virtual Basic type() const;
};

#endif //CPSL_TYPE_HPP
