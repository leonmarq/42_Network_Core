/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 20:16:08 by leon              #+#    #+#             */
/*   Updated: 2026/07/01 10:51:00 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_action
{
	CODER_INIT,
	CODER_REQUEST,
	CODER_TAKES,
	CODER_COMPILE,
	CODER_DEBUG,
	CODER_REFACTOR,
	CODER_BURNOUT,
	CODER_COMPLETED
}					t_action;

typedef enum e_scheduler
{
	FIFO,
	EDF
}					t_scheduler;

typedef enum e_dongle_state
{
	D_FREE,
	D_USED,
}					t_dongle_state;

typedef struct s_dongle_center
{
	pthread_mutex_t	mutex;
	pthread_cond_t	changed_cond;
	t_scheduler		scheduler;
	long long		count;
	long long		cooldown;
	long long		ticket;
	int				stopping;
}					t_dongle_center;

typedef struct s_shared
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	t_dongle_center	dongle_center;
	int				coders_down;
	int				coder_down;
	struct timeval	start_time;
}					t_shared;

typedef struct s_dongle
{
	int				id;
	t_dongle_state	state;
	struct timeval	time_released;
}					t_dongle;

typedef struct s_coder
{
	int				id;
	int				n_of_p;
	t_dongle		*dongle_left;
	t_dongle		*dongle_right;
	struct s_coder	*lefty;
	struct s_coder	*righty;
	long			time_req;
	struct timeval	ts_last_cp;
	pthread_t		thread;
	long long		debug;
	long long		compile;
	long long		refactor;
	long long		death;
	int				loops;
	int				i_loop;
	int				done;
	int				dead;
	t_action		state;
	long long		prio;
	long long		arrival_order;

	t_shared		*shared;
}					t_coder;

typedef struct s_data
{
	long long		n_of_p;
	long long		time_bo;
	long long		time_cp;
	long long		time_db;
	long long		time_rf;
	long long		nb_req_cp;
	long long		dongle_cd;
	int				end_of_exe;
	t_scheduler		scheduler;
	pthread_t		monitor;
	t_coder			*coders;
	t_shared		shared;
}					t_data;

int					init_data(char *argv[], t_data *data, int argc);
void				*life(void *p_v);
long long			time_ms(struct timeval start);
long				time_diff(struct timeval start, struct timeval end);
long				time_until(struct timeval end);
long				time_to_long(struct timeval ts);
struct timeval		add_time(struct timeval ts, int ms);
int					time_loop(t_coder *p);
int					terminate_all(t_coder *p);
int					p_set_dead(t_coder *p);
int					check_if_dead(t_coder *p);
int					m_printf_func(t_coder *p, t_action i);
int					print_instructions(void);
void				*ft_calloc(long long nmemb, long long size);
int					all_coders_down(t_data *data);
int					cleanup(t_data *data);
int					enter_waiting(t_coder *p, struct timeval ts);
int					scheduled_best_option(t_coder *p);
void				*monitor(void *arg);
int					check_args(char *argv[], int argc);
int					update_states(t_coder *p, t_dongle_state state);
int					both_dongles_available(t_coder *p);
int					broadcast_stop(t_dongle_center *dc);
int					failed_malloc_cleanup(t_coder *coder, int i);
int					cleanup_failed_thread(t_data *data, int i);
int					cleanup_below(t_data *data, int i);
int					destroy_all_pthread(t_data *data);

#endif
