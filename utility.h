#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

void open_file(FILE** fp,char* filename);

void newline_remover(char *s);

void check_newline(char *s);

void format_string(char *s);

int verify_date(char *data);

#endif //UTILITY_H_INCLUDED