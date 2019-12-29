fn solve_sudoku(field: &mut [usize; 81], rules: &Vec<&[usize]>) -> bool {
    let set_mask = [0; 81];
    sudoku_try_set_field(0, field, rules, set_mask)
}

fn sudoku_try_set_field(index: usize, field: &mut [usize; 81], 
                        rules: &Vec<&[usize]>, set_mask: [usize; 81]) -> bool {
    let mut field_no: usize = index;
    loop { // search next empty field
        if field_no >= 81 {
            return true;
        } 
        if field[field_no] == 0 { 
            break; // found so try
        }
        field_no += 1;
    }
    for i in 1..10 {
        if ((1 << i) & set_mask[field_no]) == 0 { // don´t try already set numbers
            field[field_no] = i;
            let mut set_mask_next = set_mask.clone(); // make a clone 
            if rules.iter().all(|rule| valid(field, rule, &mut set_mask_next)) {
                if sudoku_try_set_field(field_no + 1, field, rules, set_mask_next) {
                    return true;
                }
            }
        }
    }
    field[field_no] = 0;
    false
}

/// is field accordeing to the rule array vaild?
fn valid(field: &[usize; 81], rule: &[usize], set_mask: &mut[usize]) -> bool {
    let mut flags = [0; 9];
    for (&f, &r) in field.iter().zip(rule.iter()) {
        if f == 0 {
            continue; // check only set fields
        }
        let mask = 1 << f;
        if (flags[r] & mask)  != 0 {
            return false;
        }
        flags[r] |= mask; 
    }
    for (i, &r) in rule.iter().enumerate() {
        set_mask[i] |= flags[r]; // mark numbers that are taken for this rule
    }
    true
} 

/// prints the current state of the board
fn print_board(board: &[usize; 81]) {
    println!();
    for (i, num) in board.iter().enumerate() {
        print!(" {}", if num == &0 { "_".to_string() } else { num.to_string() });
        if (i %  3) ==  2 { print!(" "); }
        if (i %  9) ==  8 { println!();  }
        if (i % 27) == 26 { println!();  }
    }
}

fn main() {
    // All same numbers defines a group in. In these group no number between 1..10 
    // can be set twice
    let rule_rows: Vec<usize> = (0..9).cycle().take(9*9).collect();
    let rule_colums: Vec<usize> = (0..81).map(|x| x / 9).collect();
    let rule_basicblocks: Vec<usize> = 
        (0..81).map(|x| (x % 9 / 3) + ((x/27) * 3) % 9).collect();
    let rules = vec![rule_rows.as_slice(), 
                     rule_colums.as_slice(), 
                     rule_basicblocks.as_slice()];
    let mut field = [
        1, 0, 0,  0, 0, 7,  0, 9, 0,
        0, 3, 0,  0, 2, 0,  0, 0, 8,
        0, 0, 9,  6, 0, 0,  5, 0, 0,

        0, 0, 5,  3, 0, 0,  9, 0, 0,
        0, 1, 0,  0, 8, 0,  0, 0, 2,
        6, 0, 0,  0, 0, 4,  0, 0, 0,

        3, 0, 0,  0, 0, 0,  0, 1, 0, 
        0, 4, 0,  0, 0, 0,  0, 0, 7,
        0, 0, 7,  0, 0, 0,  3, 0, 0
    ];
    println!("solve following sudoko:");
	print_board(&field);
    println!("result:");
    use std::time::Instant;
    let now = Instant::now();
    let result = solve_sudoku(&mut field, &rules);
    let elapsed = now.elapsed();
    let sec = (elapsed.as_secs() as f64) + (elapsed.subsec_nanos() as f64 / 1000_000_000.0);
    println!("Seconds: {}", sec);
    if result {
        print_board(&field);
    } else {
        println!("no solition found");
    }
}
