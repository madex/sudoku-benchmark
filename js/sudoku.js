

var rule_rows = [
  0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1,
  2, 2, 2, 2, 2, 2, 2, 2, 2,
  3, 3, 3, 3, 3, 3, 3, 3, 3,
  4, 4, 4, 4, 4, 4, 4, 4, 4,
  5, 5, 5, 5, 5, 5, 5, 5, 5,
  6, 6, 6, 6, 6, 6, 6, 6, 6,
  7, 7, 7, 7, 7, 7, 7, 7, 7,
  8, 8, 8, 8, 8, 8, 8, 8, 8];
var rule_colums = [
  0, 1, 2, 3, 4, 5, 6, 7, 8,
  0, 1, 2, 3, 4, 5, 6, 7, 8,
  0, 1, 2, 3, 4, 5, 6, 7, 8,
  0, 1, 2, 3, 4, 5, 6, 7, 8,
  0, 1, 2, 3, 4, 5, 6, 7, 8,
  0, 1, 2, 3, 4, 5, 6, 7, 8,
  0, 1, 2, 3, 4, 5, 6, 7, 8,
  0, 1, 2, 3, 4, 5, 6, 7, 8,
  0, 1, 2, 3, 4, 5, 6, 7, 8];                                     
var rule_basic_blocks = [
  0, 0, 0,  1, 1, 1,  2, 2, 2,
  0, 0, 0,  1, 1, 1,  2, 2, 2,
  0, 0, 0,  1, 1, 1,  2, 2, 2,
  
  3, 3, 3,  4, 4, 4,  5, 5, 5,
  3, 3, 3,  4, 4, 4,  5, 5, 5,
  3, 3, 3,  4, 4, 4,  5, 5, 5,
  
  6, 6, 6,  7, 7, 7,  8, 8, 8,
  6, 6, 6,  7, 7, 7,  8, 8, 8,
  6, 6, 6,  7, 7, 7,  8, 8, 8];
var quiz = [
  1, 0, 0,  0, 0, 7,  0, 9, 0,
  0, 3, 0,  0, 2, 0,  0, 0, 8,
  0, 0, 9,  6, 0, 0,  5, 0, 0,
  0, 0, 5,  3, 0, 0,  9, 0, 0,
  0, 1, 0,  0, 8, 0,  0, 0, 2,
  6, 0, 0,  0, 0, 4,  0, 0, 0,
  3, 0, 0,  0, 0, 0,  0, 1, 0, 
  0, 4, 0,  0, 0, 0,  0, 0, 7,
  0, 0, 7,  0, 0, 0,  3, 0, 0];
var rules = [rule_rows, rule_colums, rule_basic_blocks]; 
var board = quiz;
function rule_valid(board, rule) {
	var flags =[0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
	var f, r, i, j = 0;
	for (i = 0; i < 9; i++) {
        f = board[j]; r = rule[j]; j = j + 1;
		if (f != 0 && r < 9 && flags[r] & (1 << f)) 
			return false;
		flags[r] |= 1 << f;
        f = board[j]; r = rule[j]; j = j + 1;
		if (f != 0 && r < 9 && flags[r] & (1 << f)) 
			return false;
		flags[r] |= 1 << f;
        f = board[j]; r = rule[j]; j = j + 1;
		if (f != 0 && r < 9 && flags[r] & (1 << f)) 
			return false;
		flags[r] |= 1 << f;
        f = board[j]; r = rule[j]; j = j + 1;
		if (f != 0 && r < 9 && flags[r] & (1 << f)) 
			return false;
		flags[r] |= 1 << f;
        f = board[j]; r = rule[j]; j = j + 1;
		if (f != 0 && r < 9 && flags[r] & (1 << f)) 
			return false;
		flags[r] |= 1 << f;
        f = board[j]; r = rule[j]; j = j + 1;
		if (f != 0 && r < 9 && flags[r] & (1 << f)) 
			return false;
		flags[r] |= 1 << f;
        f = board[j]; r = rule[j]; j = j + 1;
		if (f != 0 && r < 9 && flags[r] & (1 << f)) 
			return false;
		flags[r] |= 1 << f;
        f = board[j]; r = rule[j]; j = j + 1;
		if (f != 0 && r < 9 && flags[r] & (1 << f)) 
			return false;
		flags[r] |= 1 << f;
        f = board[j]; r = rule[j]; j = j + 1;
		if (f != 0 && r < 9 && flags[r] & (1 << f)) 
			return false;
		flags[r] |= 1 << f;
	}
	return true;
}
function check(board, rules) {
	var rule, i;
	for (i = 0; i < rules.length; i++) { // check all rules
		rule = rules[i];
		if (!rule_valid(board, rule))
			return false;
	}
	return true;
}
function sudoku_try_set_field(field_no, board, rules) {
	var i;
	while (true) { // find field_no of the next unset field
		if (field_no >= 9*9) 
			return true; // solved
		if (board[field_no] == 0)
			break;
		field_no++;	
	}
	for (i = 1; i < 10; i++) {
		board[field_no] = i;
		if (check(board, rules))
			if (sudoku_try_set_field(field_no+1, board, rules))
				return 1;
	}
	board[field_no] = 0;
	return false;
}

function print_board(board) {
	var j = 0, l = 0, i;
	for (i = 0; i < 9*9; i++) {
		console.log(" %d", board[i]);
		if ((j % 3) == 2) console.log(" ");
		if (++j == 9) {
			if ((l++ % 3) == 2) console.log("\n");
			j = 0;
			console.log("\n");
		}
	}
}

console.log("solve following sudoko:\n");
print_board(board);
var float_ts = new Date().getTime();
if (sudoku_try_set_field(0, board, rules)) {
		console.log('found solution in '+ (new Date().getTime() - float_ts) + ' ms :<br>');
		print_board(board);
} else 
		console.log("no solition found");
