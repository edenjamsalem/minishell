#include "../../minishell.h"

	// expand variables OUTSIDE of quotes, e.g. $USER, $HOME
		// if " or ' encountered, skip until next " or '
		// search string for '$'
		// if text after $ is valid variable, expand variable
		// else ... 
	
	// split input into "words", i.e. strings delimited by space, tab or \n
	// text inside quotes is considered a single word

	// words are tokenized as COMMANDS, ARGUMENTS, KEYWORDS, SPECIAL SYMBOL

	// expand variables INSIDE double quotes but NOT single quotes

t_list_2	*parse(char *input, t_dict *envp_dict)
{
	t_list_2	*parsed_input;
	char		*expanded_input;
	
	expanded_input = expand_vars(input, envp_dict, IGNORE_QUOTED_VARS);
	parsed_input = word_split(expanded_input);
	expand_vars_inside_quotes(parsed_input, envp_dict);
	//quote_removal();
//	tokenise(parsed_input);
	free(expanded_input);
	return (parsed_input);
}


int	main(int argc, char **argv, char **envp)
{
	char		*input = "\'$LANGUAGE\' \"$PATH\"";
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