# Solve difficult sudoku as a performance test for different programming languages

The work on this started in 2013 and I´ve done it in a lot of programming languages since then.

The concept is a recursive algorithm that need as little memory as possible. 
It manipulates the field directly. The rules are made of arrays, so this solution is quite minimal.
I also make an obfuscated C version out of it. [sudoku_obfuscated.c](c/other/sudoku_obfuscated.c)

The tests ard made on macOs on macbook pro 15 from early 2013.

| lang   | time  |  exe-size |
| ------ | ----- | --------- |
| c (clang) | 7 ms  | 9 KB      |
| rust   | 6 ms  | 320 KB    |
| cystal | 32 ms | 420 KB    |
| js Chorme | 24 ms | |
| js Firefox | 21 ms | |
| java | 24 ms |  | | 
| lua | 1,7 s | |
| python3.7 | 2.7 | |