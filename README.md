# libeem
A set of C macros used to transform any struct into an event emitter!

## Why
By programming in an event-driven way, you often need to use some callbacks
and/or fire events in your application.  
I created this project in order to make this process easier.  

## How to use it?
It is **REALLY** simple.  

Just create a struct that contains an `eem_t` element with the `eem` name:  

```C
struct my_obj {
	eem_t eem;
	// Your data here.
};

struct my_obj mo;
```

And then init it with:  
```C
EEM_INIT(&mo);
```

To subscribe events:  
```C
EEM_ON(&mo, EVENT_ID, CALLBACK, ARG);
// or
EEM_ONCE(&mo, EVENT_ID, CALLBACK, ARG);
```  

To fire an event:
```C
EEM_EMIT(&mo, EVENT_ID, DATA);
```

The callback must look like this:  
```C
void callback(eem_ev_t *ev, void *arg)
{
	// Funny event handling code
}
```

## Examples
Just see the file `programs/example.c`. It is self-explaining.
