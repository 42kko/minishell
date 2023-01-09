# minishell
make our mini shell
## Introduction
This mini-shell is an embodiment of bash in our own way.

## Run
1. brew install readline library</br>
If the brew is already installed
```
brew install readline
```
else
```
git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew
echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc
source $HOME/.zshrc
brew update
brew install readline
```
2. change Makefile library and Include
```
brew info readline
```
and copy and paste your readline Include path and Library path in this location
```
// Makefile

.c.o:		${SRCS}
			${CC} -I ${HEAD} -c $^ -o ${^:.c=.o} [your Include path]

${NAME}:	${OBJS}
			make -C ${LIBFT}/ 
			$(CC) $(CFLAGS) -I $(HEAD) -o $(NAME) ${OBJS} -L ./libft -lft [your Library path] -lreadline
```

3. make
```
make
```
4. execute
```
./minishell
```
