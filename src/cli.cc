#include <iostream>
#include <fstream>

#include "splat.h"

int main(int argc, char * argv[]) {
  if (argc < 3) {
    std::cout << "Usage: splat language_path testfile" << std::endl;
    return 1;
  }

  std::ifstream testfile(argv[2]);

  return test(argv[1], testfile);
}
