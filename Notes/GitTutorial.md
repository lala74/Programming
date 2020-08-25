change by Duc - 3

********
# Git
```
sudo apt-get install git	:	install git
```
**Configuration git**
```
git config --global user.name "Your Name"
git config --global user.email "youremail@gmai.com"

git config --list		:	check out configuration
```

******** 
# REPOSITORY
```
git init name_repository	:	creat a new local repository
git add name_file_untracked	:	add file to Staging Area
git commit -m "Your Msg"	:	commit all file in Staging Area to Server
git clone URL_remote_repository	:	clone a remote repository to Your Computer
```
**Add a file README.md in clone repository to server**
```
cd name_clone_repository
echo "# Huong dan Git co ban" > README.md
git add README.md
git commit -m "First commit on Github"
git push origin master	:	push data to server
```
********
# COMMIT & STAGING AREA
```
git status		:	get status of files in repository
rm name_file		:	change status of a file from tracked to untracked
rm -f name_file	:	remove forever a file
```
********
# GIT LOG
```
git log		:	watch git log of commit action
git log -p		:	watch git log (detail)
```
**How to watch git log more beautiful**
```
git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"

git lg
```
**** 
# TAG
```
git tag name_tag	:	add Lightweight Tag
git tag -a name_tag -m "Your Msg"	: 	add Annotated Tag

git tag		:	show all tags
git show name_tag	: 	show information of a tag
```
**How to add tag for an old commit**
```
git log --pretty=oneline	:	show checksum code
git tag -a name_tag checksum_code -m "Your Msg"

git push --tags		:	push all tags to server

git checkout -b version1 v1.0	:	creat a new branch with all the datas tagged v1.0
```
*****
# REMOTE REPOSITY
```
git push origin master              - origin is the name of a remote repository (repository on server)
git remove -v		:	check name remote
```
- fetch	:	get data from server
- push	:	send data to server
```
git remote rename old_name new_name	:	change name of remote reposity

git remote add new_name URL	:	add a remote to server

git fetch name_remote		:	get data from remote reposity
- data received is saved to database of Git, it's not added to local reposity

git merge name_remote		:	add data received from remote reposity to local reposity

git pull name_remote		:	get data direct from remote to local
```
*******
# BRANCH
```
git branch -a		:	list all branches
git branch new_name	:	add a new branch
git checkout name_branch	:	access branch
```
**Transfer data from branch "develop" to "master"**
```
git checkout master
git merge develop
ls
git branch -d name_branch   	: 	delete a branch
- attention !!! branch is deletable when its datas are merged to branch master

> git remote show name_remote_repository(origin)	: show all branch of an remote
```
****
# .gitignore
## Why my .gitignore doesn't work property ?
https://stackoverflow.com/questions/3833561/why-doesnt-git-ignore-my-specified-file/3833675

When a file is tracked (by git add), it can't be ignored by .gitignore. We have to remove it from the repository
```
git rm -r --cached path/file/
```
This will remove file from the repository without deleting the physical file.

*****
# FETCH DATA FROM ANOTHER BRANCH TO A BRANCH
**We fetch data of branch "branch_of_old_remote" of remote "old_remote" to "branch_of_new_remote" of remote "new_remote"
```
git remote add new_remote URL_of_remote     	// creation of new_remote
git remote -v				                	// show info of all remote
                                            	// verifire whether or not we have created a new remote
git branch branch_of_new_remote	            	// creattion of new branch
git checkout branch_of_new_remote	        	// access to new branch
git pull old_remote branch_of_old_remote	    // fetch data
```

### Pour l'erreur de basculation entre les branches par les fichiers .metadata
```
git checkout -q	                             	// supprimer l'état d'avancement
git checkout master
git checkout .metadata/.*                   	// annuler la modification dans les fichier .metadata
git checkout --track remotes/origin/sensor  	// checkout la branche sensor
```
******
# Setting SYNC
```
aa2752eb0f3c411fb4264f7ad76c7e74782c9bd6
```
****** 
# UNDO
### Undo add
```
> git reset FILENAME
```
### Undo commit
```
git commit --amend -m "Your Msg"	:	undo commit action
```

****
# Change remote URL
https://help.github.com/en/articles/changing-a-remotes-url
```
git remote -v                           to display your current URL for fetch/push
git remote set-url origin YOUR_URL      to change current URL to desire URL
```
***
# Commit your changes or stash them before you can merge”?
https://stackoverflow.com/questions/15745045/how-do-i-resolve-git-saying-commit-your-changes-or-stash-them-before-you-can-me 
**Commit the change using**
```
git commit -m "My message"
```
**Stash it**
Stashing acts as a stack, where you can push changes, and you pop them in reverse order.
To stash, type
```
git stash
```
Do the merge, and then pull the stash:
```
git stash pop
```
**Discard the local changes**
```
git reset --hard
git checkout -t -f remote/branch
```
**Or: Discard local changes for a specific file**
```
git checkout filename
```
.
.
.
.
.
.
.
.
.
.
.
.
.














