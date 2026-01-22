#include "get_next_line.h"

static void cut(int *idx, char *full_string, char *new_string) {
  while (full_string[*idx] && full_string[*idx] != '\n') {
    new_string[*idx] = full_string[*idx];
    (*idx)++;
  }
  if (full_string[*idx] == '\n') {
    new_string[*idx] = full_string[*idx];
    (*idx) += 1;
  }
  new_string[*idx] = '\0';
}

static char *cut_the_rest(char *string) {
  int idx;
  char *temp;

  if (!string)
    return (NULL);
  idx = 0;
  while (string[idx] && string[idx] != '\n')
    idx += 1;
  if (string[idx] == 0) {
    free(string);
    return (NULL);
  }
  temp = ft_substr(string, idx + 1, ft_strlen(string) - idx);
  if (!temp || *temp == 0) {
    free(temp);
    temp = NULL;
  }
  free(string);
  return (temp);
}

static char *give_the_line(char *full_string) {
  int idx;
  char *new_string;

  if (!full_string)
    return (NULL);
  idx = 0;
  while (full_string[idx] && full_string[idx] != '\n')
    idx += 1;
  if (full_string[idx] == '\n')
    idx += 1;
  new_string = malloc(idx + 1);
  if (!new_string)
    return (NULL);
  idx = 0;
  cut(&idx, full_string, new_string);
  return (new_string);
}

static char *read_file(int fd, char *full_string, char *temp) {
  int bytes_of_read;
  char *ptr;

  bytes_of_read = 1;
  while (bytes_of_read > 0) {
    bytes_of_read = read(fd, temp, BUFFER_SIZE);
    if (bytes_of_read < 0) {
      free(temp);
      free(full_string);
      full_string = NULL;
      return (NULL);
    }
    if (bytes_of_read == 0)
      break;
    temp[bytes_of_read] = '\0';
    ptr = ft_strjoin(full_string, temp);
    free(full_string);
    full_string = ptr;
    if (ft_strchr(full_string, '\n'))
      break;
  }
  return (full_string);
}

char *get_next_line(int fd) {
  char *temp;
  static char *full_string;
  char *new_line;

  if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, NULL, 0) < 0)
    return (NULL);
  temp = malloc(BUFFER_SIZE + 1);
  if (!temp)
    return (NULL);
  if (!full_string)
    full_string = ft_strdup("");
  full_string = read_file(fd, full_string, temp);
  free(temp);
  temp = NULL;
  if (!full_string || full_string[0] == '\0') {
    free(full_string);
    full_string = NULL;
    return (NULL);
  }
  new_line = give_the_line(full_string);
  full_string = cut_the_rest(full_string);
  return (new_line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
//
// 	fd = open("file.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	printf("%s", get_next_line(-1));
// 	close(fd);
// }
