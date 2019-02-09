#include "weblog-encoder.h"
#include "weblog-decoder.h"
#include "weblog-reader.h"

int main() {
  weblog::Encoder enc;
  enc.encode("~/shared_vm/access_log_Aug95", "~/shared_vm/access_log_Aug95.output");
  //enc.encode("~/shared_vm/access_log_Jul95", "~/shared_vm/access_log_Jul95.output");
}
