load("@rules_cc//cc:defs.bzl", "cc_binary")

# BUILD file for C++ project
cc_binary(
    name = "main",
    srcs = ["main.cc"],
    linkopts = ["-lpthread"],
    deps = [
        "//component:stack_trace",
        "//component:test",
    ],
)
