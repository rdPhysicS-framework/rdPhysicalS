__kernel void test(__global char *out)
{ 
	out[0] = 'O';
	out[1] = 'l';
	out[2] = 'a';
	out[3] = ' ';
	out[4] = 'm';
	out[5] = 'u';
	out[6] = 'n';
	out[7] = 'd';
	out[8] = 'o';
	out[9] = '\0';
}
