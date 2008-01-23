#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 2048

typedef struct _ListItem ListItem;

struct _ListItem {
	char *word;
	int count;
	ListItem *next;
};

ListItem *new_item(char *word)
{
	ListItem *new = malloc(sizeof(ListItem));
	new->word = malloc(strlen(word) + 1);
	strcpy(new->word, word);
	new->count = 1;

	return new;
}

ListItem *count_word(ListItem *list, char *word)
{
	ListItem *head = list;
	ListItem *prev = NULL;

	/* find surrounding items */
	while(list && (strcmp(list->word, word) < 0))
	{
		prev = list;
		list = list->next;
	}

	if(list && (strcmp(list->word, word) == 0))
	{
		/* found match */
		list->count ++;
		list = head;
	}
	else if(prev)
	{
		/* insert item */
		ListItem *new = new_item(word);
		new->next = prev->next;
		prev->next = new;
		list = head;
	}
	else
	{
		/* new first item */
		ListItem *new = new_item(word);
		new->next = head;
		list = new;
	}

	return list;
}

void print_summary(ListItem *list)
{
	while(list)
	{
		printf("%7d %s\n", list->count, list->word);
		list = list->next;
	}
}

void strip_newlines(char *line)
{
	int pos, i;

	/* remove trailing newline characters */
	i = strlen(line) - 1;
	do
	{
		if((line[i] == '\n') || (line[i] == '\r'))
		{
			line[i] = '\0';
		}
		pos ++;
	}
	while(pos > 0);
}

int main(int argc, char *argv[])
{
	ListItem *list = NULL;
	char buffer[BUF_SIZE + 1];
	char word[BUF_SIZE + 1];
	char *p;
	int i;

	while(fgets(buffer, BUF_SIZE, stdin))
	{
		strip_newlines(buffer);

		p = buffer;
		i = 0;
		memset(word, '\0', BUF_SIZE);
		while(*p)
		{
			if(isspace(*p))
			{
				/* got space */
				if(strlen(word) > 0)
				{
					/* register word */
					list = count_word(list, word);
				}

				/* reset word */
				i = 0;
				memset(word, '\0', BUF_SIZE);
			}
			else
			{
				/* add character to word */
				word[i] = *p;
				i ++;
			}

			p ++;
		}

		/* handle last word on line */
		if(strlen(word) > 0)
		{
			/* register word */
			list = count_word(list, word);
		}
	}

	print_summary(list);

	return 0;
}
