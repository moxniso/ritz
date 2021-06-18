#ifndef KMODE_H

#define RKMODE_CMDS_MAXLEN 9 // 10
#define RKMODE_CMDS_NUM 6 // 7

int rkmode_parse(char* cmd);
void rkmode_open(BOOL once);
int rkmode_init(void);

#endif /* KMODE_H */

