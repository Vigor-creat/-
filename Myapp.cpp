#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *file1 = NULL, *file2 = NULL;
	char fp1, fp2;
	int r = 0, w = 0, wo[100] = {0}, ri[100] = {0}, t = 1, i = 0, j = 0;
	if ( ( file1 = fopen ( "Answers.txt", "r" ) ) == 0 )
	{
		printf ( "can't find the file-Answers\n" );
		exit ( 0 );
	}
	if ( ( file2 = fopen ( "exercisefile.txt", "r" ) ) == 0 )
	{
		printf ( "can't find the file-exercisefile\n" );
		exit ( 0 );
	}
	while ( ( fp1 = fgetc ( file1 ) ) != EOF && ( fp2 = fgetc ( file2 ) ) != EOF )
	{
		for ( ; fp1 != '\n' || fp2 != '\n'; )
		{
			if ( fp1 != fp2 )
			{
				w++;
				wo[i++] = t;
				break;
			}
			fp1 = fgetc ( file1 ), fp2 = fgetc ( file2 );
		}
		if ( fp1 == '\n' && fp2 == '\n' )
		{
			r++;
			ri[j++] = t;
		}
		else if ( fp1 != '\n' && fp1 != EOF )
			while ( fp1 != '\n' )
				fp1 = fgetc ( file1 );
		while ( fp2 != '\n' && fp2 != EOF )
			fp2 = fgetc ( file2 );
		t++;
	}
	FILE *fp3 = fopen ( "Grade.txt", "w" );
	fclose ( fp3 );
	FILE *fpWrite = fopen ( "Grade.txt", "a" );
	fprintf ( fpWrite, "Correct:\t%d", r );
	if ( ri[0] != 0 )
	{
		fprintf ( fpWrite, "(" );
		for ( i = 0; ri[i] != 0; i++ )
			fprintf ( fpWrite, "%d,", ri[i] );
		fprintf ( fpWrite, ")\n" );
	}
	fprintf ( fpWrite, "Wrong:\t%d", w );
	if ( wo[0] != 0 )
	{
		fprintf ( fpWrite, "(" );
		for ( i = 0; wo[i] != 0; i++ )
			fprintf ( fpWrite, "%d,", wo[i] );
		fprintf ( fpWrite, ")" );
	}
	fclose ( fpWrite );
	fclose ( file1 );
	fclose ( file2 );
}
