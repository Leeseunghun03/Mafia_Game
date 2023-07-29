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


void Rule(void); //��Ģ
void nextpage(int skip); //������ �ѱ�� �Լ�
int winorlose(Player* player, int people); //�¸����� �Ǻ� �Լ�
void reas(Player** player, int *people, int removewho); //��� ������ ���Ҵ� �Լ�



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
	printf("���Ǿ� ���ӿ� �� ���� ȯ���մϴ�!\n\n���� �����е��� ���Ǿ� ���� ��ȸ�ڸ� ���� ���α׷� �Դϴ�.\n\n");
	printf("���Ǿ� ������ ���� ���� ������ 1, ���� ������ ���Ͻø� 2�� �Է����ּ���\n\n==>");
	scanf("%d", &choose);
	if (choose == 1)
		Rule();
	else if (choose == 2)
		break;
	}

	while (1)
	{
		system("cls");
		printf("���ӿ� ������ �ο��� �Է����ּ���.(6��~10��)\n==>");
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

	printf("\n�ο�����ŭ �̸��� �Է����ּ���.\n\n");

	for (int i = 0; i < people; i++)
	{
		printf("\n\n�̸��� �Է����ּ���: ");
		scanf("%s", player[i].name);
		player[i].num = i + 1;
	}

	printf("\n������ ��� �ԷµǾ����ϴ�.\n\n");
	printf("���� �ܰ踦 �����Ͻ÷��� ���͸� �����ֽʽÿ�.");
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
						strcpy(player[i].job, "���Ǿ�");
						mafia--;
						break;
					}
				}
				else if (n == 1)
				{
					if (police > 0)
					{
						strcpy(player[i].job, "����");
						police--;
						break;
					}
				}
				else if (n == 2)
				{
					if (doctor > 0)
					{
						strcpy(player[i].job, "�ǻ�");
						doctor--;
						break;
					}
				}
				else if (n == 3)
				{
					if (citizen > 0)
					{
						strcpy(player[i].job, "�ù�");
						citizen--;
						break;
					}
				}
				else if (n == 4)
				{
					if (politician > 0)
					{
						strcpy(player[i].job, "��ġ��");
						politician--;
						break;
					}
				}
				else if (n == 5)
				{
					if (gang > 0)
					{
						strcpy(player[i].job, "����");
						gang--;
						break;
					}
				}

			}
	}
	
	printf("���� ������ �˷��帱 �����Դϴ�.\n\n�̸��� �Է��� ������� ���� �ܰ踦 �������ֽʽÿ�.\n\n'%s'�� ���� ���͸� �����ֽʽÿ�.(*ȥ�ڼ� ���� �մϴ�*)", player[0].name);
	nextpage(enter);
	for (int i = 0; i < people; i++)
	{
		printf("����� ��ȣ: %d\n����� �̸�: %s\n����� ����: %s\n\n", player[i].num, player[i].name, player[i].job);
		if (strcmp(player[i].job, "���Ǿ�") == 0)
		{
			printf("���Ǿ� ���\n==>");
			for (int p = 0; p < people; p++)
			{
				if (strcmp(player[p].job, "���Ǿ�") == 0)
				{
					printf("'%s'   ", player[p].name);
				}
			}
			printf("\n\n");
		}
		if (i == people - 1)
		{
			printf("���͸� ������ ���â�� �������ϴ�.\n");
		}
		else
		{
			printf("������ '%s'���� �����Դϴ�.\n\n���͸� ������ ���â�� �������ϴ�.\n", player[i + 1].name);
		}

		nextpage(enter);

		if (i != people - 1)
		{
			printf("����� '%s'���� �´ٸ� ���͸� ������ ������ Ȯ�����ּ���.", player[i + 1].name);
			nextpage(enter);
		}

	}

	printf("��� �����ڵ鿡�� ������ �˷���Ƚ��ϴ�.\n\n");













	int removewho;
	int turn = 0;

	while (1)
	{
		printf("���� �Ǿ����ϴ�.\n\n");
		if (turn != 0)
		{
			for (int i = 0; i < people; i++)
			{
				if (player[i].die == 1)
				{
					printf("���Ǿƴ� ���� ��'%s'�Կ��� ���� �����ϴ�.\n\n", player[i].name);
					if (player[i].heal == 1)
					{
						printf("������ �ǻ簡 '%s'���� ġ���Ͽ� '%s'���� ���� �ʾҽ��ϴ�.\n\n", player[i].name, player[i].name);
						player[i].heal = 0;
						player[i].die = 0;
					}
					else
					{
						printf("�ƽ��Ե� �ǻ�� '%s'���� ġ������ ���Ͽ� '%s'���� ����߽��ϴ�.\n\n", player[i].name, player[i].name);
						removewho = i;
						reas(&player, &people, removewho);
					}
				}
			}

			int ref = 0;
			ref=winorlose(player, people);
			if (ref == 1)
				break;
			printf("����Ϸ��� ���͸� �����ּ���");
			nextpage(enter);


		}

		printf("����� �������ֽʽÿ�.\n\n");
		printf("����� �����ٸ� ���͸� �����ֽʽÿ�.");
		nextpage(enter);
		printf("�׷� ��ǥ�� �����ϰڽ��ϴ�.\n\n");
		printf("�Ʊ�� ���� ������� ��ǥ�� ������ �ֽʽÿ�\n\n");
		printf("���͸� ������ ��ǥâ���� �Ѿ�ϴ�.");
		nextpage(enter);
		for (int i = 0; i < people; i++)
		{
			int who;
			printf("'%s'���� ��ǥ �����Դϴ�.\n\n���͸� �����ֽʽÿ�.", player[i].name);
			nextpage(enter);
			if (player[i].novote == 1)
			{
				printf("����� ���� ��ǥ���� ���п� ���� ��ǥ���� ��������ϴ�.\n\n");
			}
			else
			{
				for (int j = 0; j < people; j++)
				{
					printf("%d   %s\n", player[j].num, player[j].name);
				}
				printf("�������� ��ǥ�Ͻðڽ��ϱ�?\n\n��ȣ�� �Է����ֽʽÿ�: ");
				scanf("%d", &who);
				if (strcmp(player[i].job, "��ġ��") == 0)
					player[who - 1].vote = (player[who - 1].vote) + 2;
				else
					player[who - 1].vote++;
			}
			printf("\n\n���͸� �Է��Ͻø� �Է�â�� ������ϴ�.");
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
			printf("'%s'���� ���� ���� %dǥ�� �޾ҽ��ϴ�.\n\n", player[tmp2[0]].name, tmp1[0]);
			player[tmp2[0]].vote = 0;
			printf("������ ������ ���ֽʽÿ�.\n\n");
			printf("������ ������ ������ ����Ű�� �����ּ���.");
			nextpage(enter);
			printf("�׷� '%s'���� ó���� ���� ������ǥ�� �ϵ��� �ϰڽ��ϴ�.\n\n������� ��ǥ�� �� �ֽʽÿ�\n\n���͸� ������ ��ǥ�� �����ϰڽ��ϴ�.", player[tmp2[0]].name);
			nextpage(enter);


			for (int i = 0; i < people; i++)
			{
				if (i != tmp2[0])
				{
					if (player[i].novote == 1)
					{
						printf("'%s'�� �� ��ǥ�����Դϴ�.\n\n���͸� �����ֽʽÿ�", player[i].name);
						nextpage(enter);
						printf("����� �̹� �� ���п� ���� ��ǥ���� ��������ϴ�.\n\n");
						player[i].novote = 0;
					}
					else
					{
						printf("'%s'�� �� ��ǥ�����Դϴ�.\n\n���͸� �����ֽʽÿ�", player[i].name);
						nextpage(enter);
						printf("ó���� �����Ͻø� 1\nó���� �ݴ��Ͻø� 2\n==>");
						scanf("%d", &yn);
					}

					if (yn == 1)
					{
						if (strcmp(player[i].job, "��ġ��") == 0)
							y = y + 2;
						else
							y++;
					}
					else if (yn == 2)
					{
						if (strcmp(player[i].job, "��ġ��") == 0)
							n = n + 2;
						else
							n++;
					}
					else
					{
						printf("���͸� ������ �ٽ� ��ǥ���ֽʽÿ�.");
						i--;
					}
				}

				printf("\n���͸� �����ֽʽÿ�.");
				nextpage(enter);
			}

			for (int i = 0; i < people; i++)
			{
				if (player[i].novote == 1)
					player[i].novote = 0;
			}

			if (y > n)
			{
				printf("ó���� ����ǥ��%d, �ݴ�ǥ�� %d�̹Ƿ� ó���� �����ϰڽ��ϴ�.\n\n", y, n);
				if (strcmp(player[tmp2[0]].job, "��ġ��") == 0)
					printf("������ '%s'���� ��ġ���̶� ó�������� �ʾҽ��ϴ�!\n\n", player[tmp2[0]].name);
				else
				{
					printf("'%s'���� ó�����߽��ϴ�!\n\n", player[tmp2[0]].name);
				reas(&player, &people, tmp2[0]);
				}
			}
			else
			{
				printf("ó���� ����ǥ��%d, �ݴ�ǥ�� %d�̹Ƿ� ó���� �������� �ʰڽ��ϴ�.\n\n", y, n);
				printf("'%s'���� ó���� ���⿡�� ��Ƴ��ҽ��ϴ�!\n\n", player[tmp2[0]].name);
			}

			printf("���� �ܰ�� �����Ϸ��� ����Ű�� �����ֽʽÿ�.");
			nextpage(enter);
		}

		else
		{
			printf("���� ���� ǥ�� ���� ����� ������ �����ϴ�.\n\n");
			for (int i = 0; i <= count; i++)
			{
				printf("%s   %dǥ\n", player[tmp2[i]].name, tmp1[0]);
				player[tmp2[i]].vote = 0;
			}
			printf("������ �������Ƿ� ���� ������ �������� �ʽ��ϴ�.\n\n");
			printf("����Ϸ��� ���͸� �����ֽʽÿ�.");
			nextpage(enter);
		}


		printf("���� �Ǿ����ϴ�.\n\n���ݺ��� ���� ���� ���� �ɷ��� ����Ͻ� �� �ֽ��ϴ�.\n\n");
		printf("'%s'���� �ɷ��� ���� ��븦 ������ �ֽʽÿ�.\n\n���͸� ������ ��� ���� â���� �Ѿ�ϴ�.", player[0].name);
		nextpage(enter);

		int dielistcheck = 0; //��ġȮ��
		int dielist[5] = { 0, };
		int wheremafia[5] = { 0, };
		int a = 0; //���Ǿ� �ݺ�Ƚ�� Ȯ��
		for (int i = 0; i < people; i++)
		{
			int policewho, doctorwho, gangwho;
			printf("'%s'���� �����Դϴ�.\n\n'%s'���� �����ø� ���͸� �����ֽʽÿ�.", player[i].name, player[i].name);
			nextpage(enter);
			if (strcmp(player[i].job, "����") == 0)
			{
				for (int j = 0; j < people; j++)
				{
					printf("%d   %s\n", player[j].num, player[j].name);
				}
				printf("\n���� ���Ǿ����� �˾ƺ��ðڽ��ϱ�?\n==>");
				char buffer1;
				scanf("%d%c", &policewho, &buffer1);

				if (strcmp(player[policewho - 1].job, "���Ǿ�") == 0)
					printf("'%s'���� ���Ǿ� �Դϴ�!\n\n", player[policewho - 1].name);
				else
					printf("'%s'���� ���Ǿư� �ƴմϴ�.\n\n", player[policewho - 1].name);
				printf("Ȯ���ϼ����� ���͸� �����ּ���.");

			}

			if (strcmp(player[i].job, "�ǻ�") == 0)
			{
				for (int j = 0; j < people; j++)
				{
					printf("%d   %s\n", player[j].num, player[j].name);
				}
				printf("\n������ �츮�ðڽ��ϱ�?\n==>");
				scanf("%d", &doctorwho);
				player[doctorwho - 1].heal = 1;
			}

			if (strcmp(player[i].job, "���Ǿ�") == 0)
			{
				int mafiacount = 0, formafiacount = 0, whodie;
				for (int j = i; j < people; j++)
				{
					if (strcmp(player[j].job, "���Ǿ�") == 0)
					{
						formafiacount++; //������ �ִ� ���Ǿ��� ��
					}
				}
				int b = 0;
				for (int j = 0; j < people; j++)
				{

					if (strcmp(player[j].job, "���Ǿ�") == 0)
					{
						wheremafia[b] = j;
						b++;
					}
				}

				printf("���Ǿ� ���\n==>");
				for (int p = 0; p < people; p++)
				{
					if (strcmp(player[p].job, "���Ǿ�") == 0)
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

						printf("'%s'���� ���ϴ� �ϻ� Ÿ��: %d�� ������\n", player[wheremafia[u]].name, dielist[k]);
						u++;
					}
					printf("\n�ϻ��� ����� �����ֽʽÿ�\n==>");
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

						printf("'%s'���� ���ϴ� �ϻ� Ÿ��: %d�� ������\n", player[wheremafia[u]].name, dielist[k]);
						u++;
					}
					printf("\n�� ������ ���Ǿƿ��� ���ϴ� �ϻ� Ÿ���� ���ּ���.(��ȣ�� �Է����ּ���)\n==>");
					scanf("%d", &dielist[dielistcheck]);
					dielistcheck++;
				}

				a++; //���Ǿ� �ݺ�Ƚ�� ����

			}

			if (strcmp(player[i].job, "����") == 0)
			{
				for (int j = 0; j < people; j++)
				{
					printf("%d   %s\n", player[j].num, player[j].name);
				}
				printf("\n������ ��ǥ���� ���Ѱڽ��ϱ�?\n==>");
				scanf("%d", &gangwho);
				player[gangwho - 1].novote = 1;
			}

			if (strcmp(player[i].job, "�ù�") == 0)
			{
				printf("�ù��� ���� �ɷ��� �����ϴ�.\n\n");
			}

			if (strcmp(player[i].job, "��ġ��") == 0)
			{
				printf("��ġ���� �㿡 ����� �� �ִ� �����ɷ��� �����ϴ�.\n\n");
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
	printf("������ ���۵Ǹ� �����ڿ��� ������ �����˴ϴ�.\n\n");
	printf("���Ǿ� ������ ������ ��5���Դϴ�.\n\n����, �ǻ�, �ù�, ���Ǿ�, ��ġ��, ����\n\n");
	printf("������ �㸶�� ���縦 ���� �������� ������ �� �� �ֽ��ϴ�.\n\n");
	printf("�ǻ�� �㸶�� �������� �����Ͽ� �츱 �� �ֽ��ϴ�.\n\n");
	printf("�ù��� ���Ǿƿ� �븳�ϴ� �����̸� Ư���ɷ��� ������ ���Ǿ��� �����µ� �߿��� ������ ������ �ֽ��ϴ�\n\n");
	printf("���Ǿƴ� �ù���� �����ϰ� �븳�ϴ� ���迡 ������ �㸶�� �������� �����Ͽ� ���� �� �ֽ��ϴ�\n\n");
	printf("���Ǿƴ� �㿡 ���� ���� ���Ǿƿ��� �ϻ��� Ÿ���� ��õ�� �� �ֽ��ϴ�.\n\n");
	printf("������ �ϻ������� ������ ������ �ִ� ���Ǿư� ������ �ϰ� �˴ϴ�.\n\n");
	printf("��ġ���� ��ǥ�� ���� ���� �ʽ��ϴ�. ���� �ΰ��� ��ǥ���� �����ϴ�.\n\n");
	printf("���д� ����� ��ǥ���� ���� �� �ֽ��ϴ�.\n\n");
	printf("���п� ��ġ���� ���� �����ڰ� 6���϶��� �������� �ʽ��ϴ�.\n\n\n");
	printf("���͸� ������ ���������� �Ѿ�ϴ�.");
	scanf("%c", &enter);
	nextpage(enter);
	printf("������ ���� �߾��� �� �� �ְ� ���ǾƷ� �ǽɵǴ� ������� ��ǥ�� �մϴ�\n\n");
	printf("��ǥ�� ȥ����ǥ�� ����Ǹ� ���� ����� ���� ���� �� ����� ������ �ٽ� ������ǥ�� �����մϴ�.\n\n");
	printf("���� ���� ǥ�� ���� ����� ������ǥ�� �����ϱ� �� ������ �������� ������� �����ؾ� �մϴ�.\n\n");
	printf("���� ��ǥ�� ������ �Ǹ� ó���� �������� �ʽ��ϴ�.\n\n");
	printf("ó�� ��ǥ�� ������ ���� �Ǹ� ���ڰ� ������ �ִ� Ư���ɷ��� ����� �� �ֽ��ϴ�.\n\n");
	printf("�ù����� ���� ���Ǿ��� �� ���ϰ� �Ǹ� ������ ���Ǿ��� �¸��� �˴ϴ�.\n\n");
	printf("�ù����� ��� ���ǾƸ� ���̰� �Ǹ� ������ �ù��� �¸��� �˴ϴ�.\n\n\n");
	printf("����� ���ϴ�.\n\n");
	printf("���͸� ������ ó�� ȭ������ �Ѿ�ϴ�.");
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
		if (strcmp(player[i].job, "���Ǿ�") == 0)
		{
			mafiacount++; // ���Ǿ��� ��
		}
	}
	for (int i = 0; i < people; i++)
	{
		if (strcmp(player[i].job, "���Ǿ�") != 0)
		{
			citizencount++; // �ù��� ��
		}
	}

	if (mafiacount >= citizencount)
	{
		printf("�����մϴ�.\n\n���Ǿ����� �¸��߽��ϴ�!");
		ref = 1;
	}

	else if (mafiacount == 0)
	{
		printf("�����մϴ�.\n\n�ù����� �¸��߽��ϴ�!");
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
