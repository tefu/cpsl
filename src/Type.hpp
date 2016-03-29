#ifndef CPSL_TYPE_HPP
#define CPSL_TYPE_HPP
#include <string>

struct Expression;
struct Array;

struct Type {
  static std::string integer_type() { return "integer"; }
  static std::string boolean_type() { return "bool"; }
  static std::string string_type()  { return "string"; }
  static std::string char_type()    { return "char"; }
  static std::string null_type()    { return "null"; }
  static std::string array_type()   { return "array"; }

  static const int ADDRESS_SIZE = 4;
  virtual std::string write_out(int) const=0;
  virtual std::string read_in(int) const=0;
  virtual std::string type() const=0;
  virtual std::string assign_to(int, int, int, std::string);
  virtual std::string load_into(int, int, int, std::string);
  virtual int word_size() const;
  virtual bool operator==(const Type&);
  virtual bool equals(const Array&) const;
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

struct Array : Type {
  Array(int io, int s, Type* st)
    : index_offset(io), size(s),subtype(st) {}
  virtual std::string write_out(int) const;
  virtual std::string read_in(int register) const;
  virtual std::string type() const;
  virtual std::string assign_to(int, int, int, std::string);
  virtual std::string load_into(int, int, int, std::string);
  virtual int word_size() const;
  virtual bool equals(const Array&) const;
  bool operator==(const Type&);
  int index_offset;
  int size;
  Type* subtype;
};
#endif //CPSL_TYPE_HPP
