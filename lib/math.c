double pow(double num, double pow)
{
	int counter = 1;
	while (counter <= pow)
	{
		num *= num;
		counter++;
	}
	return num;
}