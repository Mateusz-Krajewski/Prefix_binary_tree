
cc_test(
    name = "ref_test",
    srcs = [
        "nr3_test.cc",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//src/binary_tree:nr_3_model",
    ],
)

cc_test(
    name = "nr3_benchmarks",
    srcs = ["benchmark.cc"],
    visibility = ["//visibility:public"],
    deps = [
         "//src/binary_tree:nr_3_model",
        "@com_google_benchmark//:benchmark_main",
    ],
)