#include <iostream>
#include <fstream>

#include "splat.h"

int main(int argc, char * argv[]) {
  if (argc < 2) {
    std::cout << "Usage: splat <run script> <test program>" << std::endl;
    return 1;
  }

  std::ifstream testfile(argv[1]);
  return test(testfile);
}
