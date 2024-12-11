#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct reservation {
  char name[21];
  uint64_t tel;
  size_t size;
  time_t time;
} reservation;
typedef struct waitlist {
  struct reservation data;
  struct waitlist *next;
} waitlist;

waitlist *waitlist_new();
void waitlist_free(waitlist *wl);
waitlist *waitlist_recall(char const *infile);
void waitlist_save(waitlist const *wl, char const *outfile);
void waitlist_print(waitlist const *wl);
void waitlist_add(waitlist **head, reservation rv);
waitlist *waitlist_find(waitlist const *wl, uint64_t tel);
void waitlist_modify(waitlist *node, reservation rv);
void waitlist_cancel(waitlist **head, uint64_t tel);
void waitlist_process(waitlist **head, reservation rv);
char expect_char(char const *accepted, char const *initial_prompt, char const *retry_prompt);

int main(int argc, char **argv) {
  waitlist *wl = waitlist_recall("waitlist.txt");
  for (;;) {
    system("clear");
    waitlist_print(wl);
    switch (expect_char(
      "123456",
      "식당 웨이팅 프로그램\n"
      "1. 웨이팅 등록\n"
      "2. 웨이팅 조회\n"
      "3. 웨이팅 수정\n"
      "4. 웨이팅 취소\n"
      "5. 웨이팅 입장\n"
      "6. 프로그램 종료\n"
      "선택: ",
      "선택: "
    )) {
    case '1':
      break;
    case '2':
      break;
    case '3':
      break;
    case '4':
      break;
    case '5':
      break;
    case '6':
      break;
    }
  }
}

waitlist *waitlist_new() {
  return NULL;
}
void waitlist_free(waitlist *wl) {
  waitlist *tmp;
  while (wl) {
    tmp = wl;
    wl = wl->next;
    free(tmp);
  }
}
waitlist *waitlist_recall(char const *infile) {
  FILE *file = fopen(infile, "r");
  if (!file)
    return NULL;

  waitlist *wl = waitlist_new();
  char line[256];
  reservation rv;
  while (fgets(line, sizeof line, file))
    if (sscanf(line, "%[^,],%llu,%zu,%ld\n", rv.name, rv.tel, &rv.size, &rv.time) == 4)
      waitlist_add(&wl, rv);
  return wl;
}
void waitlist_save(waitlist const *wl, char const *outfile) {
  FILE *file = fopen(outfile, "w");
  if (!file)
    return;

  for (; wl; wl = wl->next)
    fprintf(file, "%s,%llu,%zu,%ld\n", wl->data.name, wl->data.tel, wl->data.size, wl->data.time);
}
void waitlist_print(waitlist const *wl) {
  // TODO
}
void waitlist_add(waitlist **head, reservation rv) {
  waitlist *tail;
  for (tail = *head; tail; tail = tail->next);
  tail->next = malloc(sizeof(waitlist));
  tail->next->data = rv;
  tail->next->next = NULL;
}
waitlist *waitlist_find(waitlist const *wl, uint64_t tel) {
  for (; wl; wl = wl->next)
    if (tel == wl->data.tel)
      return wl;
  return NULL;
}
void waitlist_modify(waitlist *node, reservation rv) {
  node->data = rv;
}
void waitlist_cancel(waitlist **head, uint64_t tel) {
  if (!*head)
    return;

  if (tel == (*head)->data.tel) {
    waitlist *tmp = *head;
    (*head)->next = (*head)->next->next;
    free(tmp);
  }

  waitlist *insert_spot;
  for (insert_spot = *head; insert_spot->next; insert_spot = insert_spot->next)
    if (tel == insert_spot->next->data.tel) {
      waitlist *tmp = insert_spot->next;
      insert_spot->next = insert_spot->next->next;
      free(tmp);
    }
}
void waitlist_process(waitlist **head, reservation rv) {
  // TODO
}
char expect_char(char const *accepted, char const *initial_prompt, char const *retry_prompt) {
  printf("%s", initial_prompt);
  char ch = getchar();
  while (!strchr(accepted, ch) || getchar() != '\n') {
    if (ch != '\n')
      while (getchar() != '\n');
    printf("%s", retry_prompt);
    ch = getchar();
  }
  return ch;
}
