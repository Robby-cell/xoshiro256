const std = @import("std");
const c = @cImport({
    @cInclude("xoshiro256.h");
});

pub fn main() void {
    var rng = c.initXoshiro256(64);
    var rng2 = c.initXoshiro256(77733);

    for (0..20) |_| {
        const next = c.nextXoshiro256(&rng);
        const next2 = c.nextXoshiro256(&rng2);
        std.debug.print("{:20} : {:20}\n", .{ next, next2 });
    }
}
