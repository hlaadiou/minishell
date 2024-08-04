/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 08:48:38 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 15:21:48 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* SPECIAL CHARACTERS */
# define BLANK " \t"
# define SEPARATOR " \t|&\"\'<>()"
# define HDOC_SEP "|&<>()"

/* SYNTAX ERRORS */
# define UNCLOSED 1
# define UNEX_PAREN 3
# define UNEX_PIPE 4
# define UNEX_OR 5
# define UNEX_AND 6
# define UNEX_NL 7
# define UNEX_RPAR 8
# define UNEX_TOK 9

/* ERROR CODES */
# define ALLOCERR 1337
# define AMBGRDIR 4242
# define SYNTAXERR 258

/* INCLUDES */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>

/* TYPEDEFS */
typedef enum s_node_type
{
	PIPE,
	RD_IN_WD,
	RD_IN_SQ,
	RD_IN_DQ,
	RD_OUT_WD,
	RD_OUT_SQ,
	RD_OUT_DQ,
	APPEND_WD,
	APPEND_SQ,
	APPEND_DQ,
	HDOC_EXP,
	HDOC,
	AND,
	OR,
	R_PAREN,
	L_PAREN,
	SPC,
	S_QUOTE,
	D_QUOTE,
	WORD,
	END
}	t_node_type;

typedef struct s_env
{
	int				hide;
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	t_node_type		type;
	char			*lexeme;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_garb
{
	void			*ptr;
	struct s_garb	*next;
}	t_garb;

typedef struct s_cmd
{
	int		hdoc;
	int		sub_hdoc;
	t_token	*list;
	t_token	*redir;
	t_token	*sub_redir;
}	t_cmd;

typedef struct s_tree	t_tree;

typedef struct s_node
{
	t_tree	*lchild;
	t_tree	*rchild;
}	t_node;

typedef enum e_type
{
	S_AND,
	T_AND,
	S_OR,
	T_OR,
	S_PIPE,
	T_PIPE,
	S_CMD,
	T_CMD,
}	t_type;

typedef struct s_tree
{
	t_type		type;
	t_node		node;
	t_cmd		cmd;
}	t_tree;

typedef struct s_exit
{
	int		status;
	t_garb	*gc;
}	t_exit;

t_exit					g_exit;

typedef struct s_data
{
	int	i;
	int	j;
	int	str_i;
	int	pat_i;
	int	*flags;
	int	flags_i;
}	t_data;

typedef struct s_entry
{
	char			*name;
	struct s_entry	*next;
}	t_entry;

typedef struct s_flags
{
	t_token	*tkn;
	int		**flagvec;
	int		arrs;
}	t_flags;

/***************** Parsing ********************/

//	Libft
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
int			ft_strcmp(char *str1, char *str2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);

//	Ascii to unsigned long long
size_t		ft_atoull(const char *str);

//	General purpose functions
t_token		*lst_last(t_token *tkn);

//	Environment
t_env		*env_dup(char *prog_name, char **env);
char		*update_shell_lvl(void);
t_env		*get_env_node(t_env *env, char *name);
char		*get_env_value(t_env *env, char *name);
void		update_env_value(t_env **env, char *name, char *new_val,
				int append);
int			env_node_insert(t_env **env, char *name, char *val, int hide);

//	Memory management
void		clean_env_list(t_env **envp);
void		clean_vec(char **vec);
void		clean_intvec(int **intvec);
void		clean_list(t_entry **list);

//	Garbage Collector
void		*ft_malloc(size_t size);
void		clean_all(void);
int			garbage_list_add(t_garb **gc, void *ptr);

//	Shell Prompt
char		*prompt(t_env *env);

//	Tokenizer functions
t_token		*lexer(char *cmdline);
int			token_list_add(t_token **list, t_node_type type, char *content,
				size_t size);
int			redir_syntax_error(char *cmdline);
int			check_tokens(t_token **tokens, char *cmdline, char *limit);
int			check_word(t_token **tokens, char *cmdline, char *limit);
int			check_parenthesis(t_token **tokens, char *cmdline);
int			check_or(t_token **tokens, char *cmdline);
int			check_and(t_token **tokens, char *cmdline);
int			check_pipe(t_token **tokens, char *cmdline);
int			check_heredoc(t_token **tokens, char *cmdline);
int			check_append(t_token **tokens, char *cmdline);
int			check_infile(t_token **tokens, char *cmdline);
int			check_outfile(t_token **tokens, char *cmdline);
int			check_redirection(t_token **tokens, char *cmdline);
int			check_single_quotes(t_token **tokens, char *cmdline);
int			check_double_quotes(t_token **tokens, char *cmdline);
int			in_set(char c, char *set);

//	Syntax errors
void		check_syntax(t_token **tokens);
int			check_paren(t_token **tok, char **s);
int			check_connector(t_token **tok);
void		print_error(char *s1, char *s2);
void		print_syntax_error(int err, char *str);
int			is_cmd(t_token *tok);
int			is_connector(t_token *tok);

//	Recursive Descent Parser functions
t_tree		*parser(t_token **tokens);
int			parse_group(t_tree **root, t_token **tokens);
int			parse_condition(t_tree **root, t_token **tokens);
int			parse_pipeline(t_tree **root, t_token **tokens);
int			parse_command(t_tree **root, t_token **tok);

//	Prser utils
int			in_list(t_token *tok);
int			build_list(t_token **ptr, t_token **tokens);
void		init_cmd_node(t_tree *cmd);
t_tree		*new_tree_node(t_type type, t_tree *left, t_tree *right);
t_type		condition_node_type(t_token **tokens);
void		subshell_root_type(t_tree *subsh);
int			add_group_redir(t_token *paren, t_tree *group);

//	Give the type of the next token that is a connector or parens 
t_node_type	peek(t_token *tokens);

//	Check whether the token is an input redirection
int			is_redir_in(t_node_type type);

//	Check whether the token is an output redirection
int			is_redir_out(t_node_type type);

//	Skip the redirections in a pipeline
void		skip_redirs(t_token **tokens);

//	Skip a certain token
void		skip(t_token **tokens, t_node_type type);

//	Builtin functions
void		_env(t_env *env, char **arg, int fd);
void		_pwd(t_env *env, char **cmd, int fd);
void		_cd(char **cmd, t_env *env, int fd);
void		_export(char **cmd, t_env **env, int fd);
void		_unset(t_env **env, char **cmd);
void		_echo(char **cmd, int fd);
void		_exit_(t_env **env, char **cmd);

//	Builtin utils
void		print_env(t_env *env, int fd);
int			check_name(char *arg, int *append);

//	Signal handling
void		signal_interrupter(void);
void		ignore_signals(void);
void		default_signals(void);
void		heredoc_signals(void);

//	HEREDOC Functions
int			open_heredoc(t_token *hdoc, t_env *env);
int			open_heredocs(t_tree *root, t_env *env);
int			open_subsh_hdoc(t_tree *root, t_env *env);
t_token		*read_heredoc(char *delim);
void		update_subshell_hdoc(t_tree *root, int subsh_hdoc);
void		heredoc(t_token *hdoc, t_env *env, int *pipe);
int			update_hdoc_fd(t_tree *cmd, t_env *env);
int			get_hdoc_fd(t_tree *cmd, t_env *env);

/***************** Wildcards ********************/

int			wildcard_match(char *str, char *pattern, int *flags);
t_entry		*dir_pattern_check(char *dir, char *pattern, int *flags);
int			entry_node_insert(t_entry **list, char *name);

/***************** Execution ********************/

//	MACRO PROCESSING
t_token		*list_expand(t_token *tokens, t_env *env);
t_token		*redir_expand(t_token *redir, t_env *env);
int			node_expand(t_cmd *cmd_node, t_env *env);
int			node_expand(t_cmd *cmd_node, t_env *env);

//	VARS PROCESSING
int			get_wordsize(char *lexeme, int i);
int			get_idsize(char *lexeme, int i);
int			expand_env_vars(t_token **newlst, t_token *lst, t_env *env);
int			get_splitted_lst_var(t_token **lst, t_token *tkn, t_env *env);
void		set_lst_exit_status(t_token *sub);

//	WILDCARD PROCESSING
void		fill_flagtab(int *tab, int *flags, int len, int *ind);
void		fill_wildtab(int *flags, t_token *tknlst);
void		create_flagtabs(int **vec, int *flags, t_token *lst);
int			**create_wildvec(int *flags, t_token *lst);
int			*create_wildflags(t_token *tknlst);
void		extract_dir_pattern(char **dir, char **pattern, t_token *tkn);
int			wild_lexeme_match(t_token **lst, t_entry *matches, char *dir, \
												t_node_type type);
int			wild_tkn_expand(t_token **newlst, t_token *tkn, int **flags, \
																int *pos);
t_token		*wildlst_expand(t_token *tknlst, int **flags);

//	TILDE PROCESSING
char		*get_home(t_env *env);
int			expandable_lst_tilde(t_token *lst);
void		expand_lst_tilde(t_token *lst, t_env *env);

//	HEREDOC PROCESSING
char		*hdoc_expand(t_token *tkn);
t_token		*heredoc_content_exp(t_token *doc, t_env *env);
t_token		*get_hdoc_delim(t_token **redir);
t_node_type	hdoc_pick_type(t_token *lst);

//	TOKENS PROCESSING
t_token		*tkn_split(t_token *tkn);
t_token		*redirlst_split(t_token *redir);
t_token		*redir_join(t_token *redir);
t_token		*tkn_join(t_token *lst);
t_token		*tkn_join(t_token *lst);
int			subtkn_update(t_token **newlst, t_token *tkn, t_token *sub, \
															t_env *env);
int			tkn_update(t_token **newlst, t_token *lst, t_env *env);

//	REDIRECTIONS PROCESSING
t_token		*wild_redirlst_exp(t_token *rdirlst, int **flags);
char		*grep_value(t_token	*tkn, t_env *env);
int			redir_update(t_token **redirlst, t_token *lst, t_env *env);
int			expand_redir_vars(t_token **newredir, t_token *lst, t_env *env);
t_token		*redir_expand(t_token *redir, t_env *env);
int			expandable_rdir_tilde(t_token *lst);
void		expand_rdir_tilde(t_token *lst, t_env *env);
int			wild_redir_match(t_token **lst, t_entry *matches, char *dir, \
														t_node_type type);
int			wild_redir_exp(t_token **newlst, t_token *tkn, int **flags, \
																int *pos);
void		ambiguous_redir(char *str);
void		join_filename(t_token **redir, char **newfile);
t_token		*redir_join(t_token *redir);
int			expandable_tkn(t_token *lst);
void		assign_rd_in(t_token *tkn);
void		assign_rd_out(t_token *tkn);
void		assign_append(t_token *tkn);
void		choose_type(t_token *tkn);
void		set_redir_exit_status(t_token *redir);
int			expandable_redir(t_token *lst);
void		truncate_dollar(t_token *tkn, char **var);
char		*get_splitted_redir_var(t_env *env, char *var);
int			check_ambiguity(t_token *tkn, t_env *env);

//	EXECUTOR
int			executor(t_tree *root, t_env **env);

//	CMD EXECUTOR
int			exec_cmd(t_tree *node, t_env **env);
void		execute_builtin(char **cmd, t_env **env, int *files);
void		exec_builtins(t_tree *node, t_env **env);
void		execute_child(t_tree *node, t_env *env);
int			execute_command(t_tree *node, t_env **env);

//	PIPES
int			exec_pipe(t_tree *node, t_env **env);
int			exec_left_pipe(t_tree *node, t_env **env, int *fds, int *pid);
int			exec_right_pipe(t_tree *node, t_env **env, int *fds, int *pid);

//	LOGICAL OPERATORS
int			exec_or(t_tree *node, t_env **env);
int			exec_and(t_tree *node, t_env **env);

//	PARENTHESIS (PRIORITY + SUBSHELL)
int			*open_subsh_files(t_cmd subsh);
int			is_subshell(t_type type);
void		set_subshell_files(t_tree *subsh);
void		subshell(t_tree *subsh, t_env **env);

//	FILES
int			open_append_files(t_token *redir, int **fildes);
int			open_out_files(t_token *redir, int **fildes);
int			open_in_files(t_token *redir, t_token **tmpredir);
int			hdoc_or_rd_in(t_token *rdirlst, t_token *tmpredir, int **fildes);
int			*open_files(t_cmd cmd);
void		close_heredocs(t_tree *root);
void		set_fildes(int *files);

//	WRAPPERS + ERRORS
void		_wait(pid_t pid);
pid_t		_fork(void);
void		_error(char *file);
void		cmd_not_found(char *cmd);
void		cmd_error(char *lexeme);
int			is_a_directory(char *lexeme);
void		throw_error(char **paths, char *abs, char *lex, int i);

//	UTILS
int			is_append(t_node_type type);
int			is_rd_in(t_node_type type);
int			is_rd_out(t_node_type type);
int			is_hdoc(t_node_type type);
int			is_builtin(t_token *cmd);
void		default_fds(int **fildes);
size_t		tkn_lst_size(t_token *lst);
size_t		count_words(t_token *list);
size_t		lst_size(t_env *env);
size_t		env_size(t_env *env);
char		*cmd_prefix(char *lexeme, t_env *envp);
char		*check_path(char *lexeme, t_env *envp);
char		**build_vec(t_token *list, t_env *envp);
char		**build_env_vec(t_env *env);
char		**build_builtin_vec(t_token *cmd);
int			check_for_builtins(t_tree *node, t_env **env);
int			extract_status(void);

#endif
