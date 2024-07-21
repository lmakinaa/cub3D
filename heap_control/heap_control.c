/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:10 by ijaija            #+#    #+#             */
/*   Updated: 2024/07/21 03:13:12 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap_control.h"

static void	del_from_session_part2(t_memsession *session, void *addr)
{
	t_memslot	*tmp;
	t_memslot	*first_node;

	first_node = session->head;
	while (first_node->next)
	{
		if (first_node->next->addr == addr)
		{
			tmp = first_node->next->next;
			free(first_node->next->addr);
			free(first_node->next);
			first_node->next = tmp;
			if (!first_node->next)
				session->tail = first_node;
			session->count--;
			return ;
		}
		first_node = first_node->next;
	}
}

/*
* Free a single address and removes it from the session list
*/
void	del_from_session(t_memsession *session, void *addr)
{
	t_memslot	*tmp;

	if (!addr)
		return ;
	if (session->head->addr == addr && session->head->next)
	{
		tmp = session->head->next;
		free(session->head->addr);
		free(session->head);
		session->head = tmp;
		session->count--;
	}
	else if (session->head->addr == addr && !session->head->next)
	{
		free(session->head->addr);
		free(session->head);
		session->head = NULL;
		session->tail = NULL;
		session->count--;
	}
	else
		del_from_session_part2(session, addr);
}

void	session_destroy(t_memsession **session_ptr)
{
	t_memslot	*first_node;
	t_memslot	*tmp;
	int			i;

	if (!(*session_ptr)->head)
		return (free(*session_ptr));
	first_node = (*session_ptr)->head;
	i = -1;
	while (++i < (*session_ptr)->count)
	{
		tmp = first_node;
		first_node = first_node->next;
		free(tmp->addr);
		free(tmp);
	}
	free(*session_ptr);
}

void	*session_malloc(t_memsession *session, size_t size, int erase)
{
	t_memslot	*new_slot;

	new_slot = malloc(sizeof(t_memslot));
	if (!new_slot)
		return (session_destroy(&session), exit_on_error(MALLOC_ERR, 24), NULL);
	new_slot->addr = malloc(size);
	if (!new_slot->addr)
		return (session_destroy(&session), exit_on_error(MALLOC_ERR, 24), NULL);
	if (erase)
		ft_bzero(new_slot->addr, size);
	new_slot->next = NULL;
	if (session->count == 0)
	{
		session->head = new_slot;
		session->tail = new_slot;
	}
	else
	{
		session->tail->next = new_slot;
		session->tail = new_slot;
	}
	session->count++;
	return (new_slot->addr);
}

/*
* M_ALLOC: uses malloc then stores and return its addresse (addr arg is ignored)
* M_DEL: free() an addresse and removes it from the addresses list (size and
* erase args are ignored)
* M_CLEAN: free() and removes all addresses allocated using this function (size,
* addr, erase args are ignored)
* erase: if passed 1, in the alloc mode, ft_bzero() will be called
* on the allocated memory
*/
void	*heap_control(int mode, size_t size, void *addr, int erase)
{
	static t_memsession	*session;

	if (!session)
		session_init(&session);
	if (mode == M_ALLOC)
		return (session_malloc(session, size, erase));
	else if (mode == M_DEL)
		return (del_from_session(session, addr), NULL);
	else if (mode == M_CLEAN)
		return (session_destroy(&session), NULL);
	return (NULL);
}
