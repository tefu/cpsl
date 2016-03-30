#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <vector>

std::stringstream sout;
extern int yyparse();
extern int yylineno;
extern FILE* yyin;

bool file_exists(std::string fileName)
{
  std::ifstream infile(fileName);
  return infile.good();
}

int main(int argc, const char** argv)
{
  std::vector<std::string> arguments;
  std::string input_file = "in.cpsl";
  std::string output_file = "out.asm";
  for(int i = 0; i < argc; i++)
  {
    arguments.push_back(std::string(argv[i]));
  }

  if (arguments.size() > 3)
  {
    std::cout << "Usage: ./cpsl [CPSL input file] [ASM output file]" << std::endl;
    return EXIT_FAILURE;
  }
  else if (arguments.size() == 3)
  {
    input_file = arguments[1];
    output_file = arguments[2];
  }
  else if (arguments.size() == 2)
  {
    input_file = arguments[1];
  }

  if (!file_exists(input_file))
  {
    std::cout << "Error: " << input_file << " does not exist!" << std::endl;
    return EXIT_FAILURE;
  }

  yyin = fopen(input_file.c_str(), "r");
  try
  {
    yyparse();
    fclose(yyin);
  }
  catch(std::runtime_error e)
  {
    std::cout << "Did not compile! " << e.what() << " at line " << yylineno << std::endl;
    fclose(yyin);
    return EXIT_FAILURE;
  }

  std::ofstream outfile;
  outfile.open(output_file);
  if (outfile.is_open())
  {
    outfile << sout.str();
  }
  outfile.close();
}
