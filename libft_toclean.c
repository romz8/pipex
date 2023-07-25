
#include "pipex.h"


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*concat;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	concat = malloc(s1_len + s2_len + 1);
	if (!concat)
		return (NULL);
	ft_memmove(concat, s1, s1_len);
	ft_memmove(concat + s1_len, s2, s2_len);
	concat[s1_len + s2_len] = '\0';
	return (concat);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dst, const void*src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *) dst;
	s = (unsigned char *) src;
	if (s < d)
	{
		while (len--)
			d[len] = s[len];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

static int	ft_wordcount(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (i > 0 && s[i] == c && s[i - 1] != c && s[i + 1] != 0)
			count++;
		i++;
	}
	return (count + 1);
}

static char	*word_insert(const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		i;
	int		wc;

	wc = ft_wordcount(s, c);
	if (!s)
		return (NULL);
	matrix = malloc((wc + 1) * 8);
	if (!matrix)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			matrix[i] = word_insert(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	matrix[i] = NULL;
	return (matrix);
}

/* NOW CLEAN : USED A LOT AND CREATED*/
void free_split(char **split_result)
{
    int i;

    if (!*split_result)
        return ;
    i = 0;
    while (split_result[i])
    {
        free(split_result[i]);
        i++;
    }
}

int split_len(char **split_result)
{
    int i;

    if (!*split_result)
        return (0);
    i = 0;
    while (split_result[i])
    {
        i++;
    }
    return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*cpy;

	len = ft_strlen(s1);
	cpy = malloc(len + 1);
	if (!cpy)
		return (NULL);
	cpy = ft_memcpy((void *) cpy, (const void *) s1, len + 1);
	return (cpy);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
}