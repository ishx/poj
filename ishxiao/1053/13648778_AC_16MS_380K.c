//1053
#include <stdio.h>
typedef union tagCARD {
    long int i;
    char c[8]; } CARD;
int doesFormSet(CARD c1, CARD c2, CARD c3) {
    static int i;
    for (i = 0; i < 4; i ++) {
	if (c1.c[i] == c2.c[i] && c2.c[i] != c3.c[i]) return 0;
	if (c2.c[i] == c3.c[i] && c3.c[i] != c1.c[i]) return 0;
	if (c3.c[i] == c1.c[i] && c1.c[i] != c2.c[i]) return 0;     }
    return 1; }
int main (void) {
  int n, i, j, k, m, c = 0;
  CARD cards[81];
  while (1) {
    if ((cards[0].c[0] = getchar() ) == EOF) break;
    if (cards[0].c[0] != 'D' && cards[0].c[0] != 'O' && cards[0].c[0] != 'S') break;
    for (n = 0; cards[n].c[0] != '\n' && cards[n].c[0] != EOF;
		cards[++ n].c[0] = getchar() ) {
       scanf("%s", &(cards[n].c[1]) ); getchar();         }
    printf("CARDS: ");
    for (i = 0; i < n; i ++) printf(" %s", cards[i].c);
    printf("\nSETS:   ");
    for (i = 0, m = 0; i < n - 2; i ++) {
      for (j = i + 1; j < n - 1; j ++) {
	for (k = j + 1; k < n; k ++) {
	  if (doesFormSet(cards[i], cards[j], cards[k]) ) {
	    if (m ++) printf("        %d.  ", m);
		     else printf("%d.  ", m);
	    printf("%s %s %s\n", cards[i].c, cards[j].c,cards[k].c);  }}}}
    if (!m) printf("*** None Found ***\n");
    putchar('\n');     }
  return 0;
}