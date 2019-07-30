#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
//#include <gperftools/malloc_extension.h>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

#define SPDLOG_NO_DATETIME
#define SPDLOG_EOL ""
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

using std::end;
using std::map;
using std::shared_ptr;
using std::stoi;
using std::string;
using std::vector;

class Spectrum {
public:
  Spectrum(size_t nbins) {
    m_x.resize(nbins, 1.0);
    m_y.resize(nbins, 1.0);
    m_e.resize(nbins, 1.0);
  }

private:
  std::vector<double> m_x, m_y, m_e;
};

class Workspace {
public:
  using VectorSpectra = vector<Spectrum>;

  Workspace(size_t nspectra, size_t nbins) {
    m_spectra.resize(nspectra, Spectrum(nbins));
  }

private:
  VectorSpectra m_spectra;
};

using WorkspaceSptr = std::shared_ptr<Workspace>;

template <typename DataType> class DataService {
public:
  using Key = string;
  using Value = DataType;

public:
  inline size_t size() const { return m_index.size(); }
  void add(const string &name, const DataType &workspace) {
    m_index.insert(end(m_index), std::make_pair(name, workspace));
  }

  void clear() { m_index.clear(); }

private:
  unorderremap<Key, Value> m_index;
};
using BasicADS = DataService<WorkspaceSptr>;

constexpr int DEFAULT_NITERATIONS = 10;
auto CONSOLE_LOGGER = spdlog::stdout_color_mt("console");

struct Arguments {
  unsigned niterations = DEFAULT_NITERATIONS;
};

constexpr double MiB = 1024 * 1024;
double PAGESIZE_MIB = static_cast<double>(sysconf(_SC_PAGE_SIZE)) / MiB;

double display_memory_usage() {
  std::ifstream fs("/proc/self/statm");
  std::string statm_content;
  std::getline(fs, statm_content);
  int _, resident, shared;
  std::istringstream is(statm_content);
  is >> _ >> resident >> shared;
  const double mem_usage = (resident - shared) * PAGESIZE_MIB;
  CONSOLE_LOGGER->info("Current process memory usage: {} MiB\n", mem_usage);
  return mem_usage;
}

// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------

Arguments parse_args(int argc, char *argv[]) {
  Arguments args;
  if (argc == 1) {
    args.niterations = static_cast<unsigned>(DEFAULT_NITERATIONS);
  } else if (argc == 2) {
    args.niterations = stoi(argv[1]); // NOLINT
  } else {
    CONSOLE_LOGGER->error("Usage: main [niterations]\n");
    exit(1);
  }
  return args;
}

int main(int argc, char *argv[]) {
  //mallopt(M_MMAP_THRESHOLD, 1);
  auto args = parse_args(argc, argv);
  spdlog::set_pattern("[%^%l%$] %v");
  auto mem_start = display_memory_usage();

  BasicADS ads;
  CONSOLE_LOGGER->info("Starting loop with {} iterations\n", args.niterations);
  for(unsigned i = 0; i < args.niterations; ++i) {
    CONSOLE_LOGGER->info("Iteration: {}\r", i+1);
    const auto ws = WorkspaceSptr(new Workspace(100,1000)); // NOLINT
    const std::string name(fmt::format("ws-{}", i));
    ads.add(name, ws);
    //CONSOLE_LOGGER->info("Address: {}\n", (void*)(ws.get()));
  }
  CONSOLE_LOGGER->info("\n");
  CONSOLE_LOGGER->info("Finished loop\n");

  display_memory_usage();
  CONSOLE_LOGGER->info("Clearing ADS and waiting 5s\n");
  ads.clear();
  // MallocExtension::instance()->ReleaseFreeMemory();

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(5s);
  auto mem_end = display_memory_usage();

  CONSOLE_LOGGER->info("Memory diff: {} MiB\n", mem_end-mem_start);

  return 0;
}
