#include<stdio.h>
#include<string.h>
#include<math.h>

#define H 7

int pword = 140816;//6位数字密码
struct customer {
	int num;//住户编号
	int age;//住户年龄
	int gender;
	int house;//所住房屋编号
	struct customer* next;
};
typedef struct customer client;//客户结构体

struct workers {
	int num;//员工工号
	int dp_num;//所管理房屋的编号
	int serviceNum;//服务对象的数量
	struct workers* next;
}SA[H];
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
};
typedef struct VIP vip;//会员结构体

struct node{
    vip stdinfo;
    struct node *next;
};typedef struct node NODE;

void house_init(void);
void mainMenu(void);
void menuSelect(void);
int search(void);
client* create(int);
client* clientOrder(client*, client*);
int Pass_word(void);
void checkDp(int);
NODE *create_vip(int *p_n,int *p_max);
NODE *add_vip(NODE *tail,NODE *new_vip);
void show_vip(NODE *head);
NODE *search_vip(NODE *head,int keyno);
NODE *delect_vip(NODE *head,int keyno,int *n);
void show_avip(vip v);
void vip_manage();
void exit(void);
void staff_manage(void);
staff* printfinforlist(staff *head);
int length(staff *head);
void push(staff* head);
staff *createnote(staff*,staff*);
void staff_manage_init(void);

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
	printf("1.Client management\n2.Department management\n3.VIP management\n4.Staff management\n5.Exit\n\n");
}

void menuSelect(void) {
	client* head;
	head = NULL;
	int choose, result;
	vip* vp;
	vp = NULL;
	int i = 1;
	int a;//房屋编号
	system("cls");
	mainMenu();
	do {
	    printf("Please choose the function number:");
        fflush(stdin);
		scanf("%d", &choose);
		switch (choose) {
		case 1:
			result = search();
			if (result == 1)
				printf("This person can check in room %d.\n\n", result);
			else
				break;
			head = clientOrder(head, create(result));
			break;//客户管理模块
		case 2:
			printf("Please enter the number of the department you want to check:");
			scanf("%d", &a);
			checkDp(a);
			break;
		case 3:
			vip_manage();
			break;
		case 4:
			Pass_word();
			staff_manage();
			break;
		case 5:
			exit();
			break;
		}
	} while (i);
}//系统功能选择

int search(void) {
	int customNum;
	customNum = 0;
	int i;
	int MaxCapacity = 2;
	printf("Please enter the number of the client:\n");
	scanf("%d", &customNum);
	if (MaxCapacity < customNum) {
		printf("Sorry,there is no room for %d people!\n\n", customNum);
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
	int gender;
	if (result != -1) {
		p->house = result;
		dp[result - 1].situation = 1;
		printf("Please input the client's number,age and gender(1 for male/2 for famale).\n");
		scanf("%d%d%d", &num, &age, &gender);
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

void checkDp(int a) {
	int j;
	for (j = 0; j < H; j++) {
		if (dp[j].number == a) {
			if (dp[j].situation == 1) {
				printf("The room %d is occupied by %d people.\n\n", dp[j].number, dp[j].capacity);
			}
			else if (dp[j].situation == 0) {
				printf("The room %d is empty.\n\n", dp[j].number);
			}
		}
	}
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
}//密码校验模块

 NODE *create_vip(int *p_n,int *p_max){
     NODE *p;
     vip v;
     p=(NODE *)malloc(sizeof(vip));
     if(p!=NULL){
        v.ID=*p_max;
        printf("age:");
        scanf("%d",v.age);
        printf("house number:");
        scanf("%d",v.houseNum);
        (*p_n)++;
        (*p_max)++;
        p->stdinfo=v;
        p->next=NULL;
        }
        return p;
}
NODE *add_vip(NODE *tail,NODE *new_vip){
    if(tail)
        tail->next=new_vip;
    return new_vip;
}
void show_vip(NODE *head){
    NODE *p=head;
    if(p==NULL)
        printf("No data!\n");
    while(p){
        show_avip(p->stdinfo);
        p=p->next;
    }
}

void show_avip(vip v){
    printf("ID:%d\n",v.ID);
    printf("age:%d\n",v.age);
    printf("houseNum:%d\n",v.houseNum);
}

NODE *search_vip(NODE *head,int keyno){
    NODE *p=head;
    while(p)
    if(p->stdinfo.ID==keyno){
        break;
    }
    p=p->next;

    if(p==NULL)
        printf("NO vip with ID %d\n",keyno);
    return p;
}

NODE *delect_vip(NODE *head,int keyno,int *p_n){
    NODE *pre=head,*result=head;
    if(!head){
        printf("the link is empty!\n");
        return NULL;
    }
    while(result){
        if(result->stdinfo.ID!=keyno){
            pre=result;
            result=result->next;
        }else
                break;
    }
    if(result){
        if(result==head){
                head=result->next;
        }else{
            pre->next=result->next;
        }
        free(result);
        (*p_n)--;
        printf("Delet is done!\n");
    }else{
        printf("No vip with ID %d!\n",keyno);
    }
    return head;
}

void vip_manage(){
    int choice;
    NODE *head=NULL,*tail=NULL;
    int n=0,max=1,keyno;
    int i=1;
    do{
        printf("enter 1:create vip\n");
        printf("enter 2:show vip\n");
        printf("enter 3:search vip\n");
        printf("enter 4:delect vip\n");
        printf("enter 0:break\n");
        fflush(stdin);
        scanf("%d",&choice);
        switch(choice){
            case 0:
                printf("bye");
                break;
            case 1:
                 if(head==NULL){
                    head=create_vip(&n,&max);
                    tail=head;
                 }
                 else{
                    tail=add_vip(tail,create_vip(&n,&max));
                 }
                 break;
             case 2:
                 show_vip(head);
                 break;
             case 3:
                 printf("enter a vip ID:");
                 scanf("%d",&keyno);
                 search_vip(head,keyno);
                 break;
             case 4:
                 printf("enter a vip ID:");
                 scanf("%d",&keyno);
                 head=delect_vip(head,keyno,&n);
                 break;
         }
    }while(i);
}

void staff_manage_init(void){
    SA[0].num = 001; SA[0].dp_num = 1; SA[0].serviceNum = 2;
	SA[1].num = 002; SA[1].dp_num = 1; SA[1].serviceNum = 2;
	SA[2].num = 003; SA[2].dp_num = 1; SA[2].serviceNum = 2;
	SA[3].num = 004; SA[3].dp_num = 1; SA[3].serviceNum = 2;
	SA[4].num = 005; SA[4].dp_num = 1; SA[4].serviceNum = 2;
	SA[5].num = 006; SA[5].dp_num = 1; SA[5].serviceNum = 2;
	SA[6].num = 007; SA[6].dp_num = 1; SA[6].serviceNum = 2;

}

staff *createnote(staff *head,staff *p){
      staff *ptr;
      ptr = (staff*)malloc(sizeof(staff));
      ptr=head;
      if(head!=NULL){
        if(ptr!=NULL){
            for(int i=0;i<H;i++){
                ptr->num=SA[i].num;
                ptr->dp_num=SA[i].dp_num;
                ptr->serviceNum=SA[i].serviceNum;
                ptr=ptr->next;
                if(ptr->next=NULL){
                    break;
                }
            }
        }
      }
      else if(ptr=NULL){
        ptr=head;
      }
      return head;
}
void push(staff* head){
      staff *newstaff=malloc(sizeof(staff));
      if(newstaff!=NULL){
        int num1,dp_num1,servicenum1;
         scanf("%d%d%d",&num1,&dp_num1,&servicenum1);
         newstaff->num=num1;
         newstaff->dp_num=dp_num1;
         newstaff->serviceNum=servicenum1;
         newstaff->next=head;
         head=newstaff;
         return head;
      }else{
         printf("error!your establishment fails!");
         return -1;
      }
}
int length(staff *head){
     int count=0;
     staff *current=head;
     while(current!=NULL){
        count++;
        current=current->next;
     }
     return(count);
}
staff* printfinforlist(staff *head){
       staff *current=head;
       int nodenumber;
       nodenumber=length(head);
       if(head!=NULL){
          for(int i=0;i<nodenumber;i++){
            printf("%d%d%d\n",current->num,current->dp_num,current->serviceNum);

            current=current->next;
            if(current==NULL){
                break;
            }
          }
       }
       return head;
}
void staff_manage(void){
    staff *head=NULL;
    staff_manage_init();
    int choice,result;
    scanf("%d",choice);
    printf("please input number(1-3)");
    printf("1:look up the initial information list");
    printf("2:add up staffs to the list");
    printf("3:look up the current information list");
    printf("\n");
    if(choice==1||choice==2||choice==3){
        do
            {switch(choice){
            case 1:
                printf("员工编号--------员工服务区域-----员工服务对象--------\n");
                printf("SA[0].num = 001 SA[0].dp_num = 1 SA[0].serviceNum = 2\n");
                printf("SA[1].num = 002 SA[1].dp_num = 1 SA[1].serviceNum = 2\n");
                printf("SA[2].num = 003 SA[2].dp_num = 1 SA[2].serviceNum = 2\n");
                printf("SA[3].num = 004 SA[3].dp_num = 1 SA[3].serviceNum = 2\n");
                printf("SA[4].num = 005 SA[4].dp_num = 1 SA[4].serviceNum = 2\n");
                printf("SA[5].num = 006 SA[5].dp_num = 1 SA[5].serviceNum = 2\n");
                printf("SA[6].num = 007 SA[6].dp_num = 1 SA[6].serviceNum = 2\n");
                break;
            case 2:
                push(head);
                break;
            case 3:
                printfinforlist(head);
                break;

        }}while(1);
    }
}

void exit(){
    printf("System is shutting down.\n");
}
