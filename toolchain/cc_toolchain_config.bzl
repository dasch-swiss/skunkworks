
load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "action_config",
    "artifact_name_pattern",
    "env_entry",
    "env_set",
    "feature",
    "feature_set",
    "flag_group",
    "flag_set",
    "make_variable",
    "tool",
    "tool_path",
    "variable_with_value",
    "with_feature_set",
)
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

all_link_actions = [
   ACTION_NAMES.cpp_link_executable,
   ACTION_NAMES.cpp_link_dynamic_library,
   ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

def _impl(ctx):

    if (ctx.attr.cpu == "darwin"):
        toolchain_identifier = "clang-darwin"
    elif (ctx.attr.cpu == "k8"):
        toolchain_identifier = "clang-linux"
    else:
        fail("Unreachable")

    if (ctx.attr.cpu == "k8"):
        host_system_name = "x86_64"
    elif (ctx.attr.cpu == "darwin"):
        host_system_name = "x86_64-apple-macosx"
    else:
        fail("Unreachable")

    if (ctx.attr.cpu == "darwin"):
        target_system_name = "x86_64-apple-macosx"
    elif (ctx.attr.cpu == "k8"):
        target_system_name = "x86_64-unknown-linux-gnu"
    else:
        fail("Unreachable")

    if (ctx.attr.cpu == "darwin"):
        target_cpu = "darwin"
    elif (ctx.attr.cpu == "k8"):
        target_cpu = "k8"
    else:
        fail("Unreachable")

    if (ctx.attr.cpu == "k8"):
        target_libc = "glibc_unknown"
    elif (ctx.attr.cpu == "darwin"):
        target_libc = "macosx"
    else:
        fail("Unreachable")

    if (ctx.attr.cpu == "darwin" or
        ctx.attr.cpu == "k8"):
        compiler = "clang"
    else:
        fail("Unreachable")

    if (ctx.attr.cpu == "k8"):
        abi_version = "clang"
    elif (ctx.attr.cpu == "darwin"):
        abi_version = "darwin_x86_64"
    else:
        fail("Unreachable")

    if (ctx.attr.cpu == "darwin"):
        abi_libc_version = "darwin_x86_64"
    elif (ctx.attr.cpu == "k8"):
        abi_libc_version = "glibc_unknown"
    else:
        fail("Unreachable")

    cc_target_os = None

    if (ctx.attr.cpu == "darwin" or
        ctx.attr.cpu == "k8"):
        builtin_sysroot = "%{sysroot_path}"
    else:
        fail("Unreachable")

    all_compile_actions = [
        ACTION_NAMES.c_compile,
        ACTION_NAMES.cpp_compile,
        ACTION_NAMES.linkstamp_compile,
        ACTION_NAMES.assemble,
        ACTION_NAMES.preprocess_assemble,
        ACTION_NAMES.cpp_header_parsing,
        ACTION_NAMES.cpp_module_compile,
        ACTION_NAMES.cpp_module_codegen,
        ACTION_NAMES.clif_match,
        ACTION_NAMES.lto_backend,
    ]

    all_cpp_compile_actions = [
        ACTION_NAMES.cpp_compile,
        ACTION_NAMES.linkstamp_compile,
        ACTION_NAMES.cpp_header_parsing,
        ACTION_NAMES.cpp_module_compile,
        ACTION_NAMES.cpp_module_codegen,
        ACTION_NAMES.clif_match,
    ]

    preprocessor_compile_actions = [
        ACTION_NAMES.c_compile,
        ACTION_NAMES.cpp_compile,
        ACTION_NAMES.linkstamp_compile,
        ACTION_NAMES.preprocess_assemble,
        ACTION_NAMES.cpp_header_parsing,
        ACTION_NAMES.cpp_module_compile,
        ACTION_NAMES.clif_match,
    ]

    codegen_compile_actions = [
        ACTION_NAMES.c_compile,
        ACTION_NAMES.cpp_compile,
        ACTION_NAMES.linkstamp_compile,
        ACTION_NAMES.assemble,
        ACTION_NAMES.preprocess_assemble,
        ACTION_NAMES.cpp_module_codegen,
        ACTION_NAMES.lto_backend,
    ]

    all_link_actions = [
        ACTION_NAMES.cpp_link_executable,
        ACTION_NAMES.cpp_link_dynamic_library,
        ACTION_NAMES.cpp_link_nodeps_dynamic_library,
    ]

    action_configs = []

    if ctx.attr.cpu == "k8":
        linker_flags = [
            # Use the lld linker.
            "-fuse-ld=lld",
            # The linker has no way of knowing if there are C++ objects; so we always link C++ libraries.
            "-Lexternal/FIXME/lib", # FIXME: fix path
            "-l:libc++.a",
            "-l:libc++abi.a",
            "-l:libunwind.a",
            # Compiler runtime features.
            "-rtlib=compiler-rt",
            # To support libunwind.
            "-lpthread",
            "-ldl",
            # Other linker flags.
            "-Wl,--build-id=md5",
            "-Wl,--hash-style=gnu",
            "-Wl,-z,relro,-z,now",
        ]
    elif ctx.attr.cpu == "darwin":
        linker_flags = [
            # Difficult to guess options to statically link C++ libraries with the macOS linker.
            "-lc++",
            "-lc++abi",
            "-headerpad_max_install_names",
            "-undefined",
            "dynamic_lookup",
        ]
    else:
        fail("Unreachable")

    opt_feature = feature(name = "opt")
    fastbuild_feature = feature(name = "fastbuild")
    dbg_feature = feature(name = "dbg")

    random_seed_feature = feature(name = "random_seed", enabled = True)
    supports_pic_feature = feature(name = "supports_pic", enabled = True)
    supports_dynamic_linker_feature = feature(name = "supports_dynamic_linker", enabled = True)

    unfiltered_compile_flags_feature = feature(
        name = "unfiltered_compile_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = all_compile_actions,
                flag_groups = [
                    flag_group(
                        flags = [
                            # Do not resolve our smylinked resource prefixes to real paths.
                            "-no-canonical-prefixes",
                            # Reproducibility
                            "-Wno-builtin-macro-redefined",
                            "-D__DATE__=\"redacted\"",
                            "-D__TIMESTAMP__=\"redacted\"",
                            "-D__TIME__=\"redacted\"",
                            "-fdebug-prefix-map=external/FIXME=debug_external/FIXME", # FIXME: fix path
                        ],
                    ),
                ],
            ),
        ],
    )

    default_link_flags_feature = feature(
        name = "default_link_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = all_link_actions,
                flag_groups = [
                    flag_group(
                        flags = [
                            "-lm",
                            "-no-canonical-prefixes",
                        ] + linker_flags,
                    ),
                ],
            ),
        ] + ([
            flag_set(
                actions = all_link_actions,
                flag_groups = [flag_group(flags = ["-Wl,--gc-sections"])],
                with_features = [with_feature_set(features = ["opt"])],
            ),
        ] if ctx.attr.cpu == "k8" else []),
    )

    default_compile_flags_feature = feature(
        name = "default_compile_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = all_compile_actions,
                flag_groups = [
                    flag_group(
                        flags = [
                            # Security
                            "-U_FORTIFY_SOURCE",  # https://github.com/google/sanitizers/issues/247
                            "-fstack-protector",
                            "-fno-omit-frame-pointer",
                            # Diagnostics
                            "-fcolor-diagnostics",
                            "-Wall",
                            "-Wthread-safety",
                            "-Wself-assign",
                        ],
                    ),
                ],
            ),
            flag_set(
                actions = all_compile_actions,
                flag_groups = [flag_group(flags = ["-g", "-fstandalone-debug"])],
                with_features = [with_feature_set(features = ["dbg"])],
            ),
            flag_set(
                actions = all_compile_actions,
                flag_groups = [
                    flag_group(
                        flags = [
                            "-g0",
                            "-O2",
                            "-D_FORTIFY_SOURCE=1",
                            "-DNDEBUG",
                            "-ffunction-sections",
                            "-fdata-sections",
                        ],
                    ),
                ],
                with_features = [with_feature_set(features = ["opt"])],
            ),
            flag_set(
                actions = all_cpp_compile_actions,
                flag_groups = [flag_group(flags = ["-std=c++17", "-stdlib=libc++"])],
            ),
        ],
    )

    objcopy_embed_flags_feature = feature(
        name = "objcopy_embed_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = ["objcopy_embed_data"],
                flag_groups = [flag_group(flags = ["-I", "binary"])],
            ),
        ],
    )

    user_compile_flags_feature = feature(
        name = "user_compile_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = all_compile_actions,
                flag_groups = [
                    flag_group(
                        expand_if_available = "user_compile_flags",
                        flags = ["%{user_compile_flags}"],
                        iterate_over = "user_compile_flags",
                    ),
                ],
            ),
        ],
    )

    sysroot_feature = feature(
        name = "sysroot",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = all_compile_actions + all_link_actions,
                flag_groups = [
                    flag_group(
                        expand_if_available = "sysroot",
                        flags = ["--sysroot=%{sysroot}"],
                    ),
                ],
            ),
        ],
    )

    coverage_feature = feature(
        name = "coverage",
        flag_sets = [
            flag_set(
                actions = all_compile_actions,
                flag_groups = [
                    flag_group(
                        flags = ["-fprofile-instr-generate", "-fcoverage-mapping"],
                    ),
                ],
            ),
            flag_set(
                actions = all_link_actions,
                flag_groups = [flag_group(flags = ["-fprofile-instr-generate"])],
            ),
        ],
        provides = ["profile"],
    )

    framework_paths_feature = feature(
        name = "framework_paths",
        flag_sets = [
            flag_set(
                actions = [
                    ACTION_NAMES.objc_compile,
                    ACTION_NAMES.objcpp_compile,
                    "objc-executable",
                    "objc++-executable",
                ],
                flag_groups = [
                    flag_group(
                        flags = ["-F%{framework_paths}"],
                        iterate_over = "framework_paths",
                    ),
                ],
            ),
        ],
    )

    include_paths_feature = feature(
        name = "include_paths",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = preprocessor_compile_actions,
                flag_groups = [
                    flag_group(
                        flags = ["/I%{quote_include_paths}"],
                        iterate_over = "quote_include_paths",
                    ),
                    flag_group(
                        flags = ["/I%{include_paths}"],
                        iterate_over = "include_paths",
                    ),
                    flag_group(
                        flags = ["/I%{system_include_paths}"],
                        iterate_over = "system_include_paths",
                    ),
                ],
            ),
        ],
    )

    dependency_file_feature = feature(
        name = "dependency_file",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = [
                    ACTION_NAMES.assemble,
                    ACTION_NAMES.preprocess_assemble,
                    ACTION_NAMES.c_compile,
                    ACTION_NAMES.cpp_compile,
                    ACTION_NAMES.cpp_module_compile,
                    ACTION_NAMES.cpp_header_parsing,
                ],
                flag_groups = [
                    flag_group(
                        expand_if_available = "dependency_file",
                        flags = ["/DEPENDENCY_FILE", "%{dependency_file}"],
                    ),
                ],
            ),
        ],
    )

    compiler_input_flags_feature = feature(
        name = "compiler_input_flags",
        flag_sets = [
            flag_set(
                actions = [
                    ACTION_NAMES.assemble,
                    ACTION_NAMES.preprocess_assemble,
                    ACTION_NAMES.c_compile,
                    ACTION_NAMES.cpp_compile,
                    ACTION_NAMES.cpp_module_compile,
                    ACTION_NAMES.cpp_header_parsing,
                    ACTION_NAMES.cpp_module_codegen,
                ],
                flag_groups = [
                    flag_group(
                        expand_if_available = "source_file",
                        flags = ["/c", "%{source_file}"],
                    ),
                ],
            ),
        ],
    )

    compiler_output_flags_feature = feature(
        name = "compiler_output_flags",
        flag_sets = [
            flag_set(
                actions = [ACTION_NAMES.assemble],
                flag_groups = [
                    flag_group(
                        expand_if_available = "output_file",
                        expand_if_not_available = "output_assembly_file",
                        flags = ["/Fo%{output_file}", "/Zi"],
                    ),
                ],
            ),
            flag_set(
                actions = [
                    ACTION_NAMES.preprocess_assemble,
                    ACTION_NAMES.c_compile,
                    ACTION_NAMES.cpp_compile,
                    ACTION_NAMES.cpp_header_parsing,
                    ACTION_NAMES.cpp_module_compile,
                    ACTION_NAMES.cpp_module_codegen,
                ],
                flag_groups = [
                    flag_group(
                        expand_if_available = "output_file",
                        expand_if_not_available = "output_assembly_file",
                        flags = ["/Fo%{output_file}"],
                    ),
                    flag_group(
                        expand_if_available = "output_file",
                        flags = ["/Fa%{output_file}"],
                    ),
                    flag_group(
                        expand_if_available = "output_file",
                        flags = ["/P", "/Fi%{output_file}"],
                    ),
                ],
            ),
        ],
    )

    features = [
        opt_feature,
        fastbuild_feature,
        dbg_feature,
        random_seed_feature,
        supports_pic_feature,
        supports_dynamic_linker_feature,
        unfiltered_compile_flags_feature,
        default_link_flags_feature,
        default_compile_flags_feature,
        objcopy_embed_flags_feature,
        user_compile_flags_feature,
        sysroot_feature,
        coverage_feature,
        # Windows only features.
        # input_paths_feature
        # dependency_file_feature
        # compiler_input_flags_feature
        # compiler_output_flags_feature
    ]
    if (ctx.attr.cpu == "darwin"):
        features.extend([framework_paths_feature])

    cxx_builtin_include_directories = [
        "external/FIXME/include/c++/v1",
        "external/FIXME/lib/clang/11.0.0/include",
        "external/FIXME/lib64/clang/11.0.0/include",
    ]
    if (ctx.attr.cpu == "k8"):
        cxx_builtin_include_directories += [
            "%{sysroot_prefix}/include",
            "%{sysroot_prefix}/usr/include",
            "%{sysroot_prefix}/usr/local/include",
        ] + [
            # FIXME: %{k8_additional_cxx_builtin_include_directories}
        ]
    elif (ctx.attr.cpu == "darwin"):
        cxx_builtin_include_directories += [
            "%{sysroot_prefix}/usr/include",
            "%{sysroot_prefix}/System/Library/Frameworks",
            "/Library/Frameworks",
        ] + [
            # FIXME: %{darwin_additional_cxx_builtin_include_directories}
        ]
    else:
        fail("Unreachable")

    artifact_name_patterns = []

    if (ctx.attr.cpu == "darwin"):
        make_variables = [
            make_variable(
                name = "STACK_FRAME_UNLIMITED",
                value = "-Wframe-larger-than=100000000 -Wno-vla",
            ),
        ]
    elif (ctx.attr.cpu == "k8"):
        make_variables = []
    else:
        fail("Unreachable")

    tool_paths = [
        tool_path(
            name = "gcc",
            path = "/usr/bin/clang",
        ),
        tool_path(
            name = "ld",
            path = "/usr/bin/ld",
        ),
        tool_path(
            name = "ar",
            path = "/bin/false",
        ),
        tool_path(
            name = "cpp",
            path = "/bin/false",
        ),
        tool_path(
            name = "gcov",
            path = "/bin/false",
        ),
        tool_path(
            name = "nm",
            path = "/bin/false",
        ),
        tool_path(
            name = "objdump",
            path = "/bin/false",
        ),
        tool_path(
            name = "strip",
            path = "/bin/false",
        ),
    ]

    features = [
        feature(
            name = "default_linker_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_link_actions,
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-lstdc++",
                            ],
                        ),
                    ]),
                ),
            ],
        ),
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        cxx_builtin_include_directories = [
            "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include",
            "/usr/include",
        ],
        toolchain_identifier = "local",
        host_system_name = "local",
        target_system_name = "local",
        target_cpu = "k8",
        target_libc = "unknown",
        compiler = "clang",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,
    )

cc_toolchain_config = rule(
    attrs = {
        "cpu": attr.string(
            mandatory = True,
            values = [
                "darwin",
                "k8",
            ],
        ),
    },
    executable = True,
    provides = [CcToolchainConfigInfo],
    implementation = _impl,
)