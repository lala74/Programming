# JAVA <!-- omit in toc -->

- [1. Installation](#1-installation)
	- [1.1. Set up Java and Java Compiler in terminal](#11-set-up-java-and-java-compiler-in-terminal)
	- [1.2. Install IntelliJ](#12-install-intellij)
	- [1.3. Configure](#13-configure)
- [2. Knowledge](#2-knowledge)
	- [2.1. Data type](#21-data-type)
	- [2.2. Casting](#22-casting)
- [3. Error](#3-error)
- [4. Vocabulary](#4-vocabulary)
- [5. METHOD](#5-method)
	- [5.1. Definition](#51-definition)
	- [5.2. Method Overloading](#52-method-overloading)
- [6. CONTROL FLOW STATEMENTS](#6-control-flow-statements)
		- [6.0.1. SWITCH](#601-switch)
		- [6.0.2. FOR](#602-for)
	- [6.1. Parse String to an integer](#61-parse-string-to-an-integer)
- [7. READING USER INPUT](#7-reading-user-input)
- [8. Array](#8-array)
- [9. ArrayList](#9-arraylist)
		- [9.0.1. Function in ArrayList](#901-function-in-arraylist)
		- [9.0.2. Autoboxing and Unboxing](#902-autoboxing-and-unboxing)
- [10. Linked List](#10-linked-list)

## 1. Installation

Download Java 11 (LTS) in oracle site: tar.gz file
Go to the folder which have .tar.gz file

```bash
tar -xvf filename.tar.gz	unzip file
sudo mkdir -p /usr/lib/jvm/jdk-11/
```

Create a sub-folder to store JDK (help IntelliJ to find JSK sub-folder

```bash
sudo mv jdk-11/* /usr/lib/jvm/jdk-11/
```

Move all content in jdk-11 to our new sub-folder

### 1.1. Set up Java and Java Compiler in terminal

```bash
sudo update-alternatives --install "/usr/bin/java" "java" "/usr/lib/jvm/jdk-11/bin/java" 1010
```

Set up to run Java on terminal

```bash
> java -version		to check the version
> sudo update-alternatives --install "/usr/bin/javac" "javac" "/usr/lib/jvm/jdk-11/bin/javac" 1010
```

Set up to run Java Compiler on terminal

### 1.2. Install IntelliJ

Download IntelliJ in jetbrains.com
Extract file
Goto /bin  -> open in terminal

```bash
./idea.sh &
```

Now the IntelliJ is installing
-> OK -> Accept -> Don't send -> Next: Desktop Entry
-> Next: Launcher Script 
-> Check "Create a script ...." and Next: Default plugins
-> Next: Futured Plugins -> Start using IntelliJ
Now we have IntelliJ IDE in our Ubuntu

### 1.3. Configure

-> Structure for new project

**Add a new JSK**

- Go to option Project in Project Settings
- Click New and navigate to /usr/lib/jvm/jdk-11
- Click OK
- In Project Language level: selec 11 - Local variable....

**Make IntelliJ easier to use**

- Configure -> Setting
- Edior -> General 
-> Auto Import
- Check Add unambiguous
- Check Optimize imports
-> Code Folding	- To see all code
- Uncheck Import
- Uncheck One-line methods
- Uncheck Closures
- Uncheck Generic constructor

---

## 2. Knowledge

### 2.1. Data type
You can write 2_258_456_123 to make large number more easy to read (only wolk above java 7)

 For long data 
 ```
long myLongValue = 316464L;         It ends with an L
```
Double (8 bytes) is more precise than float (4 bytes)
You can write:
```
double pi = 3.141_592_7d 
```
In Java, when you make a assignement (like an equation), Java will automatically change the data type to "int" or "long" or "double" (not float)
```
byte value = myByteNum/2 will occurs a type error (byte = int)
```
We don't need to use casting in long and int data type

### 2.2. Casting
```
(byte) (myByteNum/2)
```
**!!! Important: prefer using "int" or "long" and "double" in our code**

---

## 3. Error
```
boolean isDuc = true;
if (isDuc = true)	will automatically return true 

int test = 50;
if (test = 50)		will automatically return 50 (which is an error)

boolean wasCar = isCar ? true:false;
```

---
## 4. Vocabulary
Keyword : int, long, double
Expression : variable, value and operator
```
km = mile * 1.609; 		is an expression
```
Statement : a completely line
```
int km = mile * 1.609 	is a statement
```
Indentation : a Tab space in your code
```
if (km < 20) {
	km = 30;	there is an indentation
}
```
Codeblock : everything between { }
Scope : variable inside a codeblock

---

## 5. METHOD

### 5.1. Definition
To create new class in Java, right-click "src" file in Project -> new -> Java Class
In class we define the method
```
public class LeapYear {	// this is a class
    public static boolean isLeapYear(int year) {	// this is a method in class
    }
}
```
We can access method in a class using className.methodName;

### 5.2. Method Overloading
We can define 2 methods with the same name but different in parameter
to re-use that method
```
public static int calculate(String playerName, int score)
public static int calculate(int score)
```
We created 2 methods calculate different in parameter.

---

## 6. CONTROL FLOW STATEMENTS
#### 6.0.1. SWITCH
```
switch (switchValue) {
	case 1:
		sout;
		break;
	case 2: case 3: 
	default:
		sout;
		break;
}
```
#### 6.0.2. FOR
```
for(int i=0;i<5;i++) { }
```
### 6.1. Parse String to an integer
```
int number = Integer.parseInt(stringNumber);
```
We use class Integer

*****************************************
## 7. READING USER INPUT
```
Scanner scanner = new Scanner(System.in);	// create an instance of Scanner Class
sout("Enter your year of birth : ");	// get your yearOfBirth as an Integer
int year = scanner.nextInt();
scanner.nextLine();			// to handle next line character (Enter)

sout("Enter Your Name : ");			
String name = scanner.nextLine();	// get your input
scanner.close();			// close scanner

scanner.hasNextInt();			// check if the input number is integer or not
```
***
## 8. Array
```
int[] myIntArray = new int[len];
```
***
## 9. ArrayList
```
private ArrayList<Double> transactions = new ArrayList<Double>();
```
#### 9.0.1. Function in ArrayList
```
transactions.size();				// return size of list
transactions.contains(element);		// check if list contain element
transactions.add(element);			// add an element to the end of list
transactions.indexOf(element);		// return index of element (>0) if return < 0 => there is no element in list
transactions.get(position);			// get element at this position
```
***
#### 9.0.2. Autoboxing and Unboxing
[https://docs.oracle.com/javase/tutorial/java/data/autoboxing.html](https://docs.oracle.com/javase/tutorial/java/data/autoboxing.html)
`Autoboxing` is the automatic conversion that the Java compiler makes between the primitive types and their corresponding object wrapper classes.
Ex: converting int to Interger and double to Double
```
We can't write like so:
	ArrayList<int> Dette;
But we can write :
	ArrayList<Integer> Dette;
```
Because int is not an object or class but Integer is.

`Unboxing` is the conversion from Integer to int

 ***
## 10. Linked List
How String contain variable:
![Imgur](https://i.imgur.com/2jSmnlQ.png)
**Avantage**: If we have a large number of element store in an array and we decide to delete one element. All the other elements below that element has to move up 1 position to fill the gap so it's a huge amount of process.
=> With linked list, when delete an element (2nd element), there is only one process to do. (connect the end of 1st element and the begin of 3rd element)

