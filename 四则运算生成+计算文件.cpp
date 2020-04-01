#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stack>
#include<windows.h>



using std::stack;
//�����������ʽ
int ch2num ( const char &ch )  //��ȡ�����
{
	int num ( -1 );
	switch ( ch )
	{
	case'#':
		num = 0;
		break;
	case'+':
		num = 1;
		break;
	case'-':
		num = 2;
		break;
	case'*':
		num = 3;
		break;
	case'/':
		num = 4;
		break;
	case'(':
		num = 5;
		break;
	case')':
		num = 6;
		break;
	}
	return num;
}

int operator_2 ( const int &num1, const int &num2, const char &ch )  //���е��������������
{
	int num ( -1 );
	switch ( ch )
	{
	case'+':
		num = num2 + num1;
		break;
	case'-':
		num = num2 - num1;
		break;
	case'*':
		num = num2 * num1;
		break;
	case'/':
		num = num2 / num1;
		break;
	}
	return num;
}

int compare[5][6] = { { 0 }, { 1, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 1 }, { 1, 1, 1, 0, 0, 1 }, { 1, 1, 1, 0, 0, 1 } };  //����һ����ά�����¼�����֮������ȼ�

int Calculation ( char *str, int i )  //�����������ʽ���庯��
{
	stack<int>S_num;  //��������ջ�����ֵ�������
	stack<char>S_ch;
	while ( !S_ch.empty() )
		S_ch.pop();
	S_ch.push ( '#' );
	while ( !S_num.empty() )
		S_num.pop();
	int tnum ( 0 );
	for ( int i ( 0 ); str[i] != '\0'; )
	{
		if ( '0' <= str[i] && str[i] <= '9' )  //���ַ������е��������ַ���ת��Ϊ����
		{
			tnum *= 10;
			tnum += str[i] - '0';
			++i;
		}
		else if ( str[i] == '(' )  //�ж�С�������Ͳ�ѹ���ַ�ջ
		{
			S_ch.push ( '(' );
			++i;
		}
		else if ( str[i] == ')' )
		{
			S_num.push ( tnum );
			char ch = S_ch.top();  //����С�����ڵı��ʽ���������ѹ����ֵջ
			if ( ch != '(' )
			{
				S_ch.pop();
				int num1 = S_num.top();
				S_num.pop();
				int num2 = S_num.top();
				S_num.pop();
				tnum = operator_2 ( num1, num2, ch );
			}
			else
			{
				tnum = S_num.top();
				S_num.pop();
			}
			S_ch.pop();
			++i;
		}
		else
		{
			S_num.push ( tnum );
			tnum = 0;
			if ( compare[ch2num ( str[i] )][ch2num ( S_ch.top() )] == 1 )  //������������ȼ�����ֱ��ѹ�������ջ
				S_ch.push ( str[i] );
			else
			{
				while ( compare[ch2num ( str[i] )][ch2num ( S_ch.top() )] == 0 )  //������������ȼ��ͣ����Ѷ������ȼ��ߵ�������������㲢��������ѹ��
				{
					char ch = S_ch.top();
					S_ch.pop();
					int num1 = S_num.top();
					S_num.pop();
					int num2 = S_num.top();
					S_num.pop();
					S_num.push ( operator_2 ( num1, num2, ch ) );
				}
				S_ch.push ( str[i] );
			}
			++i;
		}
	}
	S_num.push ( tnum );
	char ch ( '\0' );
	while ( ( ch = S_ch.top() ) != '#' )  //��ʣ����������ε���ִ��
	{
		S_ch.pop();
		int num1 = S_num.top();
		S_num.pop();
		int num2 = S_num.top();
		S_num.pop();
		S_num.push ( operator_2 ( num1, num2, ch ) );
	}
	FILE *fpWrite = fopen ( "Answers.txt", "a" );  //��������д��Answers�ļ�
	if ( fpWrite == NULL )
	{
		return 0;
	}
	fprintf ( fpWrite, "Answer%d:\t%d\n", i, S_num.top() );
	return 1;
}





//�����������ʽ
int Random ( int m )  //������ɸ�����Χ��һ������
{
	int a;
	srand ( ( unsigned ) time ( NULL ) );
	Sleep ( 1000 );
	a = rand() % m + 1;
	return a;
}


char Symbol()  //������ɡ�+��-��*��/�����������һ��
{
	int a, b = 0;
	char x;
	a = Random ( 4 );
	do
	{


		switch ( a )
		{
		case 1:
			x = '+';
			break;

		case 2:
			x = '-';
			break;

		case 3:
			x = '*';
			break;

		case 4:
			x = '/';
			break;

		default:
			b = 1;

		}
	}
	while ( b );
	return x;
}



char Brackets ( int co, int ad )  //���ݸ��������жϲ�������ɡ���������С����
{
	int a;
	char x = '#';
	switch ( ad )
	{
	case 0:
	{
		a = Random ( 2 );
		switch ( a )
		{
		case 1:
			x = '(';
			break;

		case 2:
			break;

		default:
			break;
		}
	}

	case 1:
	{
		a = Random ( 2 );
		if ( co != 0 )
			switch ( a )
			{
			case 1:
				x = ')';
				break;

			case 2:
				break;

			default:
				break;
			}
		else
			break;
	}
	}

	return x;
}


int File_write ( char *a, int i )  //�����ɵ��������ʽд��Eercises.txt�ļ�
{
	int j = 0;
	FILE *fpWrite = fopen ( "Exercises.txt", "a" );
	if ( fpWrite == NULL )
	{
		return 0;
	}
	fprintf ( fpWrite, "topic%d:\t", i );
	while ( a[j] != NULL )
	{
		if ( a[j] == '+' || a[j] == '-' || a[j] == '*' || a[j] == '/' || a[j] == '=' )
			fprintf ( fpWrite, " %c ", a[j++] );
		else
			fprintf ( fpWrite, "%c", a[j++] );
	}
	fprintf ( fpWrite, " = " );
	fprintf ( fpWrite, "\n" );
	fclose ( fpWrite );
	return 1;
}



void Arithmetic ( int i, int n, int m )  //�����������ʽ���庯����nΪ��������������mΪ��ֵ��Χ��iΪ��Ŀ���
{
	char a[250] = {'0'};  //����һ���ַ��������������ʽ
	int x, p, add, rge, rng_num, count = 0, j = 0;  //count��Ϊ����������¼���������ŵĸ���
	rge = Random ( n );
	for ( int k = 0; k < rge; k++ )  //ѭ�������������ʽ
	{
		add = 0;  //add��Ϊ��־ֵ��Ӱ��Brackets()С�������ɺ����ڲ�ִ��
		a[j] = Brackets ( count, add );  //�������������
		if ( a[j] == '(' )
		{
			j++;
			count++;
		}

		rng_num = Random ( m );  //����һ��������ʽ����ֵ
		x = 1;
		p = 0;
		while ( rng_num / x )
		{
			x *= 10;
		}
		x /= 10;

		while ( x )
		{
			a[j++] = rng_num / x + '0';
			rng_num = rng_num % x;
			x /= 10;
			p++;
		}

		if ( a[j - 1 - p] != '(' )
		{
			add = 1;
			a[j] = Brackets ( count, add );
			if ( a[j] == ')' )
			{
				j++;
				count--;
			}
		}

		a[j++] = Symbol();  //�������һ�������

	}



	rng_num = Random ( m );  //����һ�������β��ֵ
	x = 1;
	while ( rng_num / x )
	{
		x *= 10;
	}
	x /= 10;

	while ( x )
	{
		a[j++] = rng_num / x + '0';
		rng_num = rng_num % x;
		x /= 10;
	}

	while ( count )  //����countֵ�Ƿ�Ϊ0���ж����������ž��������Ŷ�Ӧ
	{

		a[j++] = ')';
		count--;
	}
	while ( File_write ( a, i ) == 0 );  //д�����ɵ��������ʽ
	while ( Calculation ( a, i ) == 0 );  //������
}




//������
int main()
{
	int n, m, s, i;
	printf ( "�������������ʽ��ຬ������ĸ�����" );
	scanf ( "%d,%d,%d", &n );
	printf ( "�������������ʽ����ֵ�ķ�Χ��" );
	scanf ( "%d", &m );
	printf ( "�����������������ʽ��������" );
	scanf ( "%d", &s );
	FILE *fp1, *fp2;
	fp1 = fopen ( "Exercises.txt", "w" );
	fclose ( fp1 );
	fp2 = fopen ( "Answers.txt", "w" );
	fclose ( fp2 );
	for ( i = 1; i <= s; i++ )
	{
		Arithmetic ( i, n, m );
	}
	return 0;
}








