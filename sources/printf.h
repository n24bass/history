// N.B. we add buffering to the default printf since we can only process
//      a few BDM accesses per second thru the "Trap #14" mechanism... :-(

int
snprintf(char *buffer, int length, char *format, ...);

int
sprintf(char *buffer, char *format, ...);

int
printf(char *format, ...);
