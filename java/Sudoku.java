import java.io.InputStream;
import java.io.OutputStream;
import java.util.Date;
import java.util.Set;
import javax.lang.model.SourceVersion;

public class Sudoku {
    public static void main(String[] args) {
        byte[] board = quiz;
        System.out.println("solve following sudoko:\n");
        print_board(board);
        long time  = new Date().getTime(); 
        if (sudoku(board)) {
            System.out.println("found solution in " + (new Date().getTime() - time) + " ms :");
            print_board(board);
        } else 
            System.out.println("no solition found\n");
        System.out.println("");
    }

    static byte rule_rows[] = {
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

    static byte rule_colums[] = {
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
                        
    static byte rule_basic_blocks[] = {
        0, 0, 0,  1, 1, 1,  2, 2, 2,
        0, 0, 0,  1, 1, 1,  2, 2, 2,
        0, 0, 0,  1, 1, 1,  2, 2, 2,
        
        3, 3, 3,  4, 4, 4,  5, 5, 5,
        3, 3, 3,  4, 4, 4,  5, 5, 5,
        3, 3, 3,  4, 4, 4,  5, 5, 5,
        
        6, 6, 6,  7, 7, 7,  8, 8, 8,
        6, 6, 6,  7, 7, 7,  8, 8, 8,
        6, 6, 6,  7, 7, 7,  8, 8, 8,
    };

    static byte quiz[] = { //  http://www.kubieziel.de/blog/archives/684-schwerstes-Sudoku.html
        1, 0, 0,  0, 0, 7,  0, 9, 0,
        0, 3, 0,  0, 2, 0,  0, 0, 8,
        0, 0, 9,  6, 0, 0,  5, 0, 0,
        0, 0, 5,  3, 0, 0,  9, 0, 0,
        0, 1, 0,  0, 8, 0,  0, 0, 2,
        6, 0, 0,  0, 0, 4,  0, 0, 0,
        3, 0, 0,  0, 0, 0,  0, 1, 0, 
        0, 4, 0,  0, 0, 0,  0, 0, 7,
        0, 0, 7,  0, 0, 0,  3, 0, 0,
    };

    static byte rules[][] = {rule_rows, rule_colums, rule_basic_blocks}; 

    static boolean rule_valid(byte[] board, byte[] rule, int[] sets) {
        int flags[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int i = 0; i < 9*9; i++) {
            byte b = board[i];
            if (b == 0) continue;
            int mask = (1 << b);
            int r = rule[i];
            if ((flags[r] & mask) != 0) {
                return false;
            }
            flags[r] |= mask;
        }
        for (int i = 0; i < 9*9; i++) {
            sets[i] |= flags[rule[i]];
        }
        return true;
    }

    static boolean check(byte[] board, int[] sets) {
        for (int i = 0; i < rules.length; i++) { // check all rules
            if (!rule_valid(board, rules[i], sets)) {
                return false;
            }
        }
        return true; 
    }

    static boolean sudoku_try_set_field(int field_no, byte[] board, int sets[]) {
        while (true) { // find field_no of the next unset field
            if (field_no >= 9*9) { 
                return true; // solved
            }
            if (board[field_no] == 0) {
                break;
            }
            field_no++;	
        }
        for (byte i = 1; i < 10; i++) {
            if (((1 << i) & sets[field_no]) == 0) {
                board[field_no] = i;
                int[] new_sets = sets.clone();
                if (check(board, new_sets)) {
                    if (sudoku_try_set_field(field_no+1, board, new_sets)) {
                        return true;
                    }
                }
            }
        }
        board[field_no] = 0;
        return false; 
    }

    static boolean sudoku(byte[] board) {
        int[] sets = new int[81];
        return sudoku_try_set_field(0, board, sets);
    } 

    static void print_board(byte[] board) {
        System.out.println();
        for (int i = 0; i < 9*9; i++) {
            if (board[i] == 0) { 
                System.out.print(" _"); 
            } else { 
                System.out.print(" " + board[i]);
            }
            if ((i %  3) ==  2) { System.out.print(" "); }
            if ((i %  9) ==  8) { System.out.println(); }
            if ((i % 27) == 26) { System.out.println(); }
        }
    }
}
