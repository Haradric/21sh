/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 16:31:01 by mbraslav          #+#    #+#             */
/*   Updated: 2017/07/05 16:31:03 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "shell.h"

# define HIST_SIZE 20

# define KEY_ESC 0x1B
# define KEY_UP 0x415B
# define KEY_DOWN 0x425B
# define KEY_RIGHT 0x435B
# define KEY_LEFT 0x445B
# define KEY_DEL 0x7E335B
# define KEY_BACKSPACE 0x7F
# define KEY_ALT_LEFT 0x445b1b
# define KEY_ALT_RIGHT 0x435b1b
# define KEY_ALT_UP 0x415b1b
# define KEY_ALT_DOWN 0x425b1b
# define KEY_HOME 0x485b
# define KEY_END 0x465b

typedef struct	s_term
{
	int			rows;
	int			cols;
	char		*prompt;
	t_list		*entry;
	char		*cursor;
}				t_term;

t_list			*hist_new_entry(void);
t_list			*hist_add_entry(t_list **hist);
void			hist_switch_to_entry(t_list **current, t_list *new, \
										t_term *term);

void			init_terminal_data(void);
void			interrogate_terminal(t_term *info);

void			read_input(t_term *term);
char			*add_to_entry(t_list *entry, char c, char *cursor);
char			*remove_from_entry(t_list *entry, char *cursor);
void			edit_entry(char c, t_list *entry, t_term *term);

void			input_validate(t_list *entry);

void			cursor_move(t_list *entry, int spaces, t_term *term);
void			cursor_to_start(t_list *entry, t_term *term);
void			cursor_to_end(t_list *entry, t_term *term);
void			cursor_word_left(t_list *entry, t_term *term);
void			cursor_word_right(t_list *entry, t_term *term);
void			cursor_str_up(t_list *entry, t_term *term);
void			cursor_str_down(t_list *entry, t_term *term);

void			key_handle(t_list **entry, t_term *term);
void			key_handle_left(t_list *entry, t_term *term);
void			key_handle_right(t_list *entry, t_term *term);
void			key_handle_backspace(t_list *entry, t_term *term);
void			key_handle_delete(t_list *entry, t_term *term);

void			enable_keypress(struct termios *settings);
void			disable_keypress(struct termios *settings);
ssize_t			get_key(char *buff, size_t size);

#endif
