#include <cassert>
#include <iostream>

using namespace std;

int main(int argc, char **) {
  if (argc != 2) {
    cerr << "Usage: readbin FILE\n";
    return 1;
  }
  assert(argc == 2);
}
