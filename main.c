#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define H 7

int pword = 140816;//6位数字密码
struct customer {
	int num;//住户编号
	int age;//住户年龄
	char gender;//M for male,F for famale
	int house;//所住房屋编号
	struct customer* next;
};
typedef struct customer client;//客户结构体
struct workers {
	int num;//员工工号
	char area;//服务区域
	int serviceNum;//服务对象的数量
	struct workers* next;
};
typedef struct workers staff;//员工结构体

struct department {
	int number;//房屋编号
	int situation;//入住状态
	int capacity;//可入住人数
}dp[H] = { {1,0,2},{1,0,2},{1,0,2},{1,0,2},{1,0,1},{1,0,1},{1,0,1} };//公寓结构体

struct VIP {
	int ID;//会员编号
	int age;//年龄
	int houseNum;//所居住房屋编号
	struct VIP* next;
};
typedef struct VIP vip;//会员结构体

void house_init(void);
void mainMenu(void);
void menuSelect(void);
int search(void);
client* create(int);
client* clientOrder(client*,client*);
int Pass_word(void);

int main(void)
{
	house_init();
	menuSelect();//系统功能选择
	return 0;
}

void house_init(void) {
	dp[0].number = 1; dp[0].situation = 0; dp[0].capacity = 2;
	dp[1].number = 2; dp[1].situation = 0; dp[1].capacity = 2;
	dp[2].number = 3; dp[2].situation = 0; dp[2].capacity = 2;
	dp[3].number = 4; dp[3].situation = 0; dp[3].capacity = 2;
	dp[4].number = 5; dp[4].situation = 0; dp[4].capacity = 1;
	dp[5].number = 6; dp[5].situation = 0; dp[5].capacity = 1;
	dp[6].number = 7; dp[6].situation = 0; dp[6].capacity = 1;
}//公寓数据初始化
void mainMenu() {
	printf("********************************\n");
	printf("Elderly community service system\n");
	printf("********************************\n");
	printf("1.Client management\n2.Department management\n3.VIP management\n4.Staff management\n5.Exit\n");
	printf("Please choose the function:");
}
void menuSelect(void) {
	client* head;
	head = NULL;
	int choose,result;
	int i = 1;
	system("cls");
	do {
		mainMenu();
		scanf("%d", &choose);
		switch (choose) {
		case 1:
			result = search();
			if (result == 1)
				printf("This person can check in room %d.\n", result);
			else
				break;
			head = clientOrder(head, create(result));
			break;//客户管理模块
		case 4:
			Pass_word();
			break;//员工管理模块
		case 5:
			exit(1);
			break;
		}
	} while (i);
}//系统功能选择
int search(void) {
	int customNum;
	customNum = 0;
	int i;
	int MaxCapacity = 5;
	printf("Please enter the number of the client:\n");
	scanf("%d", &customNum);
	if (MaxCapacity < customNum) {
		printf("Sorry,there is no room for %d people!\n", customNum);
		return -1;
	}
	while (customNum <= MaxCapacity) {
		for (i = 0; i < H; i++) {
			if (dp[i].situation == 0)
				return (dp[i].number);
		}
		printf("Sorry,no room avilable now.");
	}
	return -1;
}//检索公寓
client* create(int result) {
	client* p;
	p = (client*)malloc(sizeof(client));
	int i, num, age, house;
	char gender;
	if (result != -1) {
		p->house = result;
		dp[result - 1].situation = 1;
		printf("Please input the client's number,age and gender(M for male/F for famale).\n");
		scanf("%d%d%c", &num, &age, gender);
		p->num = num;
		p->age = age;
		p->gender = gender;
	}
	putchar('\n');
	p->next = NULL;
	return p;
}
client* clientOrder(client* head, client* p) {
	client* pnew;
	pnew = head;
	if (head != NULL) {
		if (p != NULL) {
			while (pnew->next != NULL)
				pnew = pnew->next;
			pnew->next = p;
			printf("Check in!\n");
		}
		else
			printf("Error!");
	}
	else {
		if (p != NULL)
			head = p;
	}
	return head;
}
int Pass_word() {
    int password;
    do {
        printf("Please enter a 6-digit password:\n");
        scanf("%d", &password);
        if (pword == password) {
            printf("****************************************\n");
            printf(" Welcome to the staff management system\n");
            printf("****************************************\n");
            return 1;
        }
        else {
            printf("Wrong password!Please enter again.\n");
            printf("Input again or not('Y' for yes):\n");
        }
    } while (getchar() == 'y' || getchar() == 'Y');
    return 0;
}
