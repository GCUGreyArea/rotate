#include <benchmark/benchmark.h>
#include <assert.h>

#include <string>

#include <libData.h>

static void BM_BenchmarkData(benchmark::State &state)
{
    char key_arr[100][10];
    char val_arr[100][10];
    for(int i=0; i < 100; i++) {
        std::string key = "key" + std::to_string(i);
        std::string val = "value" + std::to_string(i);

        sprintf(key_arr[i],"%s",key.c_str());
        sprintf(val_arr[i],"%s",val.c_str());
    }

    // Perform setup here
    for (auto _ : state)
    {
        data_t *data = create_data(100);
        assert(data);

        for(int i=0; i < 100; i++) {
            data_err_t err = add_str_kv_value(data,key_arr[i],val_arr[i]);
            if(err != OK) {
                // abort();
            }
        }

        render(data);
        teardown(data);

    }
}


BENCHMARK(BM_BenchmarkData);

// Run the benchmark
BENCHMARK_MAIN();