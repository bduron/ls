
LS Specifications 
=================


Random notes : 
--------------
- manage duplicate **'/'** in file path, user can add or omit it.
	- ie.  `ls file1 file2/`  (avoid //file2) 
	



Default Behaviour : 
-------------------
### ls display order :
input: `ls 3 1 2 libft . auteur main.c auteur .`
```
ls: 1: No such file or directory
ls: 2: No such file or directory
ls: 3: No such file or directory
auteur auteur main.c

.:
Makefile    auteur      includes    libft       ls_specs.md main.c      srcs        tests

.:
Makefile    auteur      includes    libft       ls_specs.md main.c      srcs        tests

libft:
Makefile auteur   includes src
```

1. Error messages :
	- `ls: file: No such file or directory` 
	- sorted lexicographically

2. Files of the working directory `'.'`
	- w/ no newline before
