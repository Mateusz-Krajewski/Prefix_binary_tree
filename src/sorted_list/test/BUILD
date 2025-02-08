

cc_test(
    name = "check_ip_test",
    srcs = [
        "test_check_ip.cc",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//src/nr2:nr_2_model",
    ],
)

cc_test(
    name = "ref_test",
    srcs = [
        "reference_test.cc",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//src/nr2:nr_2_model",
    ],
)

cc_test(
    name = "nr2_benchmarks",
    srcs = ["benchmark.cc"],
    visibility = ["//visibility:public"],
    deps = [
         "//src/sorted_list:nr_2_model",
        "@com_google_benchmark//:benchmark_main",
    ],
)