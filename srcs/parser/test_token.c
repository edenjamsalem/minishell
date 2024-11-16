#include "../../minishell.h"

// test for tokenisation 

void	free_word(t_word *word)
{
	free(word->text);
	free(word);
}

const char *token_type_to_string(enum e_token token)
{
    switch (token)
    {
        case TEXT: return "TEXT";
        case NUMBER: return "NUMBER";
        case CMD: return "CMD";
        case VAR: return "VAR";
        case KEYWORD: return "KEYWORD";
        case S_QUOTES: return "S_QUOTES";
        case D_QUOTES: return "D_QUOTES";
        case PATH: return "PATH";
        case CONTROL_OP: return "CONTROL_OP";
        case REDIRECT: return "REDIRECT";
        case COMMENT: return "COMMENT";
        case GLOB: return "GLOB";
        case NLINE: return "NLINE";
        default: return "UNKNOWN";
    }
}

t_list_2 *create_word_list(char *words[], int count)
{
    t_list_2 *list = NULL;
    t_word *word;
    t_list_2 *node;
    int i;

    for (i = 0; i < count; i++)
    {
        word = malloc(sizeof(t_word));
        word->text = ft_strdup(words[i]);
        word->token = TEXT; // default token type
        node = ft_lst_2new(word);
        ft_lst_2add_back(&list, node);
    }
    return list;
}

// tokenisation test for every token type except for path
// tbh half of these probably won't be necessary 
void test_tokenisation()
{
    char *words[] = {
        "echo",          // CMD
        "$USER",         // VAR
        "\"Hello, World!\"", // D_QUOTES
        "'",             // S_QUOTES
        "#",             // COMMENT
        "*",             // GLOB
        "\n",            // NLINE
        "if",            // KEYWORD
        "123",           // NUMBER
        "/path/to/file", // PATH
        ">",             // REDIRECT
        "&&",            // CONTROL_OP
        "text"           // TEXT
    };
    
    int word_count = sizeof(words) / sizeof(words[0]);
    t_list_2 *word_list = create_word_list(words, word_count);
    tokenise(word_list);
    t_word *word;
    t_list_2 *temp = word_list;
    while (temp)
    {
        word = (t_word *)temp->content;
        printf("Word: %s, Token Type: %s\n", word->text, token_type_to_string(word->token));
        temp = temp->next;
    }
    ft_lst_2clear(&word_list, (void *)free_word);
}

int main()
{
    test_tokenisation();
    return 0;
}
