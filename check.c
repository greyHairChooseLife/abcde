#define _CRT_SECURE_NO_WARNINGS
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 20
/*
char *num_index(char *str)
{

}

char *text_index(char *str)
{

}
*/

struct arr_box{
	char *A[10];
	char *B[10];
	char *B2[10];
	char **C[20];
}box;

int ft_len(char *nbr)
{
	int idx;

	idx = 0;
	while (*nbr++)
		idx++;
	return (idx);
}

int f_atoi(char *str)
{
	int res;

	res = 0;
	while (*str)
	{
		res *= 10;
		res += *str++ - '0';
	}
	return (res);
}

void arr_push(char *nbr, char *text)
{
	int len;

	len = ft_len(nbr);
	//printf("len : %d\n", len);
	if (len == 1)
	{
		box.A[f_atoi(nbr)] = text;
		//printf("%s\n", box.A[f_atoi(nbr)]);
	}
}

char *make_clean_text(char *str)
{
	char res[2048];
	int idx;

	printf("%p__res\n", res);

	char *re;
	re = res;
	idx = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str != '\n')
		res[idx++] = *str++;
	res[idx] = 0;
	return (re);
}

char *make_clean_nbr(char *str)
{
	char res1[2045];
	int idx;

	printf("%p__res1\n", res1);
	char *re1;
	re1 = res1;
	idx = 0;
	while (*str >= '0' && *str <= '9')
		res1[idx++] = *str++;
	res1[idx] = '\0';
	return (re1);
}

void index_split(char *str)
{
	char tmp[2048];
	char tmp2[2048];
	int idx;			//세고있는 tmp의 인덱스 위치
	int flag;
	int cnt;			//결과값 첫번째의 몇번째 배열인지 체크
	char **p_res;
	char *input_nbr;
	char *input_text;

	idx = 0;
	flag = 0;
	cnt = 0;
	while (*str)
	{
		tmp2[idx] = *str;
		tmp[idx++] = *str;
		if (*str == ':' && !flag)
		{
			tmp[idx] = 0;
			input_nbr = make_clean_nbr(tmp);
			//여기서 print값 넘겨주기
			idx = 0;
			flag = 1;
		}
		else if (*str == '\n')
		{
			tmp2[idx] = 0;
			input_text = make_clean_text(tmp2);

			printf("arr_nbr : %s\n", input_nbr);
			printf("arr_text : %s\n\n", input_text);
		//	arr_push(input_nbr, input_text);
			idx = 0;
			flag = 0;
		}
		str++;
	}
}

int main()
{
	int fd;
	int cnt;
	char buff[2048];					//파일 최대 크기 구하기위함 1024보다 더크게해야할듯
	char *ERR = "Dict Error\n";
	int idx;
	int arr_size = 0;
	char **arr_save;

	fd = open("./numbers.dict.txt", O_RDONLY);
	if (fd == -1)						//파일 읽지못했을때 에러 출력(errcode=1)
	{
		while (*ERR)
			write(1, ERR++,1);
		return (1);
	}
	while (read(fd, buff, 1) > 0)
	{
		if (buff[0] == '\n')			//동적 할당 얼마나 받을지 정함
			arr_size++;
		cnt++;							//파일 최대크기 세기
	}
	close(fd);
	open("./numbers.dict.txt", O_RDONLY);

	read(fd, buff, cnt);
	int	index = 0;
	char *p_buff;						//저장한 buff확인
	p_buff = buff;

	char tmp[2048];						//최대 크기를 1024라고 잡아도 되는지..

	printf("arr_size : %d\n", arr_size);
	index_split(p_buff);

}
