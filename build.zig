const std = @import("std");

const @"c src": []const []const u8 = &.{
    "src/xoshiro256.c",
    "src/split.c",
};
const @"c flags": []const []const u8 = &.{
    "-Wall",
    "-Wextra",
    "-pedantic",
};

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});

    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addSharedLibrary(.{
        .name = "xoshiro256",

        .target = target,
        .optimize = optimize,
    });
    lib.addIncludePath(.{ .path = "include" });

    lib.addCSourceFiles(.{
        .files = @"c src",
        .flags = @"c flags",
    });
    lib.linkLibC();

    const exe = b.addExecutable(.{
        .name = "xoshiro",
        .root_source_file = .{ .path = "src/main.zig" },
        .optimize = optimize,
        .target = target,
    });
    exe.linkLibC();
    exe.linkLibrary(lib);

    exe.addIncludePath(.{ .path = "include" });

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    const run_step = b.step("run", "Run the application.");
    run_step.dependOn(&run_cmd.step);

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    b.installArtifact(lib);
    const lib_unit_tests = b.addTest(.{
        .root_source_file = .{ .path = "src/root.zig" },
        .target = target,
        .optimize = optimize,
    });

    const run_lib_unit_tests = b.addRunArtifact(lib_unit_tests);

    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_lib_unit_tests.step);
}
