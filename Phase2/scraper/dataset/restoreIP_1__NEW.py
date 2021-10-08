char res[1000][20];
char ip[4][6];
int getNum(char *s, int start, int end) {
    if (end - start > 3) {
        return 300;
    }
    char tmp = s[end];
    s[end] = 0;
    int num = atoi(&s[start]);
    s[end] = tmp;
    return num;
}
void getIp(char *s, int *returnSize, int level, int startIndex) {
    if (startIndex >= strlen(s)) {
        return;
    }
    if (level == 3) {
        int num = getNum(s, startIndex, strlen(s));
        if (num > 255 || (s[startIndex] == '0' && startIndex < strlen(s) - 1)) {
            return;
        }else {
            sprintf(ip[level], "%s", &s[startIndex]);
            sprintf(res[*returnSize],"%s.%s.%s.%s", ip[0], ip[1], ip[2], ip[3]);
            (*returnSize)++;
        }
        return;
    }else {
        
        sprintf(ip[level], "%c", s[startIndex]);
        getIp(s, returnSize, level + 1, startIndex + 1);
        if (startIndex < strlen(s) - 2 && s[startIndex] != '0') {
            sprintf(ip[level], "%c%c", s[startIndex], s[startIndex + 1]);
            getIp(s, returnSize, level + 1, startIndex + 2);
        }
        if (startIndex < strlen(s) - 3 && s[startIndex] != '0') {
            int num = getNum(s, startIndex, startIndex + 3);
            if (num <= 255) {
                sprintf(ip[level], "%c%c%c", s[startIndex], s[startIndex + 1], s[startIndex + 2]);
                getIp(s, returnSize, level + 1, startIndex + 3);
            }

        }
    }
    
    
}
char ** restoreIpAddresses(char * s, int* returnSize){
    *returnSize = 0;
    getIp(s, returnSize, 0, 0);
    char **r = (char **)malloc((sizeof(char *))*5000);
    for (int i = 0; i < *returnSize; i++) {
        r[i] = (char *)malloc(25);
        strcpy(r[i], res[i]);
    }
    return r;
    
}
