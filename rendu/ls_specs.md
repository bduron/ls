
ls specifications
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
	- lexicographically sorted 
		- *`💡: sort argv[]`*

2. Files arguments :
	- no newline before this section 
	- display duplicate files `auteur auteur`
	- lexicographically sorted   

3. Arguments directories content : 
	- newline before 
	- lexicographically sorted   
	- title: `directory_name:\n`
	- display duplicate directories  

