#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void display_table(int round, char user_card, char cpu_card, int pot, int user_points, int cpu_points, bool showdown);
void play_round(int round, int* user_points, int* cpu_points);
void shuffle_cards(char* card1, char* card2, char* card3);
int card_value(char card);
void menu();
void print_rules();
void print_points(int points);
int cpu(char user_card, char cpu_card, bool bet);

int main(void) {
  // Deterministic, yes, but you never specified _which_ random
  srand(0);
  menu();
  return 0;
}

void display_table(int round, char user_card, char cpu_card, int pot, int user_points, int cpu_points, bool showdown) {
  printf("==============================\n");
  printf("| 경기 횟수: %-16d|\n", round);
  printf("==============================\n");
  printf("|      USER의 카드: %c        |\n", user_card);
  printf("|       CPU의 카드: %c        |\n", showdown ? cpu_card : '?');
  printf("------------------------------\n");
  printf("|            팟: "); print_points(pot); printf("    |\n");
  printf("------------------------------\n");
  printf("| USER의 포인트: "); print_points(user_points); printf("    |\n");
  printf("|  CPU의 포인트: "); print_points(cpu_points); printf("    |\n");
  printf("------------------------------\n");
}
void play_round(int round, int* user_points, int *cpu_points) {
  char user_card, cpu_card, table;
  int pot = 0;
  shuffle_cards(&user_card, &cpu_card, &table);
  system("clear");
  display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
  printf("경기 %d을(를) 시작합니다.\n", round);
  printf("\nc를 눌러서 진행합니다: ");
  while (getchar() != 'c' || getchar() != '\n') {
    while (getchar() != '\n');
    printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
    printf("\nc를 눌러서 진행합니다: ");
  }

  *user_points -= 1, *cpu_points -= 1, pot += 2;
  bool bet = false;
  int passes = 0;
  while (passes < 2) {
    system("clear");
    display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
    int ch;
    if (*user_points) {
      if (bet)
        printf("[USER] 1 포인트를 콜하거나 폴드합니다. (0: 콜, 1: 폴드): ");
      else
        printf("[USER] 체크하거나 1 포인트를 베트합니다. (0: 체크, 1: 베트): ");
      while ((unsigned) (ch = getchar()) - '0' >= 2 || getchar() != '\n') {
        while (getchar() != '\n');
        system("clear");
        display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
        printf("올바르지 않은 입력입니다. 다시 입력해주세요\n");
        if (bet)
          printf("[USER] 1 포인트를 콜하거나 폴드합니다. (0: 콜, 1: 폴드): ");
        else
          printf("[USER] 체크하거나 1 포인트를 베트합니다. (0: 체크, 1: 베트): ");
      }
    } else {
      if (bet) {
        printf("[USER] 포인트 부족으로 인해 USER는 콜할 수 없습니다. 자동으로 폴드합니다.\n");
        ch = '1';
      } else {
        printf("[USER] 포인트 부족으로 인해 USER는 베트할 수 없습니다. 자동으로 체크합니다.\n");
        ch = '0';
      }
    }
    printf("\nc를 눌러서 진행합니다: ");
    while (getchar() != 'c' || getchar() != '\n') {
      while (getchar() != '\n');
      printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
      printf("\nc를 눌러서 진행합니다: ");
    }
    if (bet)
      switch (ch) {
        case '0':
          *user_points -= 1, pot += 1, bet = false, passes += 1;
          system("clear");
          display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
          printf("[USER] 1 포인트를 콜했습니다. 이제 팟은 %d 포인트입니다.\n", pot);
          break;
        case '1':
          *cpu_points += pot;
          system("clear");
          display_table(round, user_card, cpu_card, 0, *user_points, *cpu_points, true);
          printf("[폴드] CPU가 %d 포인트의 팟을 차지합니다.\n", pot);
          printf("경기 %d의 결과로 USER는 %d 포인트, CPU는 %d 포인트를 가지게 되었습니다.\n",
            round, *user_points, *cpu_points);
          printf("\nc를 눌러서 진행합니다: ");
          while (getchar() != 'c' || getchar() != '\n') {
            while (getchar() != '\n');
            printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
            printf("\nc를 눌러서 진행합니다: ");
          }
          return;
      }
    else
      switch (ch) {
        case '0':
          passes += 1;
          system("clear");
          display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
          printf("[USER] 체크합니다.\n");
          break;
        case '1':
          *user_points -= 1, pot += 1, bet = true, passes = 1;
          system("clear");
          display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
          printf("[USER] 1 포인트를 베트했습니다. 이제 팟은 %d 포인트입니다.\n", pot);
          break;
      }
    printf("\nc를 눌러서 진행합니다: ");
    while (getchar() != 'c' || getchar() != '\n') {
      while (getchar() != '\n');
      printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
      printf("\nc를 눌러서 진행합니다: ");
    }

    system("clear");
    display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
    if (*cpu_points)
      ch = cpu(user_card, cpu_card, bet);
    else {
      if (bet) {
        printf("[CPU] 포인트 부족으로 인해 CPU는 콜할 수 없습니다. 자동으로 폴드합니다.\n");
        ch = '1';
      } else {
        printf("[CPU] 포인트 부족으로 인해 CPU는 베트할 수 없습니다. 자동으로 체크합니다.\n");
        ch = '0';
      }
    }
    if (bet)
      switch (ch) {
        case '0':
          printf("[CPU] CPU는 콜하기로 결정했습니다.\n");
          printf("\nc를 눌러서 진행합니다: ");
          while (getchar() != 'c' || getchar() != '\n') {
            while (getchar() != '\n');
            printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
            printf("\nc를 눌러서 진행합니다: ");
          }
          *cpu_points -= 1, pot += 1, bet = false, passes += 1;
          system("clear");
          display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
          printf("[CPU] 1 포인트를 콜했습니다. 이제 팟은 %d 포인트입니다.\n", pot);
          break;
        case '1':
          printf("[CPU] CPU는 폴드하기로 결정했습니다.\n");
          printf("\nc를 눌러서 진행합니다: ");
          while (getchar() != 'c' || getchar() != '\n') {
            while (getchar() != '\n');
            printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
            printf("\nc를 눌러서 진행합니다: ");
          }
          *user_points += pot;
          system("clear");
          display_table(round, user_card, cpu_card, 0, *user_points, *cpu_points, true);
          printf("[폴드] USER가 %d 포인트의 팟을 차지합니다.\n", pot);
          printf("경기 %d의 결과로 USER는 %d 포인트, CPU는 %d 포인트를 가지게 되었습니다.\n",
            round, *user_points, *cpu_points);
          printf("\nc를 눌러서 진행합니다: ");
          while (getchar() != 'c' || getchar() != '\n') {
            while (getchar() != '\n');
            printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
            printf("\nc를 눌러서 진행합니다: ");
          }
          return;
      }
    else
      switch (ch) {
        case '0':
          printf("[CPU] CPU는 체크하기로 결정했습니다.\n");
          printf("\nc를 눌러서 진행합니다: ");
          while (getchar() != 'c' || getchar() != '\n') {
            while (getchar() != '\n');
            printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
            printf("\nc를 눌러서 진행합니다: ");
          }
          passes += 1;
          system("clear");
          display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
          printf("[CPU] 체크합니다.\n");
          break;
        case '1':
          printf("[CPU] CPU는 베트하기로 결정했습니다.\n");
          printf("\nc를 눌러서 진행합니다: ");
          while (getchar() != 'c' || getchar() != '\n') {
            while (getchar() != '\n');
            printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
            printf("\nc를 눌러서 진행합니다: ");
          }
          *cpu_points -= 1, pot += 1, bet = true, passes = 1;
          system("clear");
          display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
          printf("[CPU] 1 포인트를 베트했습니다. 이제 팟은 %d 포인트입니다.\n", pot);
          break;
      }
    printf("\nc를 눌러서 진행합니다: ");
    while (getchar() != 'c' || getchar() != '\n') {
      while (getchar() != '\n');
      printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
      printf("\nc를 눌러서 진행합니다: ");
    }
  }

  system("clear");
  display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, true);
  printf("[쇼다운] 카드를 공개합니다.\n");
  printf("\nc를 눌러서 진행합니다: ");
  while (getchar() != 'c' || getchar() != '\n') {
    while (getchar() != '\n');
    printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
    printf("\nc를 눌러서 진행합니다: ");
  }
  if (card_value(user_card) > card_value(cpu_card)) {
    *user_points += pot;
    system("clear");
    display_table(round, user_card, cpu_card, 0, *user_points, *cpu_points, true);
    printf("[경기 결과] USER가 %d 포인트의 팟을 차지합니다.\n", pot);
  } else {
    *cpu_points += pot;
    system("clear");
    display_table(round, user_card, cpu_card, 0, *user_points, *cpu_points, true);
    printf("[경기 결과] CPU가 %d 포인트의 팟을 차지합니다.\n", pot);
  }
  printf("경기 %d의 결과로 USER는 %d 포인트, CPU는 %d 포인트를 가지게 되었습니다.\n",
    round, *user_points, *cpu_points);
  printf("\nc를 눌러서 진행합니다: ");
  while (getchar() != 'c' || getchar() != '\n') {
    while (getchar() != '\n');
    printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
    printf("\nc를 눌러서 진행합니다: ");
  }
}
void shuffle_cards(char* card1, char* card2, char* card3) {
  switch (rand() % 6) {
    case 0:
      *card1 = 'K', *card2 = 'Q', *card3 = 'J';
      break;
    case 1:
      *card1 = 'K', *card2 = 'J', *card3 = 'Q';
      break;
    case 2:
      *card1 = 'Q', *card2 = 'K', *card3 = 'J';
      break;
    case 3:
      *card1 = 'Q', *card2 = 'J', *card3 = 'K';
      break;
    case 4:
      *card1 = 'J', *card2 = 'K', *card3 = 'Q';
      break;
    case 5:
      *card1 = 'J', *card2 = 'Q', *card3 = 'K';
      break;
  }
}
int card_value(char card) {
  switch (card) {
    case 'K':
      return 2;
    case 'Q':
      return 1;
    case 'J':
      return 0;
  }
}
void menu() {
  while (true) {
    printf("[쿤 포커 (Kuhn Poker)]\n");
    printf("1. 규칙 출력\n");
    printf("2. 게임 시작\n");
    printf("3. 게임 종료\n");
    printf("선택지를 입력합니다: ");
    int ch;
    while ((unsigned) (ch = getchar()) -  '1' >= 3 || getchar() != '\n') {
      while (getchar() != '\n');
      system("clear");
      printf("올바르지 않은 입력입니다. 다시 입력해주세요.\n");
      printf("\n");
      printf("[쿤 포커 (Kuhn Poker)]\n");
      printf("1. 규칙 출력\n");
      printf("2. 게임 시작\n");
      printf("3. 게임 종료\n");
      printf("선택지를 입력합니다: ");
    }
    switch (ch) {
      case '1':
        system("clear");
        print_rules();
        printf("r을 누르면 메인 메뉴로 돌아갑니다: ");
        while (getchar() != 'r' || getchar() != '\n') {
          while (getchar() != '\n');
          printf("올바르지 않은 입력입니다. r을 눌러야 메인 메뉴로 돌아갑니다: ");
        }
        break;
      case '2':
        int round = 0, user_points = 4, cpu_points = 4;
        do play_round(++round, &user_points, &cpu_points);
          while (user_points > 0 && cpu_points > 0);
        system("clear");
        printf("%s의 포인트가 소진되었습니다. %s가 승리했습니다.\n",
          user_points ? "CPU" : "USER", user_points ? "USER" : "CPU");
        printf("메인 화면으로 돌아갑니다.\n\n");
        break;
      case '3':
        printf("게임을 종료합니다.\n");
        return;
    }
  }
}
void print_rules() {
  printf("=============================\n");
  printf("| 쿤 포커 (Kuhn Poker) 규칙 |\n");
  printf("=============================\n");
  printf("\n");
  printf(" 1. 플레이어들은 각자 4 포인트를 소지한 상태로 게임을 시작합니다.\n");
  printf(" 2. 게임은 여러 번의 경기로 구성됩니다.\n");
  printf(" 3. 가지고 있는 포인트를 음수로 만드는 선택은 허용하지 않습니다.\n");
  printf(" 4. 플레이어 둘 중 한 명이 더 이상 앤티를 지불할 수 없을 때까지 경기를 반복합니다.\n");
  printf(" 5. 앤티를 지불할 수 없는 플레이어는 게임을 패배합니다.\n");
  printf(" 6. 경기는 팟이 0인 상태에서 각 플레이어가 1 포인트의 앤티를 베트하는 것으로 시작합니다.\n");
  printf(" 7. 이후 각 플레이어는 세 장의 카드 중 한 장을 받습니다. 남은 한 장은 공개하지 않습니다.\n");
  printf(" 8. 첫 번째 플레이어는 체크하거나 1 포인트를 베트할 수 있습니다.\n");
  printf(" 9. 어느 한쪽이 체크를 하면 상대방은 체크하거나 1 포인트를 베트할 수 있습니다.\n");
  printf("10. 두 플레이어가 모두 체크하면, 더 높은 카드를 가진 플레이어가 팟을 가져갑니다.\n");
  printf("11. 어느 한쪽이 베트하면 상대방은 콜하거나 폴드할 수 있습니다.\n");
  printf("12. 상대방이 폴드하면 베팅한 플레이어가 팟을 가져갑니다.\n");
  printf("13. 상대방이 콜하면 쇼다운이 이루어지며, 더 높은 카드를 가진 플레이어가 팟을 가져갑니다.\n");
  printf("14. 카드는 K, Q, J 순으로 높습니다. (K > Q > J)\n");
  printf("15. 두 플레이어 중 한 플레이어가 팟을 가져가는 경우 다음 경기를 진행합니다.\n");
  printf("16. 한 번의 경기를 진행한 이후 카드는 무작위로 섞어야 합니다.\n");
}
void print_points(int points) {
  int i;
  for (i = 0; i < points; i++)
    printf("■");
  for (; i < 8; i++)
    printf("□");
}
int cpu(char user_card, char cpu_card, bool bet) {
  return '0';
}
