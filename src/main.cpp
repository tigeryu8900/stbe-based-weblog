#include <gflags/gflags.h>
#include "weblog-encoder.h"
#include "weblog-decoder.h"
#include "weblog-reader.h"
/*
DEFINE_string(input, "", "File to encode");
DEFINE_string(output, "output.stbe", "Output file (will create if file does not exist)");
DEFINE_int32(block_size, 4096, "Block size in KB (default: 4096)");
*/
int main(int argc, char* argv[]) {
  /*
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  if (FLAGS_input == "") {
    std::cout << "Error: input flag is missing or has an empty parameter." << std::endl;
  }
  weblog::Encoder enc;
  enc.encode(FLAGS_input, FLAGS_output);
  */weblog::Encoder enc;
  enc.encode("./test_file", "./test_file.stbe");
  weblog::Decoder dec;
  dec.decode("./test_file.stbe", "./test_file_new");
}
