typedef enum {
    EXCLUDE_LIMITS = 0,
    MIN_LIMIT = 1,
    MAX_LIMIT = 2
} RangeInclude;

double inputDouble(const char *prompt);

double inputDoublePositive(const char *prompt);

int inputNatural(const char *prompt);

int inputNatural0(const char *prompt);

int inputIntInRange(const char *prompt, int min, int max);

double inputDoubleInRange(const char *prompt, double min, double max, RangeInclude include);
