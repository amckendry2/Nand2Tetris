// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

	@SCREEN
	D=A
	@draw
	M=D
	@8191
	D=D+A
	@lim
	M=D
(LOOP)
	@color
	M=0
	@KBD
	D=M
	@WHITE
	D;JEQ
	@color
	M=-1
(WHITE)
	@color
	D=M
	@draw
	A=M
	M=D
	@draw
	M=M+1
	D=M
	@lim
	D=D-M
	@SKIP
	D;JLT
	@draw
	M=0
(SKIP)
	@LOOP
	0;JMP
