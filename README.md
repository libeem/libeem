# libeem
A set of C macros used to transform any struct into an event emitter!

## Why
By programming in an event-driven way, you often need to use some callbacks
and/or fire events in your application.  
I created this project in order to make this process easier.  

## How to use it?
It is **REALLY** simple.  
Just create a struct that contains an `eem_t` element with the `eem` name.  
Like:
```c
struct my_obj {  
	eem_t eem;  
	// Your data here.  
}  
```


## Examples
Just see the file `programs/example.c`. It is self-explaining.
