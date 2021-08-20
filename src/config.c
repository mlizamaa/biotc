#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "./headers/config.h"



// initialize configurations with default values
void
init_parameters (struct sample_parameters * parms)
{
  strncpy(parms-> DEFAULT_TEMPERATURE_MEASURE, "c", 2);
  strncpy(parms-> SHOW_SYMBOL, "1",2);
}

/*
 * trim:delete both trailing and leading whitespace
 */
char *
trim (char * s)
{
  // copy of s to delete  trailing whitespace
  char *s1 = s;

  // copy of s to delete  leading whitespace
  char *s2 = &s[strlen (s) - 1];

  /* delete trailing witespace */
  while ((isspace(*s2)) && (s2 >= s1) )
    s2--;

  *(s2+1) = '\0';

  /* delete leading witespace */
  while ( (isspace (*s1)) && (s1 < s2) )
    s1++;

  /* Copy finished string */
  strcpy(s,s1);
  return s;
}

void 
parse_config (struct sample_parameters * parms)
{
  char *s, buff[256];
  FILE *fp = fopen (CONFIG_FILE, "r");
  if (fp == NULL)
  {
    return;
  }
  // read line to line
  while ((s = fgets (buff, sizeof buff, fp)) != NULL)
  {
    if (buff[0] == '\n' || buff[0] == '#')
      continue;

    char  name[LENGHT_64], 
          value[LENGHT_1];
    
    s = strtok (buff, "=");
    
    if (s==NULL)
      continue;
    else
      strncpy (name, s, LENGHT_64);

    s = strtok (NULL, "=");

    if (s==NULL)
      continue;
    else
      strncpy (value, s, LENGHT_1);
    trim (value);
    trim(name);
    /* Copy into correct entry in parameters struct */
    printf("%s",name);
    if (strcmp(name, "default-temperature-measurement")==0){
      strncpy (parms->DEFAULT_TEMPERATURE_MEASURE, value, LENGHT_1);
    }
    else if(strcmp(name, "show-symbol")){
      strncpy (parms->SHOW_SYMBOL, value, LENGHT_1);
      }
    else
      printf ("WARNING: %s/%s: Unknown name/value pair!\n",name,value);
  }

  /* Close file */
  fclose (fp);
}