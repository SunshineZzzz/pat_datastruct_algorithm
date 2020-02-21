// 中缀表达式如何转换为后缀表达式：
// 从头到尾读取中缀表达式的每个对象，对每个对象按不同的情况处理。
// 运算数：直接输出
// 左括号：压入堆栈
// 右括号：将栈顶的运算符弹出并输出，直到遇到左括号（出栈，不输出）；
// 运算符：
// 		若优先级大于栈顶运算符时，则把它压栈；
// 		若优先级小于等于栈顶运算符时，将栈顶运算符弹出并输出；再比较新的栈顶运算符，
// 		直到该运算符大于栈顶运算符优先级为止，然后将该运算符压栈；
// 若各对象处理完毕，则把堆栈中存留的运算符一并输出。
// 从入后缀表达式求值：
// 运算数：入栈；
// 运算符：从堆栈中弹出适当数量的运算数，计算并结果入栈；
// 最后，堆栈顶上的元素就是表达式的结果值。

#ifdef _WIN32
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// 线性栈的大小
#define stack_size 64
// 是否是运算符
#define is_operator(c) (c == '+' || c == '-' || c == '*' || c == '/')
// 是否是数字
#define is_number(c) (c >= '0' && c <= '9')

// 运算符优先级
int op_preced(const char c)
{
	switch (c)
	{
	case '*':
	case '/':
	{
		return 2;
	}
	case '+':
	case '-':
	{
		return 1;
	}
	}
}

// 运算符需要操作数个数
unsigned int op_arg_count(const char c)
{
	switch (c)
	{
	case '*':
	case '/':
	case '+':
	case '-':
	{
		return 2;
	}
	}
}

// 调度场算法
bool shunting_yard(const char* input, char* output)
{
	// 访问 输入的表达式字符串
	const char* strpos = input;
	// 表达式 字符串结尾
	const char* strend = input + strlen(input);
	// 临时变量 保存 遍历输入表达式字符
	char c;
	// 运算符栈
	char stack[stack_size];
	// 遍历堆栈 临时字符变量
	char sc;
	// 用于保存到 输出队列字符数组
	char* outpos = output;
	// 栈顶 下标，访问需要减少1
	unsigned int sl = 0;

	// 遍历 输入表达式
	while (strpos < strend)
	{
		c = *strpos;
		if (c != ' ')
		{
			// 如果输入为一个数字，则直接入输出队列
			if (is_number(c))
			{
				*outpos = c;
				++outpos;
			}
			// 如果输入符号为操作符，入栈
			else if (is_operator(c))
			{
				if (output < outpos)
				{
					if (is_number(*(outpos - 1)))
					{
						*outpos = '#';
						++outpos;
					}
				}
				// 判断运算符与栈顶符号的优先级，
				// 优先级低于找顶符号，
				// 则栈顶元素依次弹出并输出 到 输出队列
				while (sl > 0)
				{
					sc = stack[sl - 1];
					if (is_operator(sc) && (op_preced(c) <= op_preced(sc)))
					{
						*outpos = sc;
						++outpos;
						--sl;
					}
					else
					{
						break;
					}
				}
				stack[sl] = c;
				++sl;
			}
			// 如果是左括号直接入栈即可
			else if (c == '(')
			{
				if (output < outpos)
				{
					if (is_number(*(outpos - 1)))
					{
						*outpos = '#';
						++outpos;
					}
				}
				stack[sl] = c;
				++sl;
			}
			// 如果是右括号
			else if (c == ')')
			{
				if (output < outpos)
				{
					if (is_number(*(outpos - 1)))
					{
						*outpos = '#';
						++outpos;
					}
				}
				// 是否到左括号
				bool pe = false;
				// 从栈中弹出运算符直到左括号，将弹出的操作符追加到输出队列
				while (sl > 0)
				{
					sc = stack[sl - 1];
					if (sc == '(')
					{
						pe = true;
						break;
					}
					else
					{
						*outpos = sc;
						++outpos;
						--sl;
					}
				}

				if (!pe)
				{
					printf("parentheses mismatched\n");
					return false;
				}
				// 弹出左括号
				--sl;
			}
			else
			{
				printf("unknow token %c\n", c);
				return false;
			}
		}
		++strpos;
	}

	while (sl > 0)
	{
		if (output < outpos)
		{
			if (is_number(*(outpos - 1)))
			{
				*outpos = '#';
				++outpos;
			}
		}
		sc = stack[sl - 1];
		if (sc == '(' || sc == ')')
		{
			printf("parentheses mismatched\n");
			return false;
		}
		*outpos = sc;
		++outpos;
		--sl;
	}

	*outpos = '\0';
	return true;
}

// 计算后缀表达式
bool calculate(const char* input, double* rst)
{
	// 访问 输入的表达式字符串
	const char* strpos = input;
	// 表达式 字符串结尾
	const char* strend = input + strlen(input);
	// 临时变量 保存 遍历输入表达式字符
	char c;
	// 数字栈
	double stack[stack_size] = {0};
	// 栈顶 下标，访问需要减少1
	unsigned int sl = 0;
	// 临时用组装数字
	char tmp_number[stack_size] = { 0 };
	char* tmppos = tmp_number;
	const char* tmpend = tmp_number + stack_size;
	*rst = 0;

	while (strpos != strend)
	{
		c = *strpos;
		if (c != ' ')
		{
			if (is_number(c))
			{
				if (!tmppos || tmppos > tmpend || tmppos + 1 > tmpend)
				{
					printf("tmp_number length not enough");
					return false;
				}
				*tmppos = c;
				++tmppos;
				*tmppos = '\0';
			}
			else if (c == '#')
			{
				stack[sl] = atof(tmp_number);
				++sl;
				tmppos = tmp_number;
			}
			else if (is_operator(c))
			{
				int count = op_arg_count(c);
				if (sl < count)
				{
					printf("not enough operands on the stack");
					return false;
				}
				while (count)
				{
					if (c == '+')
					{
						*rst = stack[sl - 2] + stack[sl - 1];
						sl -= 2;
						stack[sl] = *rst;
						++sl;
						count -= 2;
					}
					else if (c == '-')
					{
						// 注意顺序
						*rst = stack[sl - 2] - stack[sl - 1];
						sl -= 2;
						stack[sl] = *rst;
						++sl;
						count -= 2;
					}
					else if (c == '*')
					{
						*rst = stack[sl - 2] * stack[sl - 1];
						sl -= 2;
						stack[sl] = *rst;
						++sl;
						count -= 2;
					}
					else if (c == '/')
					{
						// 注意顺序
						*rst = stack[sl - 2] / stack[sl - 1];
						sl -= 2;
						stack[sl] = *rst;
						++sl;
						count -= 2;
					}
					else
					{
						printf("unknow token %c\n", c);
						return false;
					}
				}
			}
		}
		++strpos;
	}

	if (sl == 1)
	{
		*rst = stack[sl - 1];
		--sl;
		return true;
	}

	printf("there is not only one value in the stack");
	return false;
}

int main()
{
	while (true)
	{
		char input[stack_size * 2] = { 0 };
		char output[stack_size * 4] = { 0 };

		scanf("%[^\n]", input);
		getchar();
		input[stack_size * 2 - 1] = 0;

		if (!shunting_yard(input, output))
		{
			break;
		}

		printf("%s => %s\n", input, output);

		double rst;
		if (!calculate(output, &rst))
		{
			break;
		}

		printf("%s = %f\n", input, rst);
	}

	return 0;
}