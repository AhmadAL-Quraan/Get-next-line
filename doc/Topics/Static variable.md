
* Memory is separated into layers:
![[Pasted image 20260107175447.png]]

* The static variable is stored in the [[#Data segment]] (Uninitialized Data, Initialized Data).
	* We can use static variables to make a variable live long when make in any function.


# Data segment

 * Holds initialized global and static variables.
	 * Initialized Data: variables with initial values.
	 * BSS (Block started by symbol): uninitialized global/static variables.



>[!note] static variables because they are stored in Data segment, they are unlike stack which remove the memory address of the var after the function is finished.





