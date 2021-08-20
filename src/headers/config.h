#define CONFIG_FILE "biotc.config"
#define LENGHT_1 1
#define LENGHT_2 2
#define LENGHT_4 4
#define LENGHT_8 8
#define LENGHT_16 16
#define LENGHT_32 32
#define LENGHT_64 64
struct sample_parameters
{
  char DEFAULT_TEMPERATURE_MEASURE[1];
  char SHOW_SYMBOL[1];
} sample_parameters;

void init_parameters (struct sample_parameters * parms);
char * trim (char * s);
void parse_config (struct sample_parameters * parms);
