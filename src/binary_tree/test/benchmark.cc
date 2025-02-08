#include <benchmark/benchmark.h>
#include "src/binary_tree/lib.h"

static void REF_BM_AddElement(benchmark::State& state) {
    for (auto _ : state) {
        for (unsigned int i = 0; i < state.range(0); ++i) {
            unsigned int base = 0x0A000000 + i;
            unsigned int mask = 0xFFFFFF00;
            add(base, mask);
        }
    }
}
BENCHMARK(REF_BM_AddElement)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Iterations(100);

static void BM_CheckFunction(benchmark::State& state) {
    for (auto _ : state) {
        for (unsigned int i = 0; i < state.range(0); ++i) {
            unsigned int base = 0x0A000000 + i * 256;
            unsigned int mask = 0xFFFFFF00;
            add(base, mask);
        }
        unsigned int test_ip = 0x0A000200;
        benchmark::DoNotOptimize(check(test_ip));
    }
}
BENCHMARK(BM_CheckFunction)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Iterations(100);

BENCHMARK_MAIN();