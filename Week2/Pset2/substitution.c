//a program that implements a substitution cipher

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool validate(string key);


int main(int argc, string argv[])
{
    //correct size?
    if (argc == 2)
    {
        //use function dublicate...
        if (validate(argv[1]) == true)
        {
            //len code has to be 26
            int lenar = strlen(argv[1]);

            if (lenar != 26)
            {
                //error
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            else
            {

                //get inp
                string plt = get_string("plaintext: ");
                int len = strlen(plt);

                // which Letter in ascii
                int count = 0;

                // ciphertext array
                char let [len + 1];
                int coun = 0;
                int x = 0;
                string alph = "abcdefghijklmnopqrstuvwxyz";

                for (int i = 0; i < len; i++)
                {
                    //for uppercase letter
                    if (isupper(plt[i]) != 0)
                    {
                        for (int upc = 0; upc < 26; upc++)
                        {
                            if (alph[upc] == tolower(plt[i]))
                            {
                                let[i] = toupper(argv[1][upc]);
                                break;
                            }
                        }
                    }

                    //for lowercase letter
                    else if (islower(plt[i]) != 0)
                    {
                        for (int lowc = 0; lowc < 26; lowc++)
                        {
                            if (alph[lowc] == plt[i])
                            {
                                let[i] = tolower(argv[1][lowc]);
                                break;
                            }
                        }
                    }

                    //without letter
                    else
                    {
                        let[i] = plt[i];
                    }
                }


                int i = 0;

                // terminating null
                let[len] = '\0';

                char str[3];
                strcat(strcpy(str, let), "\n");

                printf("ciphertext: ");
                //print array
                printf("%s", str);
                return 0;

            }

        }
        else
        {
            //fail
            printf("Pleas enter a single Key of 26 chars!\n");
            return 1;
        }
    }
    else
    {
        //fail
        printf("Pleas enter a single Key of 26 chars!\n");
        return 1;
    }

}

//function for val key
bool validate(string key)
{
    int matches = 0;
    if (strlen(key) == 26)
    {

        //look for dublicates
        for (char c = 'a'; c <= 'z'; c++)
        {
            for (int i = 0; i < 26; i++)
            {
                if (tolower(key[i]) == c)
                {
                    matches++;
                    break;
                }
            }
        }
        // only if right count moves on
        if (matches == 26)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else
    {
        return false;
    }
}
