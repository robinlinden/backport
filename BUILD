load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "backport",
    hdrs = ["backport/source_location.hpp"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "backport_test",
    size = "small",
    srcs = ["backport/source_location_test.cpp"],
    deps = [":backport"],
)
