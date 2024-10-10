#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void display_table(int round, char user_card, char cpu_card, int pot, int user_points, int cpu_points, bool showdown);
void play_round(int round, int* user_points, int* cpu_points);
void shuffle_cards(char* card1, char* card2, char* card3);
int card_value(char card);
void menu();
void print_rules();
void print_points(int points);
int cpu(char user_card, char cpu_card, bool bet);

int main(void) {
  srand(time(NULL));
  menu();
  return 0;
}

/**
 * @brief Display the game table.
 * 
 * @param round The current round number.
 * @param user_card The user's card.
 * @param cpu_card The CPU's card.
 * @param pot The current pot.
 * @param user_points The user's points.
 * @param cpu_points The CPU's points.
 * @param showdown Whether the cards are revealed.
 * @return void
 * 
 * @note This function does not clear the screen by itself.
 */
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

/**
 * @brief Play a round of the game.
 * 
 * This function serves as the main game loop for a single round, calling the
 * necessary functions to shuffle the cards, display the table, and handle the
 * user and CPU's turns as required by itself.
 * 
 * @param round The current round number.
 * @param user_points The user's points, by reference.
 * @param cpu_points The CPU's points, by reference.
 * @return void
 * 
 * @note This function modifies the referenced points variables.
 */
void play_round(int round, int* user_points, int *cpu_points) {
  char user_card, cpu_card, table;
  int pot = 0;
  int op, ch;
  shuffle_cards(&user_card, &cpu_card, &table);
  system("clear");
  display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
  printf("경기 %d을(를) 시작합니다.\n", round);
  printf("\nc를 눌러서 진행합니다: ");
  // The mechanisms related to processing invalid input is explained in detail
  // in menu(), please refer
  while ((ch = getchar()) != 'c' || getchar() != '\n') {
    if (ch != '\n')
      while (getchar() != '\n');
    printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
    printf("\nc를 눌러서 진행합니다: ");
  }

  // Collect the ante
  *user_points -= 1, *cpu_points -= 1, pot += 2;
  // Whether the previous player's action was a bet
  bool bet = false;
  // Number of consecutive 'passive' actions used to determine the end of the round
  // Checking and calling is passive, betting is aggressive but a following
  // passive action ends the turn, and folding doesn't matter since the match
  // is forfeited anyways
  // Two consecutive 'passive' actions end the round
  int passes = 0;
  while (passes < 2) {
    system("clear");
    display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
    // If USER has no points, they can't bet or call
    if (*user_points) {
      if (bet)
        printf("[USER] 1 포인트를 콜하거나 폴드합니다. (0: 콜, 1: 폴드): ");
      else
        printf("[USER] 체크하거나 1 포인트를 베트합니다. (0: 체크, 1: 베트): ");
      while ((unsigned) (op = getchar()) - '0' >= 2 || getchar() != '\n') {
        if (op != '\n')
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
        op = '1';
      } else {
        printf("[USER] 포인트 부족으로 인해 USER는 베트할 수 없습니다. 자동으로 체크합니다.\n");
        op = '0';
      }
    }
    printf("\nc를 눌러서 진행합니다: ");
    while ((ch = getchar()) != 'c' || getchar() != '\n') {
      if (ch != '\n')
        while (getchar() != '\n');
      printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
      printf("\nc를 눌러서 진행합니다: ");
    }
    if (bet)
      switch (op) {
        // Call
        case '0':
          *user_points -= 1, pot += 1, bet = false, passes += 1;
          system("clear");
          display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
          printf("[USER] 1 포인트를 콜했습니다. 이제 팟은 %d 포인트입니다.\n", pot);
          break;
        // Fold
        case '1':
          // USER folds, therefore CPU wins the pot
          *cpu_points += pot;
          system("clear");
          display_table(round, user_card, cpu_card, 0, *user_points, *cpu_points, true);
          printf("[폴드] CPU가 %d 포인트의 팟을 차지합니다.\n", pot);
          printf("경기 %d의 결과로 USER는 %d 포인트, CPU는 %d 포인트를 가지게 되었습니다.\n",
            round, *user_points, *cpu_points);
          printf("\nc를 눌러서 진행합니다: ");
          while ((ch = getchar()) != 'c' || getchar() != '\n') {
            if (ch != '\n')
              while (getchar() != '\n');
            printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
            printf("\nc를 눌러서 진행합니다: ");
          }
          return;
      }
    else
      switch (op) {
        // Check
        case '0':
          passes += 1;
          system("clear");
          display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
          printf("[USER] 체크합니다.\n");
          break;
        // Bet
        case '1':
          *user_points -= 1, pot += 1, bet = true, passes = 1;
          system("clear");
          display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
          printf("[USER] 1 포인트를 베트했습니다. 이제 팟은 %d 포인트입니다.\n", pot);
          break;
      }
    printf("\nc를 눌러서 진행합니다: ");
    while ((ch = getchar()) != 'c' || getchar() != '\n') {
      if (ch != '\n')
        while (getchar() != '\n');
      printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
      printf("\nc를 눌러서 진행합니다: ");
    }
    if (passes == 2)
      break;

    system("clear");
    display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
    // If CPU has no points, they can't bet or call
    if (*cpu_points)
      // CPU makes a supposedly informed decision and returns '0' or '1'
      op = cpu(user_card, cpu_card, bet);
    else {
      if (bet) {
        printf("[CPU] 포인트 부족으로 인해 CPU는 콜할 수 없습니다. 자동으로 폴드합니다.\n");
        op = '1';
      } else {
        printf("[CPU] 포인트 부족으로 인해 CPU는 베트할 수 없습니다. 자동으로 체크합니다.\n");
        op = '0';
      }
    }
    if (bet)
      switch (op) {
        // Call
        case '0':
          printf("[CPU] CPU는 콜하기로 결정했습니다.\n");
          printf("\nc를 눌러서 진행합니다: ");
          while ((ch = getchar()) != 'c' || getchar() != '\n') {
            if (ch != '\n')
              while (getchar() != '\n');
            printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
            printf("\nc를 눌러서 진행합니다: ");
          }
          *cpu_points -= 1, pot += 1, bet = false, passes += 1;
          system("clear");
          display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
          printf("[CPU] 1 포인트를 콜했습니다. 이제 팟은 %d 포인트입니다.\n", pot);
          break;
        // Fold
        case '1':
          printf("[CPU] CPU는 폴드하기로 결정했습니다.\n");
          printf("\nc를 눌러서 진행합니다: ");
          while ((ch = getchar()) != 'c' || getchar() != '\n') {
            if (ch != '\n')
              while (getchar() != '\n');
            printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
            printf("\nc를 눌러서 진행합니다: ");
          }
          // CPU folds, therefore USER wins the pot
          *user_points += pot;
          system("clear");
          display_table(round, user_card, cpu_card, 0, *user_points, *cpu_points, true);
          printf("[폴드] USER가 %d 포인트의 팟을 차지합니다.\n", pot);
          printf("경기 %d의 결과로 USER는 %d 포인트, CPU는 %d 포인트를 가지게 되었습니다.\n",
            round, *user_points, *cpu_points);
          printf("\nc를 눌러서 진행합니다: ");
          while ((ch = getchar()) != 'c' || getchar() != '\n') {
            if (ch != '\n')
              while (getchar() != '\n');
            printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
            printf("\nc를 눌러서 진행합니다: ");
          }
          return;
      }
    else
      switch (op) {
        // Check
        case '0':
          printf("[CPU] CPU는 체크하기로 결정했습니다.\n");
          printf("\nc를 눌러서 진행합니다: ");
          while ((ch = getchar()) != 'c' || getchar() != '\n') {
            if (ch != '\n')
              while (getchar() != '\n');
            printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
            printf("\nc를 눌러서 진행합니다: ");
          }
          passes += 1;
          system("clear");
          display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, false);
          printf("[CPU] 체크합니다.\n");
          break;
        // Bet
        case '1':
          printf("[CPU] CPU는 베트하기로 결정했습니다.\n");
          printf("\nc를 눌러서 진행합니다: ");
          while ((ch = getchar()) != 'c' || getchar() != '\n') {
            if (ch != '\n')
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
    while ((ch = getchar()) != 'c' || getchar() != '\n') {
      if (ch != '\n')
        while (getchar() != '\n');
      printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
      printf("\nc를 눌러서 진행합니다: ");
    }
  }

  system("clear");
  // Show CPU's card by setting showdown to true
  display_table(round, user_card, cpu_card, pot, *user_points, *cpu_points, true);
  printf("[쇼다운] 카드를 공개합니다.\n");
  printf("\nc를 눌러서 진행합니다: ");
  while ((ch = getchar()) != 'c' || getchar() != '\n') {
    if (ch != '\n')
      while (getchar() != '\n');
    printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
    printf("\nc를 눌러서 진행합니다: ");
  }
  if (card_value(user_card) > card_value(cpu_card)) {
    // USER wins
    *user_points += pot;
    system("clear");
    display_table(round, user_card, cpu_card, 0, *user_points, *cpu_points, true);
    printf("[경기 결과] USER가 %d 포인트의 팟을 차지합니다.\n", pot);
  } else {
    // CPU wins, there is no tie
    *cpu_points += pot;
    system("clear");
    display_table(round, user_card, cpu_card, 0, *user_points, *cpu_points, true);
    printf("[경기 결과] CPU가 %d 포인트의 팟을 차지합니다.\n", pot);
  }
  printf("경기 %d의 결과로 USER는 %d 포인트, CPU는 %d 포인트를 가지게 되었습니다.\n",
    round, *user_points, *cpu_points);
  printf("\nc를 눌러서 진행합니다: ");
  while ((ch = getchar()) != 'c' || getchar() != '\n') {
    if (ch != '\n')
      while (getchar() != '\n');
    printf("올바르지 않은 입력입니다. c를 눌러야 진행됩니다.");
    printf("\nc를 눌러서 진행합니다: ");
  }
}

/**
 * @brief Shuffle three cards randomly.
 * 
 * @param card1 The first card, by reference.
 * @param card2 The second card, by reference.
 * @param card3 The third card, by reference.
 * @return void
 * 
 * @note The random seed must be set with srand before calling this function.
 */
void shuffle_cards(char* card1, char* card2, char* card3) {
  // The most emptyheaded way is also the simplest here.
  // Since there are exactly 6 permutations of the cards, we can just generate
  // a random number between 0 and 5 and assign the cards based on the result.
  // Do note that modulus of rand() is not perfectly uniform, and rand() is not
  // secure in the first place.
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

/**
 * @brief Get the value of a card.
 * 
 * 'Values' of cards are assigned arbitrarily, and the only guarantee made is
 * that 'K' > 'Q' > 'J'.
 * 
 * @param card The card to get the value of.
 * @return int The value of the card.
 * 
 * @note This function returns -1 for invalid cards.
 */
int card_value(char card) {
  // K = 2, Q = 1, J = 0 is an easy choice
  // Common playing card values (K = 13, Q = 12, J = 11) work too
  // GCC complains about the lack of a default case, therefore I throw in -1
  // The absence of a default case is also an invariant I will uphold,
  // therefore this value doesn't matter as much.
  switch (card) {
    case 'K':
      return 2;
    case 'Q':
      return 1;
    case 'J':
      return 0;
    default:
      return -1;
  }
}

/**
 * @brief The main menu of the game.
 * 
 * This function displays the main menu of the game, allowing the user to view
 * the rules, start a game, or exit the program. This function serves as the
 * effective entry point of the program, calling all other functions as needed.
 * 
 * @return void
 */
void menu() {
  int op, ch;
  // Break conditions are for input 3 (exit)
  while (true) {
    printf("[쿤 포커 (Kuhn Poker)]\n");
    printf("1. 규칙 출력\n");
    printf("2. 게임 시작\n");
    printf("3. 게임 종료\n");
    printf("선택지를 입력합니다: ");
    // Now this requires some explanation.
    // The first call to getchar() expects a char between '1' and '3' inclusive.
    // Luckily the values are contiguous, so we can just subtract '1' and check
    // if the result is between 0 and 2 inclusive. Casting to unsigned does the
    // comparison to 0 for us, so we just check if the result is less than 3.
    // The second call to getchar() expects a newline, this ensures that nothing
    // else follows. The following loop will continually attempt to ask for
    // input while it is invalid.
    while ((unsigned) (op = getchar()) -  '1' >= 3 || getchar() != '\n') {
      // This consumes the rest of the input buffer, so that the next call to
      // getchar() will read from a clean buffer. This however exposes a bug
      // where if the input is a single newline, the program will hang waiting
      // for another line, only continuing after consuming an entire extra line.
      // To remedy, a simple check for '\n' is added before the loop.
      if (op != '\n')
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
    switch (op) {
      // Print rules
      case '1':
        system("clear");
        print_rules();
        printf("r을 누르면 메인 메뉴로 돌아갑니다: ");
        while ((ch = getchar()) != 'r' || getchar() != '\n') {
          if (ch != '\n')
            while (getchar() != '\n');
          printf("올바르지 않은 입력입니다. r을 눌러야 메인 메뉴로 돌아갑니다: ");
        }
        system("clear");
        break;
      // Start game
      case '2':
        int round = 0, user_points = 4, cpu_points = 4;
        // Loop rounds while both players have points
        do play_round(++round, &user_points, &cpu_points);
          while (user_points > 0 && cpu_points > 0);
        system("clear");
        printf("%s의 포인트가 소진되었습니다. %s가 승리했습니다.\n",
          user_points ? "CPU" : "USER", user_points ? "USER" : "CPU");
        printf("메인 화면으로 돌아갑니다.\n\n");
        break;
      // Exit
      case '3':
        printf("게임을 종료합니다.\n");
        // return exits from the entire function
        return;
    }
  }
}

/**
 * @brief Print the rules of the game.
 * 
 * @return void
 * 
 * @note This function does not clear the screen by itself.
 */
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

/**
 * @brief Print a number of points as filled squares.
 * 
 * @param points The number of points to print.
 * @return void
 * 
 * @note This function prints directly to stdout, instead of a string buffer.
 */
void print_points(int points) {
  int i;
  for (i = 0; i < points; i++)
    printf("■");
  for (; i < 8; i++)
    printf("□");
}

/**
 * @brief The CPU's turn.
 * 
 * This function represents the CPU player's decision-making process. The CPU
 * player will randomly decide to bet or fold, with a 50% chance of either.
 * Parameters are passed such that the CPU can make an (over)informed decision,
 * and it is trivial to modify the function to include more complex decision
 * making.
 * 
 * @param user_card The user's card.
 * @param cpu_card The CPU's card.
 * @param bet Whether the user has bet.
 * @return int The CPU's decision, in '0' or '1'.
 * 
 * @note The random seed must be set with srand before calling this function.
 */
int cpu(char user_card, char cpu_card, bool bet) {
  if (rand() % 2)
    return '1';
  else
    return '0';
}
