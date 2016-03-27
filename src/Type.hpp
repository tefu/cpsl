#ifndef CPSL_TYPE_HPP
#define CPSL_TYPE_HPP
#include <string>

struct Type {
  static std::string integer_type() { return "integer"; }
  static std::string boolean_type() { return "bool"; }
  static std::string string_type()  { return "string"; }
  static std::string char_type()    { return "char"; }
  static std::string null_type()    { return "null"; }

  static const int ADDRESS_SIZE = 4;
  virtual std::string write_out(int register) const=0;
  virtual std::string read_in(int register) const=0;
  virtual std::string type() const=0;
  virtual int word_size() const;
  bool operator==(const Type&);
};

struct Integer : Type {
  virtual std::string write_out(int) const;
  virtual std::string read_in(int register) const;
  virtual std::string type() const;
};

struct Character : Type {
  virtual std::string write_out(int) const;
  virtual std::string read_in(int register) const;
  virtual std::string type() const;
};

struct StringConstant : Type {
  virtual std::string write_out(int) const;
  virtual std::string read_in(int register) const;
  virtual std::string type() const;
};

struct Boolean : Type {
  virtual std::string write_out(int) const;
  virtual std::string read_in(int register) const;
  virtual std::string type() const;
};

struct Null : Type {
  virtual std::string write_out(int) const;
  virtual std::string read_in(int register) const;
  virtual std::string type() const;
};

#endif //CPSL_TYPE_HPP
