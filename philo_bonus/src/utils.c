/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:39:08 by tmina-ni          #+#    #+#             */
/*   Updated: 2024/05/13 00:33:40 by tmina-ni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest <= src)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			((unsigned char *)dest)[i - 1] = ((unsigned char *)src)[i - 1];
			i--;
		}
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memmove(ptr, s1, s1_len);
	ft_memmove(&ptr[s1_len], s2, s2_len);
	ptr[s1_len + s2_len] = '\0';
	return (ptr);
}

char	*ft_utoa(unsigned int n)
{
	long	lnb;	
	size_t	len;
	char	*ptr;

	lnb = n;
	len = 0;
	if (lnb == 0)
		len = 1;
	while (lnb > 0)
	{
		lnb = lnb / 10;
		len++;
	}
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[len--] = '\0';
	lnb = n;
	if (lnb == 0)
		ptr[len] = '0';
	while (lnb > 0)
	{
		ptr[len--] = (lnb % 10) + '0';
		lnb = lnb / 10;
	}
	return (ptr);
}

pid_t	ft_fork(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close_shared_semaphores(data);
		unlink_shared_semaphores();
		free(data->philo_pid);
		exit(FORK_ERROR);
	}
	return (pid);
}
