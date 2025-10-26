#### Header Files
- header thing
- ```
  /*
  This is a large multi-line comment that tells the reader what the file does.
  It mentions what settings to toggle in the IOC, what peripherals it uses, which pins.
  It also mentions what functions to use and anything else important such that 
  someone else can use it in their project
  */*
  ```
- "include guards"
- include necessary .h
	- Find the specific stm header file that defines things like GPIOB/TIM2, don't include `main.h` like we did in onboarding, it was just quick and easy
- define macros and enums
- declare only public functions that are used in other c files

#### C Files
- include its .h file. Should be the only include statement here, other includes go in header file
- Try to limit use of global variables. Name the global variable in a way that makes it clear it is a global var.

#### Functions
- For drivers, include an `init()` function
- Public functions should take in as little arguments as possible

#### Drivers
- Make it modular. Depending on the peripheral used, you can use a few different pins for it (Alternate Functions) Write the driver such that the user can easily change which pins are used.