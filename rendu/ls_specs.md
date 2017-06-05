
ls specifications
=================


notes : 
--------------
- manage duplicate **'/'** in file path, user can add or omit it.
	- ie.  `ls file1 file2/`  (avoid //file2) 
- ls without arguments = `ls .`	
- empty string arg `""` produces error:  `ls main.c fakefile ""`
	- `ls: fts_open: No such file or directory` 


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

2. Files arguments :
	- no newline before this section 
	- display duplicate files `ie. auteur auteur`
	- lexicographically sorted   

3. Arguments directories content : 
	- newline before 
	- lexicographically sorted   
	- title: `directory_name:\n`
	- display duplicate directories  

💡  **Key takeaways**
```
+ lexicographically sort files
+ lexicographically sort directories
+ sort argv[] to display errors in the right order
```

### option flags conflits 
| ID    | Name | On   | Off |
| :---: |----- | :---:|:---:|
| -1 | Force output to be one entry per line | 1 (one) | l (ell) |
| -l | List in long format | l (ell) | 1 (one) |
| -R | Recursively list subdirectories | R |  |
| -a | Display directory entries beginning with a dot (.) | a |  |
| -r | Reverse lexicographicalorder or oldest entries first   | r |  |
| -t | Sort by time modified (recent first), then sort lexicographically  | t |  |


**Is there some kind of option flags precedence ?**

`bash-3.2$ ls -1l` *-l takes precedence over -1 as it comes after*
```
total 32
-rw-r--r--  1 benjaminduron  staff  1643 Jun  1 16:43 Makefile
-rw-r--r--  1 benjaminduron  staff     7 May 31 20:39 auteur
drwxr-xr-x  4 benjaminduron  staff   136 Jun  5 11:08 includes
drwxr-xr-x  6 benjaminduron  staff   204 Jun  5 11:09 libft
-rw-r--r--  1 benjaminduron  staff  1762 Jun  5 13:30 ls_specs.md
-rw-r--r--  1 benjaminduron  staff  2996 Jun  1 12:22 main.c
drwxr-xr-x  6 benjaminduron  staff   204 Jun  5 11:08 srcs
drwxr-xr-x  4 benjaminduron  staff   136 May 31 20:39 tests
```

`bash-3.2$ ls -l1` *then -1 takes precedence over -l as it comes after*
```
Makefile
auteur
includes
libft
ls_specs.md
main.c
srcs
tests
```

💡  **Key takeaways**
```
+ flags seem to be activated in the order they are encountered. So no precedence apply. 
```

### -R recursive subdirectories listing


### Links following

When encountered during a recursive subdirectories listing (-R), by default, symlinks are not followed

`ls -lR`
```
total 0
drwxr-xr-x  4 benjaminduron  staff  136 Jun  5 16:41 dirA
drwxr-xr-x  5 benjaminduron  staff  170 Jun  5 16:50 dirB
-rw-r--r--  1 benjaminduron  staff    0 Jun  5 16:43 rootFile01

./dirA:
total 8
lrwxr-xr-x  1 benjaminduron  staff    7 Jun  5 16:41 link2dirB -> ../dirB
drwxr-xr-x  3 benjaminduron  staff  102 Jun  5 16:34 subdirA

./dirA/subdirA:
total 0
-rw-r--r--  1 benjaminduron  staff  0 May 31 20:39 fileA

./dirB:
total 0
-rw-r--r--  1 benjaminduron  staff    0 May 31 20:39 hello00
d---------  3 benjaminduron  staff  102 Jun  5 16:37 nopermdir
----------  1 benjaminduron  staff    0 Jun  5 16:35 nopermfile

./dirB/nopermdir:
ls: nopermdir: Permission denied
```

**Symlink as ls argument :**

`ls link2dirB`
```
hello00    nopermdir  nopermfile
```

`ls -l link2dirB`
```
lrwxr-xr-x  1 benjaminduron  staff  7 Jun  5 16:41 link2dirB -> ../dirB
```
  
💡  **Key takeaways**
```
+ By default links are not followed during a -R recursion
+ If passed as a ls argument without options, ls display the linked directory content
+ If passed as a ls argument with -l option, ls display the link infos
```
	


Testing ls :
------------
Here are some interesting commands to test 

```
ls /etc ; ls -l /etc
ls -l /dev
ls 5 1 4 2 3
ls valid files + 5 1 4 2 3
mkdir mydir; chmod 000 mydir; ls -l mydir
ls -lat
ls -lratR
```



Algorithm :
----------

Key data structures:
- next directories list (dirs)
- current directory entries list (ents)

```   
PARSE ARGV 
----------
output if argv empty :
	ents [NULL]
	dirs ["."]
output if argv !empty :
	ents [files + dirs] sorted
	dirs [dirs] sorted
		in this case :
			display ents
			delete ents 	

LS LOOP
-------
while (dirs != NULL) 
	pop currentdir from dirs 
	get currentdir entries: ents [file, file, dir, file, ...]
	if -R		
		+ get nextdirs from currentdir: nextdirs [dir, dir, dir, ...]				
		sort nextdirs
		dirs = merge nextdirs + dirs 	
	compute ents (sort, ...) 
	display ents 
	deletes ents 		
	go to the next dir in dirs 
	
```		
