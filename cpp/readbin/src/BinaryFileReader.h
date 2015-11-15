#ifndef BINARYFILEREADER_H_
#define BINARYFILEREADER_H_
// -----------------------------------------------------------------------------
// Headers
// -----------------------------------------------------------------------------
#include <cstdio>
#include <memory>
#include <string>

/**
 * Takes a filename argument and allows for reading
 * arbitrary numbers of bytes from a file.
 *
 */
class BinaryFileReader final {
public:
  BinaryFileReader(std::string filename);
  ~BinaryFileReader();

private:
  FILE *m_descriptor;
};

#endif // BINARYFILEREADER_H_
