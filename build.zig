const std = @import("std");

const @"c src": []const []const u8 = &.{
    "src/xoshiro256.c",
    "src/split.c",
};
const @"c flags": []const []const u8 = &.{
    "-Wall",
    "-Wextra",
    "-pedantic",
    "-fPIC",
    "-shared",
};

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});

    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addSharedLibrary(.{
        .name = "xoshiro256",

        .target = target,
        .optimize = optimize,
        .pic = true,
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

    const cExe = b.addExecutable(.{
        .name = "cxoshiro",
        .target = target,
        .optimize = optimize,
    });
    cExe.addIncludePath(.{ .path = "include" });
    cExe.addCSourceFile(.{ .file = .{ .path = "main.c" }, .flags = &.{} });
    cExe.linkLibC();
    cExe.linkLibrary(lib);
    b.installArtifact(cExe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    const run_step = b.step("run", "Run the application.");
    run_step.dependOn(&run_cmd.step);

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    b.installArtifact(lib);
}
