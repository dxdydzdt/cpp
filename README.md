# xio.h

This header includes implementations of some stuff like:
* An easy-to-use input function
* A console menu class and its builder

## Input
It can be used like this:

![](https://image.prntscr.com/image/G7UEXuKAR12FjB9-1HbJSw.png)

**Arguments**:
1. A **message** to the user.

2. A **lambda** or a **pointer to the function** that validates the entered data for your own conditions. It's optional...

And looks like this:

![](https://image.prntscr.com/image/d6bipdazQ8SFrH1IITd36g.png)

## Menu

It can be used like this:

![](https://image.prntscr.com/image/Ld7Ede7HQy2wKAtS-vQ81w.png)

**addItem()** takes two arguments:
1. Item text

2. A **lambda** or a **pointer to the function** that handles this item. It's optional and possible to be nullptr.

**build()** doesn't take any argument, **BUT**:
It always adds **Exit item** to the end of the list. This item hasn't any implemented function, that's nullptr. The implementation is in **handle()** function(see below).

**handle()**:
This func implements printing of the just created menu and handels the items.

### DO NOT FORGET TO FREE MEMORY ALLOCATED FOR THE MENU

And it looks like this:

![](https://image.prntscr.com/image/7TrNzy5xQLqznhi97uZx6Q.png)

![](https://image.prntscr.com/image/859OwzCpRmuUeWYWBbd5PQ.png)
