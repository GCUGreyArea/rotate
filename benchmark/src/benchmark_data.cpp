#include <benchmark/benchmark.h>
#include <string>

#include <libtest.h>

static void BM_BenchmarkTest(benchmark::State &state)
{
    // Perform setup here
    for (auto _ : state)
    {
}


BENCHMARK(BM_BenchmarkData);

// Run the benchmark
BENCHMARK_MAIN();