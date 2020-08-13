const std = @import("std");
const warn = std.debug.warn;

fn solve_sudoku(field: *[81]u8, rules: [3][9 * 9]u8) bool {
    var set_mask = [_]u16{0} ** 81;
    return sudoku_try_set_field(0, field, rules, &set_mask);
}

fn sudoku_try_set_field(index: u8, field: *[81]u8, rules: [3][81]u8, set_mask: *[81]u16) bool {
    var field_no: u8 = index;
    while (true) { // search next empty field
        if (field_no >= 81) {
            return true;
        }
        if (field[field_no] == 0) {
            break; // found so try
        }
        field_no += 1;
    }
    var i: u8 = 1;
    while (i < 10) {
        if ((@intCast(u16, 1) << @intCast(u4, i) & set_mask[field_no]) == 0) { // don´t try already set numbers
            field[field_no] = i;
            var set_mask_next: [81]u16 = undefined;
            std.mem.copy(u16, &set_mask_next, set_mask); // make a clone
            var all_valid: bool = true;
            for (rules) |rule| {
                if (!valid(field, rule, &set_mask_next)) {
                    all_valid = false;
                    break;
                }
            }
            if (all_valid) {
                if (sudoku_try_set_field(field_no + 1, field, rules, &set_mask_next)) {
                    return true;
                }
            }
        }
        i += 1;
    }
    field[field_no] = 0;
    return false;
}

fn valid(field: *[81]u8, rule: [81]u8, set_mask: *[81]u16) bool {
    var flags = [_]u16{0} ** 9;
    for (field) |f, i| {
        if (f == 0) {
            continue;
        }
        const mask: u16 = (@intCast(u16, 1) << @intCast(u4, f));
        const r: u8 = rule[i];
        if (flags[r] & mask != 0) {
            return false;
        }
        flags[r] |= mask;
    }
    for (rule) |r, i| {
        set_mask[i] |= flags[r]; // mark numbers that are taken for this rule
    }
    return true;
}

fn printBoard(board: [9 * 9]u8) void {
    warn("\n", .{});
    for (board) |num, i| {
        if (num == 0) {
            warn(" _", .{});
        } else {
            warn(" {}", .{num});
        }
        if ((i % 3) == 2) {
            warn(" ", .{});
        }
        if ((i % 9) == 8) {
            warn("\n", .{});
        }
        if ((i % 27) == 26) {
            warn("\n", .{});
        }
    }
}

pub fn main() anyerror!void {
    var board = [_]u8{
        1, 0, 0, 0, 0, 7, 0, 9, 0,
        0, 3, 0, 0, 2, 0, 0, 0, 8,
        0, 0, 9, 6, 0, 0, 5, 0, 0,
        0, 0, 5, 3, 0, 0, 9, 0, 0,
        0, 1, 0, 0, 8, 0, 0, 0, 2,
        6, 0, 0, 0, 0, 4, 0, 0, 0,
        3, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 4, 0, 0, 0, 0, 0, 0, 7,
        0, 0, 7, 0, 0, 0, 3, 0, 0,
    };
    const rule_rows = [_]u8{
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
    };
    const rule_colums = [_]u8{
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2,
        3, 3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6, 6,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        8, 8, 8, 8, 8, 8, 8, 8, 8,
    };
    const rule_basicblocks = [_]u8{
        0, 0, 0, 1, 1, 1, 2, 2, 2,
        0, 0, 0, 1, 1, 1, 2, 2, 2,
        0, 0, 0, 1, 1, 1, 2, 2, 2,
        3, 3, 3, 4, 4, 4, 5, 5, 5,
        3, 3, 3, 4, 4, 4, 5, 5, 5,
        3, 3, 3, 4, 4, 4, 5, 5, 5,
        6, 6, 6, 7, 7, 7, 8, 8, 8,
        6, 6, 6, 7, 7, 7, 8, 8, 8,
        6, 6, 6, 7, 7, 7, 8, 8, 8,
    };
    const rules = [_][9 * 9]u8{
        rule_rows,
        rule_colums,
        rule_basicblocks,
    };
    printBoard(board);
    const msBefore = std.time.milliTimestamp();
    const reuslt = solve_sudoku(&board, rules);
    const ms = std.time.milliTimestamp() - msBefore;
    warn("Time {} ms", .{ms});
    if (reuslt) {
        printBoard(board);
    } else {
        warn("no solution found", .{});
    }
}
