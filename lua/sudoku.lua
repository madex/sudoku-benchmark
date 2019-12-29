local std_rules = {
     { -- rule_rows
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2,
        3, 3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6, 6,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        8, 8, 8, 8, 8, 8, 8, 8, 8 
    }, { -- rule_colums
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8
    }, { --  rule basic blocks
        0, 0, 0,  1, 1, 1,  2, 2, 2,
        0, 0, 0,  1, 1, 1,  2, 2, 2,
        0, 0, 0,  1, 1, 1,  2, 2, 2,

        3, 3, 3,  4, 4, 4,  5, 5, 5,
        3, 3, 3,  4, 4, 4,  5, 5, 5,
        3, 3, 3,  4, 4, 4,  5, 5, 5,

        6, 6, 6,  7, 7, 7,  8, 8, 8,
        6, 6, 6,  7, 7, 7,  8, 8, 8,
        6, 6, 6,  7, 7, 7,  8, 8, 8
    }
}  
local quiz = { -- http://www.kubieziel.de/blog/archives/684-schwerstes-Sudoku.html
    1, 0, 0,  0, 0, 7,  0, 9, 0,
    0, 3, 0,  0, 2, 0,  0, 0, 8,
    0, 0, 9,  6, 0, 0,  5, 0, 0,
    0, 0, 5,  3, 0, 0,  9, 0, 0,
    0, 1, 0,  0, 8, 0,  0, 0, 2,
    6, 0, 0,  0, 0, 4,  0, 0, 0,
    3, 0, 0,  0, 0, 0,  0, 1, 0, 
    0, 4, 0,  0, 0, 0,  0, 0, 7,
    0, 0, 7,  0, 0, 0,  3, 0, 0
}

local function print_board(board)
    for k,v in ipairs(board) do
        io.write(" ")
        if (v == 0) then
            io.write("_");
        else
            io.write(v);
        end
        if ((k %  3) == 0) then io.write(" "); end
        if ((k %  9) == 0) then print(); end
        if ((k % 27) == 0) then print(); end
    end
end

local function rule_valid(board, rule)
    flags = {false, false, false, false, false, false, false, false, false,
             false, false, false, false, false, false, false, false, false,
             false, false, false, false, false, false, false, false, false,
             false, false, false, false, false, false, false, false, false,
             false, false, false, false, false, false, false, false, false,
             false, false, false, false, false, false, false, false, false,
             false, false, false, false, false, false, false, false, false,
             false, false, false, false, false, false, false, false, false,
             false, false, false, false, false, false, false, false, false
    }
    for k,v in ipairs(board) do
        if v > 0 then
            i = rule[k]*9 + v
            if (flags[i]) then
                return false;
            end
            flags[i] = true;
        end
    end
    return true;
end

local function rule_valid_slow_bits(board, rule)
    flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    for k,v in ipairs(board) do
        if v ~= 0 then
            mask = bit32.lshift(1, v)
            r = rule[k] + 1
            if (bit32.band(flags[r], mask)) ~= 0 then
                return false;
            end
            flags[r] = bit32.bor(flags[r], mask);
        end
    end
    return true;
end

local function check(board, rules)
    for k,v in ipairs(rules) do
        if not rule_valid(board, v) then 
            return false;
        end    
    end
    return true
end

local function sudoku_try_set_field(field_no, board, rules)
    while (true) do
        if (field_no > 9*9) then 
            return true; -- solved
        end
        if (board[field_no] == 0) then
            break;
        end
        field_no = field_no + 1;	
    end
    for i = 1,9,1 do
        board[field_no] = i;
        if check(board, rules) then
            if sudoku_try_set_field(field_no+1, board, rules) then
                return true;
            end
        end
    end
    board[field_no] = 0;
    return false;
end

print("solve following sudoko:\n");
print_board(quiz)
local start  = os.clock()
local result = sudoku_try_set_field(1, quiz, std_rules)
local time   = os.clock() - start
if result then
    print("found solution in ", time, " sec")
    print_board(quiz)
else
    print("no solution found")
end
