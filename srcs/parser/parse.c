#include "../../minishell.h"

void	remove_quotes(char *text)
{
	char	quote_to_del;
	int		i;

	quote_to_del = *(ft_strchrset(text, QUOTES));
	while (*text)
	{
		if (*text == quote_to_del)
		{
			i = 0;
			while (text[i + 1])
			{
				text[i] = text[i + 1];
				i++;
			}
			text[i] = '\0';
		}
		text++;
	}
}

void	quote_removal(t_list_2 *input)
{
	t_word	*word;

	while (input)
	{
		word = (t_word *)(input->content);
		if (ft_strchrset(word->text, QUOTES))
			remove_quotes(word->text);
		input = input->next;
	}
}

t_list_2	*parse(char *input, t_dict *envp_dict)
{
	t_list_2	*split_input;
	char		*expanded_input;
	
	expanded_input = expand_vars(input, envp_dict, IGNORE_QUOTED_VARS);
	split_input = word_split(expanded_input);
	expand_vars_inside_quotes(split_input, envp_dict);
	quote_removal(split_input);
//	tokenise(parsed_input);
	free(expanded_input);
	return (split_input);
}


int	main(int argc, char **argv, char **envp)
{
	char		*input = "\'\"\"$LANGUAGE\"\"\' hello\"$PATH\"";
	t_list_2	*parsed_input;
	t_list_2	*tmp;
	t_dict		*envp_dict;

	envp_dict = init_envp_dict(envp);
	parsed_input = parse(input, envp_dict);
	tmp = parsed_input;
	while (tmp)
	{
		printf("%s ", ((t_word *)tmp->content)->text);
		tmp = tmp->next;
	}
	dict_clear(&envp_dict);
	ft_lst_2clear(&parsed_input, (void *)free_word);
}