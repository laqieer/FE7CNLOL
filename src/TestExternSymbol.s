	.extern TestFunc1
	.global TestExternSymbol
TestExternSymbol:
	.word 0
	.word TestFunc1+1
	