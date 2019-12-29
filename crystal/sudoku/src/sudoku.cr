# TODO: Write documentation for `Sudoku`
module Sudoku
  VERSION           = "0.1.0"
  RULE_ROWS         = (0..8).cycle.first(9*9).to_a
  RULE_COLUMS       = (0..80).map { |x| x // 9 }.to_a
  RULE_BASIC_BLOCKS =
    (0..80).map { |x| (x % 9 // 3) + ((x//27) * 3) % 9 }.to_a
  RULES = [RULE_ROWS, RULE_COLUMS, RULE_BASIC_BLOCKS]

  def self.print_board(board : Array(Int32))
    puts ""
    board.each_with_index do |x, i|
      print " #{x.zero? ? "_" : x}"
      print " " if i %  3 ==  2
      puts ""   if i %  9 ==  8
      puts ""   if i % 27 == 26
    end
  end

  private def self.set_field?(index : Int32, board : Array(Int32), set_mask : Array(Int32))
    field_no = index
    loop do
      return true if field_no >= 81
      break if board[field_no].zero?
      field_no += 1
    end
    (1..9).each do |i|
      if ((1 << i) & set_mask[field_no]).zero?
        board[field_no] = i
        new_set_mask = set_mask.clone
        if RULES.all? { |rule| valid?(board, rule, new_set_mask) }
          if set_field?(field_no + 1, board, new_set_mask)
            return true
          end
        end
      end
    end
    board[field_no] = 0
    false
  end

  private def self.valid?(board, rule, set_mask)
    flags = Array.new(9, 0)
    board.zip(rule).each do |(f, r)|
      next if f.zero?
      mask = 1 << f
      return false if !(flags[r] & mask).zero?
      flags[r] |= mask
    end
    rule.each_with_index do |r, i|
      set_mask[i] |= flags[r] # mark numbers that are taken for this rule
    end
    true
  end

  def self.solve?(board : Array(Int32))
    set_mask = Array.new(81, 0)
    set_field?(0, board, set_mask)
   end

  def self.main
    field = [
      1, 0, 0,  0, 0, 7,  0, 9, 0,
      0, 3, 0,  0, 2, 0,  0, 0, 8,
      0, 0, 9,  6, 0, 0,  5, 0, 0,

      0, 0, 5,  3, 0, 0,  9, 0, 0,
      0, 1, 0,  0, 8, 0,  0, 0, 2,
      6, 0, 0,  0, 0, 4,  0, 0, 0,

      3, 0, 0,  0, 0, 0,  0, 1, 0, 
      0, 4, 0,  0, 0, 0,  0, 0, 7,
      0, 0, 7,  0, 0, 0,  3, 0, 0
    ]

    print_board(field)
    start_time = Time.local
    result = solve?(field)
    stop_time = Time.local
    puts "Millisecounds: #{(stop_time - start_time).nanoseconds() / 1000_000.0}"
    if result
      print_board(field)
    else
      puts "no solition found"
    end
  end

  main
end
