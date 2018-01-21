//void RemoveNewLine(char* string);

void CopyString(char *target, char *source);

bool EqualStrings(const char *s1, const char *s2);

bool StartsWith(const char *pre, const char *str);

char *SplitFields(char * str, char const * delims);

bool ParseYesNo();

void ExitError(char * message, int num);

FILE *OpenFile(const char file_dir[], char mode[], int i);

const char *SingleArgumentParser(int argc, char *argv[]);

char *Concat(const char *s1, const char *s2);

void Compress(const char *bin_dir);

void Decompress(const char *bin_dir);