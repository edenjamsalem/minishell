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

void	parse(char *input)
{
	t_list **parsed_input;
	
	parsed_input = parse_exc_quotes(input);
	expand_vars_inside_quotes();
	tokenize();
}