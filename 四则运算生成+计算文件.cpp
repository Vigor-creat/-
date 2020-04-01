#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stack>
#include<windows.h>



using std::stack;
//计算算术表达式
int ch2num ( const char &ch )  //读取运算符
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

int operator_2 ( const int &num1, const int &num2, const char &ch )  //进行单个运算符的运算
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

int compare[5][6] = { { 0 }, { 1, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 1 }, { 1, 1, 1, 0, 0, 1 }, { 1, 1, 1, 0, 0, 1 } };  //创建一个二维数组记录运算符之间的优先级

int Calculation ( char *str, int i )  //计算算术表达式主体函数
{
	stack<int>S_num;  //创建两个栈存放数值和运算符
	stack<char>S_ch;
	while ( !S_ch.empty() )
		S_ch.pop();
	S_ch.push ( '#' );
	while ( !S_num.empty() )
		S_num.pop();
	int tnum ( 0 );
	for ( int i ( 0 ); str[i] != '\0'; )
	{
		if ( '0' <= str[i] && str[i] <= '9' )  //将字符数组中的数字由字符型转化为整型
		{
			tnum *= 10;
			tnum += str[i] - '0';
			++i;
		}
		else if ( str[i] == '(' )  //判断小括号类型并压入字符栈
		{
			S_ch.push ( '(' );
			++i;
		}
		else if ( str[i] == ')' )
		{
			S_num.push ( tnum );
			char ch = S_ch.top();  //计算小括号内的表达式，并将结果压入数值栈
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
			if ( compare[ch2num ( str[i] )][ch2num ( S_ch.top() )] == 1 )  //读入运算符优先级高则直接压入运算符栈
				S_ch.push ( str[i] );
			else
			{
				while ( compare[ch2num ( str[i] )][ch2num ( S_ch.top() )] == 0 )  //读入运算符优先级低，则将已读入优先级高的运算符先做运算并弹出，再压入
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
	while ( ( ch = S_ch.top() ) != '#' )  //将剩余运算符依次弹出执行
	{
		S_ch.pop();
		int num1 = S_num.top();
		S_num.pop();
		int num2 = S_num.top();
		S_num.pop();
		S_num.push ( operator_2 ( num1, num2, ch ) );
	}
	FILE *fpWrite = fopen ( "Answers.txt", "a" );  //将计算结果写入Answers文件
	if ( fpWrite == NULL )
	{
		return 0;
	}
	fprintf ( fpWrite, "Answer%d:\t%d\n", i, S_num.top() );
	return 1;
}





//生成算术表达式
int Random ( int m )  //随机生成给定范围内一个数字
{
	int a;
	srand ( ( unsigned ) time ( NULL ) );
	Sleep ( 1000 );
	a = rand() % m + 1;
	return a;
}


char Symbol()  //随机生成‘+、-、*、/’运算符其中一个
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



char Brackets ( int co, int ad )  //根据给定参数判断并随机生成‘（、）’小括号
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


int File_write ( char *a, int i )  //将生成的算术表达式写入Eercises.txt文件
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



void Arithmetic ( int i, int n, int m )  //生成算术表达式主体函数，n为最大运算符个数，m为数值范围，i为题目编号
{
	char a[250] = {'0'};  //定义一个字符数组存放算术表达式
	int x, p, add, rge, rng_num, count = 0, j = 0;  //count作为计数器，记录生成左括号的个数
	rge = Random ( n );
	for ( int k = 0; k < rge; k++ )  //循环生成算术表达式
	{
		add = 0;  //add作为标志值，影响Brackets()小括号生成函数内部执行
		a[j] = Brackets ( count, add );  //随机生成左括号
		if ( a[j] == '(' )
		{
			j++;
			count++;
		}

		rng_num = Random ( m );  //生成一个参与表达式的数值
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

		a[j++] = Symbol();  //随机生成一个运算符

	}



	rng_num = Random ( m );  //生成一个随机结尾数值
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

	while ( count )  //根据count值是否为0，判断所有左括号均有右括号对应
	{

		a[j++] = ')';
		count--;
	}
	while ( File_write ( a, i ) == 0 );  //写入生成的算术表达式
	while ( Calculation ( a, i ) == 0 );  //计算结果
}




//主函数
int main()
{
	int n, m, s, i;
	printf ( "请输入算术表达式最多含运算符的个数：" );
	scanf ( "%d,%d,%d", &n );
	printf ( "请输入算术表达式内数值的范围：" );
	scanf ( "%d", &m );
	printf ( "请输入生成算术表达式的数量：" );
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








