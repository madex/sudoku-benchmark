import time
std_rules =  [[i for n  in range(9) for i in range(1,10)], # colum
			  [i for i in range(1,10) for n in range(9)], # row
			  [3*int(i/3) + j for i in range(9) for j in range(1,4) for k in range(3)]] # basic blocks

testBase = 	[1, 0, 0,  0, 0, 7,  0, 9, 0,
			 0, 3, 0,  0, 2, 0,  0, 0, 8,
			 0, 0, 9,  6, 0, 0,  5, 0, 0,
			 0, 0, 5,  3, 0, 0,  9, 0, 0,
			 0, 1, 0,  0, 8, 0,  0, 0, 2,
			 6, 0, 0,  0, 0, 4,  0, 0, 0,
			 3, 0, 0,  0, 0, 0,  0, 1, 0, 
			 0, 4, 0,  0, 0, 0,  0, 0, 7,
			 0, 0, 7,  0, 0, 0,  3, 0, 0]

def valid(zipedField):
	flags = [0,0,0,0,0,0,0,0,0,0]
	for f,r in zipedField:
		if f == 0:
			continue
		mask = 1 << f
		if (flags[r] & mask) != 0:
			return False
		flags[r] |= mask
	return True

def check(field, rules):
	for rule in rules:		
		if not valid(zip(field, rule)):
			return False
	return True

def try_one_field(index, field, rules):
	try:
		while field[index] != 0:
			index += 1
	except IndexError:
		return False if 0 in field else True
	for i in range(1, 10):
		field[index] = i
		if check(field, rules):
			if try_one_field(index+1, field, rules):
				return True
	field[index] = 0
	return False

def sudoko(base, rules=std_rules):
	#field = list(base)
	print('solve following sudoko:')
	print_field(base)
	start = time.process_time()
	if try_one_field(0, base, rules):
		messuredTime = time.process_time() - start
		print('found solution in: ', messuredTime, ' sec')
		print_field(base)
	else:
		print('no solition found')
		
def print_field(field):
	j, l = 0, 0
	print()
	for i in field:
		print(' ', i if i > 0 else '_', end='')
		if j % 3 == 2: print(' ', end='')
		j += 1
		if j == 9:
			if l % 3 == 2: print()
			j, l = 0, l+1
			print()

sudoko(testBase)

