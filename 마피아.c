#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct
{
	int num;
	char name[101];
	char job[11];
	int vote;
	int novote;
	int die;
	int heal;

}Player;


void Rule(void); //규칙
void nextpage(int skip); //페이지 넘기는 함수
int winorlose(Player* player, int people); //승리조건 판별 함수
void reas(Player** player, int *people, int removewho); //사람 죽으면 재할당 함수



int main(void)
{
	int choose, people;
	char enter = 0;
	int mafia=0, police=0, doctor=0, citizen=0, politician=0, gang=0;

	while(1)
	{
	printf("\n\n");
	printf("                         &&&&                                      &&&&                             &&&\n");
	printf("&&&&&&&&&&&&&&&&&&&      &&&&         &&&&&&&&&&&&&&&&&&&&&&       &&&&         &&&&&&&&&&&&&&      &&&\n");
	printf("&&&&&&&&&&&&&&&&&&&      &&&&         &&&&&&&&&&&&&&&&&&&&&&       &&&&       &&              &&    &&&\n");
	printf("&&&             &&&      &&&&             &&&         &&&          &&&&      &&                &&   &&&\n");
	printf("&&&             &&&      &&&&&&&&         &&&         &&&          &&&&      &&                &&   &&&&&&&\n");
	printf("&&&             &&&      &&&&&&&&         &&&         &&&          &&&&      &&                &&   &&&&&&&\n");
	printf("&&&             &&&      &&&&             &&&         &&&          &&&&       &&              &&    &&&\n");
	printf("&&&&&&&&&&&&&&&&&&&      &&&&         &&&&&&&&&&&&&&&&&&&&&&       &&&&         &&&&&&&&&&&&&&      &&&\n");
	printf("&&&&&&&&&&&&&&&&&&&      &&&&         &&&&&&&&&&&&&&&&&&&&&&       &&&&                             &&&\n");
	printf("                         &&&&                                      &&&&                             &&&\n\n");
	printf("마피아 게임에 온 것을 환영합니다!\n\n저는 여러분들의 마피아 게임 사회자를 맡은 프로그램 입니다.\n\n");
	printf("마피아 게임의 룰을 보고 싶으면 1, 게임 시작을 원하시면 2를 입력해주세요\n\n==>");
	scanf("%d", &choose);
	if (choose == 1)
		Rule();
	else if (choose == 2)
		break;
	}

	while (1)
	{
		system("cls");
		printf("게임에 참가할 인원을 입력해주세요.(6명~10명)\n==>");
		scanf("%d", &people);

		if (people == 6)
		{
			mafia = 2, police = 1, doctor = 1, citizen = 2;
			break;
		}
		else if (people == 7)
		{
			mafia = 2, police = 1, doctor = 1, citizen = 1, politician = 1, gang = 1;
			break;
		}
		else if (people == 8)
		{
			mafia = 3, police = 1, doctor = 1, citizen = 1, politician = 1, gang = 1;
			break;
		}
		else if (people == 9)
		{
			mafia = 3, police = 1, doctor = 1, citizen = 2, politician = 1, gang = 1;
			break;
		}
		else if (people == 10)
		{
			mafia = 4, police = 1, doctor = 1, citizen = 2, politician = 1, gang = 1;
			break;
		}
	}

	Player* player = (Player*)malloc(sizeof(Player) * people);
	for (int i = 0; i < people; i++)
	{
		player[i].vote = 0;
	}

	for (int i = 0; i < people; i++)
	{
		player[i].novote = 0;
	}

	for (int i = 0; i < people; i++)
	{
		player[i].die = 0;
	}

	for (int i = 0; i < people; i++)
	{
		player[i].heal = 0;
	}

	printf("\n인원수만큼 이름을 입력해주세요.\n\n");

	for (int i = 0; i < people; i++)
	{
		printf("\n\n이름을 입력해주세요: ");
		scanf("%s", player[i].name);
		player[i].num = i + 1;
	}

	printf("\n정보가 모두 입력되었습니다.\n\n");
	printf("다음 단계를 진행하시려면 엔터를 눌러주십시오.");
	scanf("%c", &enter);
	nextpage(enter);

	srand(time(NULL));

	int* jobnum = (int*)malloc(sizeof(int) * (people + 1));

	for (int i=0; i<people; i++)
	{
			while (1)
			{
				int n = rand() % 6;
				if (n == 0)
				{
					if (mafia > 0)
					{
						strcpy(player[i].job, "마피아");
						mafia--;
						break;
					}
				}
				else if (n == 1)
				{
					if (police > 0)
					{
						strcpy(player[i].job, "경찰");
						police--;
						break;
					}
				}
				else if (n == 2)
				{
					if (doctor > 0)
					{
						strcpy(player[i].job, "의사");
						doctor--;
						break;
					}
				}
				else if (n == 3)
				{
					if (citizen > 0)
					{
						strcpy(player[i].job, "시민");
						citizen--;
						break;
					}
				}
				else if (n == 4)
				{
					if (politician > 0)
					{
						strcpy(player[i].job, "정치인");
						politician--;
						break;
					}
				}
				else if (n == 5)
				{
					if (gang > 0)
					{
						strcpy(player[i].job, "깡패");
						gang--;
						break;
					}
				}

			}
	}
	
	printf("제가 직업을 알려드릴 차례입니다.\n\n이름을 입력한 순서대로 다음 단계를 진행해주십시오.\n\n'%s'님 먼저 엔터를 눌러주십시오.(*혼자서 봐야 합니다*)", player[0].name);
	nextpage(enter);
	for (int i = 0; i < people; i++)
	{
		printf("당신의 번호: %d\n당신의 이름: %s\n당신의 직업: %s\n\n", player[i].num, player[i].name, player[i].job);
		if (strcmp(player[i].job, "마피아") == 0)
		{
			printf("마피아 명단\n==>");
			for (int p = 0; p < people; p++)
			{
				if (strcmp(player[p].job, "마피아") == 0)
				{
					printf("'%s'   ", player[p].name);
				}
			}
			printf("\n\n");
		}
		if (i == people - 1)
		{
			printf("엔터를 누르면 출력창이 지워집니다.\n");
		}
		else
		{
			printf("다음은 '%s'님의 차례입니다.\n\n엔터를 누르면 출력창이 지워집니다.\n", player[i + 1].name);
		}

		nextpage(enter);

		if (i != people - 1)
		{
			printf("당신이 '%s'님이 맞다면 엔터를 누르고 직업을 확인해주세요.", player[i + 1].name);
			nextpage(enter);
		}

	}

	printf("모든 참가자들에게 직업을 알려드렸습니다.\n\n");













	int removewho;
	int turn = 0;

	while (1)
	{
		printf("낮이 되었습니다.\n\n");
		if (turn != 0)
		{
			for (int i = 0; i < people; i++)
			{
				if (player[i].die == 1)
				{
					printf("마피아는 지난 밤'%s'님에게 총을 쐈습니다.\n\n", player[i].name);
					if (player[i].heal == 1)
					{
						printf("하지만 의사가 '%s'님을 치료하여 '%s'님은 죽지 않았습니다.\n\n", player[i].name, player[i].name);
						player[i].heal = 0;
						player[i].die = 0;
					}
					else
					{
						printf("아쉽게도 의사는 '%s'님을 치료하지 못하여 '%s'님은 사망했습니다.\n\n", player[i].name, player[i].name);
						removewho = i;
						reas(&player, &people, removewho);
					}
				}
			}

			int ref = 0;
			ref=winorlose(player, people);
			if (ref == 1)
				break;
			printf("계속하려면 엔터를 눌러주세요");
			nextpage(enter);


		}

		printf("토론을 시작해주십시오.\n\n");
		printf("토론이 끝났다면 엔터를 눌러주십시오.");
		nextpage(enter);
		printf("그럼 투표를 시작하겠습니다.\n\n");
		printf("아까와 같이 순서대로 투표를 시작해 주십시오\n\n");
		printf("엔터를 누르면 투표창으로 넘어갑니다.");
		nextpage(enter);
		for (int i = 0; i < people; i++)
		{
			int who;
			printf("'%s'님의 투표 차례입니다.\n\n엔터를 눌러주십시오.", player[i].name);
			nextpage(enter);
			if (player[i].novote == 1)
			{
				printf("당신의 오늘 투표권은 깡패에 의해 투표권이 사라졌습니다.\n\n");
			}
			else
			{
				for (int j = 0; j < people; j++)
				{
					printf("%d   %s\n", player[j].num, player[j].name);
				}
				printf("누구에게 투표하시겠습니까?\n\n번호를 입력해주십시오: ");
				scanf("%d", &who);
				if (strcmp(player[i].job, "정치인") == 0)
					player[who - 1].vote = (player[who - 1].vote) + 2;
				else
					player[who - 1].vote++;
			}
			printf("\n\n엔터를 입력하시면 입력창이 사라집니다.");
			nextpage(enter);
		}

		int* tmp1 = (int*)malloc(sizeof(int) * (people + 1));
		int* tmp2 = (int*)malloc(sizeof(int) * (people + 1));
		int retmp1, retmp2;
		for (int i = 0; i < people; i++)
		{
			tmp1[i] = player[i].vote;
		}
		for (int i = 0; i < people; i++)
		{
			tmp2[i] = (player[i].num) - 1;
		}

		for (int i = 0; i < people - 1; i++)
		{
			for (int j = i + 1; j < people; j++)
			{
				if (tmp1[i] < tmp1[j])
				{
					retmp2 = tmp2[i];
					retmp1 = tmp1[i];
					tmp2[i] = tmp2[j];
					tmp1[i] = tmp1[j];
					tmp2[j] = retmp2;
					tmp1[j] = retmp1;
				}
			}
		}

		int count = 0;
		for (int i = 1; i < people; i++)
		{
			if (tmp1[0] == tmp1[i])
			{
				count++;
			}
		}

		if (count == 0)
		{
			int yn = 0, y = 0, n = 0;
			printf("'%s'님이 가장 많은 %d표를 받았습니다.\n\n", player[tmp2[0]].name, tmp1[0]);
			player[tmp2[0]].vote = 0;
			printf("최후의 변론을 해주십시오.\n\n");
			printf("최후의 변론이 끝나면 엔터키를 눌러주세요.");
			nextpage(enter);
			printf("그럼 '%s'님의 처형에 대해 찬반투표를 하도록 하겠습니다.\n\n순서대로 투표를 해 주십시오\n\n엔터를 누르면 투표를 진행하겠습니다.", player[tmp2[0]].name);
			nextpage(enter);


			for (int i = 0; i < people; i++)
			{
				if (i != tmp2[0])
				{
					if (player[i].novote == 1)
					{
						printf("'%s'님 의 투표차례입니다.\n\n엔터를 눌러주십시오", player[i].name);
						nextpage(enter);
						printf("당신은 이번 밤 깡패에 의해 투표권이 사라졌습니다.\n\n");
						player[i].novote = 0;
					}
					else
					{
						printf("'%s'님 의 투표차례입니다.\n\n엔터를 눌러주십시오", player[i].name);
						nextpage(enter);
						printf("처형에 찬성하시면 1\n처형에 반대하시면 2\n==>");
						scanf("%d", &yn);
					}

					if (yn == 1)
					{
						if (strcmp(player[i].job, "정치인") == 0)
							y = y + 2;
						else
							y++;
					}
					else if (yn == 2)
					{
						if (strcmp(player[i].job, "정치인") == 0)
							n = n + 2;
						else
							n++;
					}
					else
					{
						printf("엔터를 누르고 다시 투표해주십시오.");
						i--;
					}
				}

				printf("\n엔터를 눌러주십시오.");
				nextpage(enter);
			}

			for (int i = 0; i < people; i++)
			{
				if (player[i].novote == 1)
					player[i].novote = 0;
			}

			if (y > n)
			{
				printf("처형의 찬성표가%d, 반대표가 %d이므로 처형을 진행하겠습니다.\n\n", y, n);
				if (strcmp(player[tmp2[0]].job, "정치인") == 0)
					printf("하지만 '%s'님은 정치인이라 처형당하지 않았습니다!\n\n", player[tmp2[0]].name);
				else
				{
					printf("'%s'님이 처형당했습니다!\n\n", player[tmp2[0]].name);
				reas(&player, &people, tmp2[0]);
				}
			}
			else
			{
				printf("처형의 찬성표가%d, 반대표가 %d이므로 처형을 진행하지 않겠습니다.\n\n", y, n);
				printf("'%s'님이 처형의 위기에서 살아남았습니다!\n\n", player[tmp2[0]].name);
			}

			printf("다음 단계로 진행하려면 엔터키를 눌러주십시오.");
			nextpage(enter);
		}

		else
		{
			printf("가장 많은 표를 받은 사람은 다음과 같습니다.\n\n");
			for (int i = 0; i <= count; i++)
			{
				printf("%s   %d표\n", player[tmp2[i]].name, tmp1[0]);
				player[tmp2[i]].vote = 0;
			}
			printf("동률이 나왔으므로 오늘 사형은 집행하지 않습니다.\n\n");
			printf("계속하려면 엔터를 눌러주십시오.");
			nextpage(enter);
		}


		printf("밤이 되었습니다.\n\n지금부터 각자 가진 고유 능력을 사용하실 수 있습니다.\n\n");
		printf("'%s'부터 능력을 쓰실 상대를 지정해 주십시오.\n\n엔터를 누르면 대상 지정 창으로 넘어갑니다.", player[0].name);
		nextpage(enter);

		int dielistcheck = 0; //위치확인
		int dielist[5] = { 0, };
		int wheremafia[5] = { 0, };
		int a = 0; //마피아 반복횟수 확인
		for (int i = 0; i < people; i++)
		{
			int policewho, doctorwho, gangwho;
			printf("'%s'님의 차례입니다.\n\n'%s'님이 맞으시면 엔터를 눌러주십시오.", player[i].name, player[i].name);
			nextpage(enter);
			if (strcmp(player[i].job, "경찰") == 0)
			{
				for (int j = 0; j < people; j++)
				{
					printf("%d   %s\n", player[j].num, player[j].name);
				}
				printf("\n누가 마피아인지 알아보시겠습니까?\n==>");
				char buffer1;
				scanf("%d%c", &policewho, &buffer1);

				if (strcmp(player[policewho - 1].job, "마피아") == 0)
					printf("'%s'님은 마피아 입니다!\n\n", player[policewho - 1].name);
				else
					printf("'%s'님은 마피아가 아닙니다.\n\n", player[policewho - 1].name);
				printf("확인하셨으면 엔터를 눌러주세요.");

			}

			if (strcmp(player[i].job, "의사") == 0)
			{
				for (int j = 0; j < people; j++)
				{
					printf("%d   %s\n", player[j].num, player[j].name);
				}
				printf("\n누구를 살리시겠습니까?\n==>");
				scanf("%d", &doctorwho);
				player[doctorwho - 1].heal = 1;
			}

			if (strcmp(player[i].job, "마피아") == 0)
			{
				int mafiacount = 0, formafiacount = 0, whodie;
				for (int j = i; j < people; j++)
				{
					if (strcmp(player[j].job, "마피아") == 0)
					{
						formafiacount++; //앞으로 있는 마피아의 수
					}
				}
				int b = 0;
				for (int j = 0; j < people; j++)
				{

					if (strcmp(player[j].job, "마피아") == 0)
					{
						wheremafia[b] = j;
						b++;
					}
				}

				printf("마피아 명단\n==>");
				for (int p = 0; p < people; p++)
				{
					if (strcmp(player[p].job, "마피아") == 0)
					{
						printf("'%s'   ", player[p].name);
					}
				}

				if (formafiacount == 1)
				{
					printf("\n\n");
					for (int j = 0; j < people; j++)
					{
						printf("%d   %s\n", (player[j].num), player[j].name);
					}

					int u = 0;

					for (int k = 0; k < a; k++)
					{

						printf("'%s'님이 원하는 암살 타겟: %d번 참가자\n", player[wheremafia[u]].name, dielist[k]);
						u++;
					}
					printf("\n암살할 사람을 정해주십시오\n==>");
					scanf("%d", &whodie);
					player[whodie - 1].die = 1;

				}

				else if (formafiacount > 1)
				{
					printf("\n\n");
					for (int j = 0; j < people; j++)
					{
						printf("%d   %s\n", (player[j].num), player[j].name);
					}

					int u = 0;

					for (int k = 0; k < a; k++)
					{

						printf("'%s'님이 원하는 암살 타겟: %d번 참가자\n", player[wheremafia[u]].name, dielist[k]);
						u++;
					}
					printf("\n뒷 차례의 마피아에게 원하는 암살 타겟을 써주세요.(번호를 입력해주세요)\n==>");
					scanf("%d", &dielist[dielistcheck]);
					dielistcheck++;
				}

				a++; //마피아 반복횟수 세기

			}

			if (strcmp(player[i].job, "깡패") == 0)
			{
				for (int j = 0; j < people; j++)
				{
					printf("%d   %s\n", player[j].num, player[j].name);
				}
				printf("\n누구의 투표권을 빼앗겠습니까?\n==>");
				scanf("%d", &gangwho);
				player[gangwho - 1].novote = 1;
			}

			if (strcmp(player[i].job, "시민") == 0)
			{
				printf("시민은 고유 능력이 없습니다.\n\n");
			}

			if (strcmp(player[i].job, "정치인") == 0)
			{
				printf("정치인은 밤에 사용할 수 있는 고유능력은 없습니다.\n\n");
			}

			nextpage(enter);

		}

		turn++;

	}
	
	return 0;
}


void Rule(void)
{
	system("cls");
	int i = 0;
	char enter;
	printf("게임이 시작되면 참여자에게 직업이 배정됩니다.\n\n");
	printf("마피아 게임의 직업은 총5개입니다.\n\n경찰, 의사, 시민, 마피아, 정치인, 깡패\n\n");
	printf("경찰은 밤마다 수사를 통해 누군가의 직업을 알 수 있습니다.\n\n");
	printf("의사는 밤마다 누군가를 지정하여 살릴 수 있습니다.\n\n");
	printf("시민은 마피아와 대립하는 집단이며 특수능력은 없지만 마피아을 밝히는데 중요한 역할을 가지고 있습니다\n\n");
	printf("마피아는 시민편과 유일하게 대립하는 관계에 있으며 밤마다 누군가를 지목하여 죽일 수 있습니다\n\n");
	printf("마피아는 밤에 같은 편인 마피아에게 암살할 타겟을 추천할 수 있습니다.\n\n");
	printf("누구를 암살할지는 마지막 순서에 있는 마피아가 결정을 하게 됩니다.\n\n");
	printf("정치인은 투표를 통해 죽지 않습니다. 또한 두개의 투표권을 가집니다.\n\n");
	printf("깡패는 상대의 투표권을 없앨 수 있습니다.\n\n");
	printf("깡패와 정치인은 게임 참가자가 6명일때는 존재하지 않습니다.\n\n\n");
	printf("엔터를 누르면 다음장으로 넘어갑니다.");
	scanf("%c", &enter);
	nextpage(enter);
	printf("낮에는 각자 발언을 할 수 있고 마피아로 의심되는 사람에게 투표를 합니다\n\n");
	printf("투표는 혼합투표로 진행되며 죽일 사람을 뽐은 다음 그 사람을 죽일지 다시 찬반투표를 진행합니다.\n\n");
	printf("가장 많은 표를 받은 사람은 찬반투표를 진행하기 전 최후의 변론으로 사람들을 설득해야 합니다.\n\n");
	printf("만약 투표가 동률이 되면 처형은 진행하지 않습니다.\n\n");
	printf("처형 투표가 끝나고 밤이 되면 각자가 가지고 있는 특수능력을 사용할 수 있습니다.\n\n");
	printf("시민편의 수가 마피아의 수 이하가 되면 게임은 마피아의 승리가 됩니다.\n\n");
	printf("시민편이 모든 마피아를 죽이게 되면 게임은 시민의 승리가 됩니다.\n\n\n");
	printf("행운을 빕니다.\n\n");
	printf("엔터를 누르면 처음 화면으로 넘어갑니다.");
	nextpage(enter);

}

void reas(Player** player, int* people, int removewho)
{
	for (int j = removewho; j < (*people); j++)
	{
		(*player)[j] = (*player)[j + 1];
	}

	(*people)--;
	(*player) = (Player*)realloc((*player), sizeof(Player) * (*people));

	for (int i = 0; i < (*people); i++)
	{
		(*player)[i].num = i + 1;
	}
}

int winorlose(Player* player, int people)
{
	int ref = 0;
	int mafiacount = 0, citizencount=0;
	for (int i = 0; i < people; i++)
	{
		if (strcmp(player[i].job, "마피아") == 0)
		{
			mafiacount++; // 마피아의 수
		}
	}
	for (int i = 0; i < people; i++)
	{
		if (strcmp(player[i].job, "마피아") != 0)
		{
			citizencount++; // 시민의 수
		}
	}

	if (mafiacount >= citizencount)
	{
		printf("축하합니다.\n\n마피아팀이 승리했습니다!");
		ref = 1;
	}

	else if (mafiacount == 0)
	{
		printf("축하합니다.\n\n시민팀이 승리했습니다!");
		ref = 1;
	}

	return ref;
}

void nextpage(int skip)
{
	char next;
	if (skip == '\n')
	scanf("%c", &next);
	fflush(stdin);
	system("cls");
}
