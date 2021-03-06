https://shibboleth.insa-cvl.fr/idp/Authn/UserPassword
https://controller.access.network/101/portal/

# NODE.JS		
### DEBUGGER
**Debug via command line**
Run in terminal to get access to debug environment
```
node inspect FILENAME.js 		OR
nodemon inspect FILENAME.js		RECOMMENDED !!!
n		execute next line code
c		execute all the line code below
```
If we want to stop and see value of variable at someline
```
repl
VARIABLE
```
If we dont want to use n to go a line specified, write "debugger;" above
the line we want to stop in debug
```
node inspect FILENAME.js
c
```
and the debug will stop at debugger

**Debug via Chrome tools**
RECOMMENDED !!!!
```
node --inspect-brk FILENAME.js	OR
nodemon --inspect-brk FILENAME.js	RECOMMENDED !!!
```
Debugger listening on ws://127.0.0.1:9229/3982861c-0661-4bcf-8eba-ded08ea9c002

- Then we will go to chrome, type chrome://inspect and hit Enter
(chrome://version for more info about the version of your Chrome)
- Under Remote Target, we should have one target, that is our target of debugging (we dont want to click that)
- We click "Open dedicated DevTools for Node"
- The console bar (at the end) is like repl (we can run our code here)
### NOTION OF NODE.JS
**Synchronous**
One line run after the next

**Event driven**

**Non blocking**
The application can do other thing while waiting a long running process to complete

**Single threaded**

**Call Stack**
- Running function in our main()
- The job of call satck is to track the execution of our program and is does that by keeping track of all of the functions that are currently running
- Tennis ball structure data: You can add something onto the top of the list and you can remove the top item< But you cant remove or add something at the middle, or the bottom of the tennis ball can.

**Callback Queue**
- Callback Queue is a strandard line, you add function at the end of the line and the function at the front of the line will be executed first (like a queue of people at fastfood store - KFC)
- The function of Callback Queue is maintain a list of function is already to execute (functions in Node APIs)


**Event Loop**
- The function of Event Loop is to look at the Call Stack and the Callback Queue. If the Call Stack is empty, the functions in Callback Queue will be added to Call Stack and be executed.
- Call Stack > Callback Queue

**Object Property Shorthand**
- If an object has the name of value of property is exactly the same name of property, we can just erase the property name
```
user = {name: name} can be transform to 
user = {name}
```
**Destructuring**
If we want to store the value of some properties of an object, we can use destructuring like:
```
{label:myLabel, stock} = product;
```
to store the value of property "label" of product to variable "myLabel" and value of property "stock" of product to variable "stock"

---

# GIT
------ How to integrate Git to your project at VS Code ? ------

- We need to run the command line at the root project folder which is "web server"

> git init	to initialize git in our project
this command will initialize a .git folder that store everything about your project

> git status	to get the status of all file in our project (Untracked Files, Unstagged Changes, Staged Changes, Commits)

------------------------------------------------------
!! Attention : You don't want track node_module file in git
- To ignore a file in our project, you have to create a file name ".gitignore"
- In this file, we can write node_modules/ to ignore node_module in the futur
------------------------------------------------------

> git add src/		will add all files in src/ folder to the stagged area
> git add .		will add all untracked files which show up in git status command line

> git commit -m "Init commit"	commit all files in stagged area to git cloud


-----------------------------------------------
- After modified and make changes to our file, we have some "modified file" that we need to add it to the stagged area
> git add .
> git commit -m "Modified something"


***************** SSH (secured shell)***************************

----------------- Set up SSH key -------------------------------
> ls -a -l ~/.ssh		to looking for .ssh file in our project
we are going to create a SSH key inside .ssh file

> ssh-keygen -t rsa -b 4096 -C "laminhduc07041@gmail.com"		to generate ssh key
-b is for the bit we want to use (4096 bits) the higher the bit are, the more secure you have
-C is for comment, usually we want to add our email
After you just hit enter with default configuration: file to save key, no passphrase

We can use the command line up above to look into our ssh file 
	* id_rsa is the private key file in our local machine, NOT SHARE TO ANYONE
	* id_rsa.pub is public key that we want to share with GitHub or Heroku to secure the communication
	between our machine and their servers

> eval "$(ssh-agent -s)"	to register our new private key file
> ssh-add ~/.ssh/id_rsa		to register the key to these id_rsa files 


*************************
*	     GITHUB 	    *
*************************

> git remote add origin https://github.com/lala74/node3-weather-website.git
to create a new line of communication between your code and GitHub repositoty
You can imagine that is like adding a new contact to your mobile phone
	* origin is the name of the contact
	* https://github.com/lala74/node3-weather-website.git is phone number

We need set up a new SSH key in your GitHub account to be able to push our code to GitHub
-> github.com -> setting -> SSH and GPG keys -> new SSH keys
	* Title: Home Laptop
	* Key : content in > cat ~/.ssh/id_rsa.pub
-> Add new keys

To test if our key has been setup successfully
> ssh -T git@github.com 	and then type yes


> git push -u origin master
to push our code to the GitHub repositoty

*************************
*	     HEROKU 	    *
*************************

> heroku keys:add		to add ssh key to heroku account

> heroku create la-weather-application			to create new application in heroku server
and heroku will give to us 2 URLs:
	* the first one is live URL to our app 
	* the second one is URL for git repository that we should push our code in

--------------------------------------------------------------------- 
!!! ATTENTION: to get heroku know which file to execute to make 	|
our app run, we change make some changes in "package.json file"		|
	- We can remove "test" line in "scripts" and add our scripts	|
	- Add "start" object to "scripts":								|		
		 	"scripts": {											|
   				 "start" : "node src/app.js"						|
  			},														|
	(Now we can use > npm run start 	to run our app)				|
	- We have to change "app.listen()" at "app.js"					|
			const port = process.env.PORT || 3000;					|
			app.listen(port, () => {								|
    			console.log('Server is up on port ' + port);		|
			});														|
	- Now the final change in in client side: public/js/app.js		|
		- We need clear localhost::3000 in "url" variable:			|
			var url = '/weather?address=' + location;				|
    		fetch(url).then((respond) => { }						|
---------------------------------------------------------------------


****************** RESUME *******************************
> git add .
> git commit -m "Set up app for heroku"
> git push

> git remote		we can see that heroku are created another branch name "heroku" for us
> git push heroku master
*********************************************************
