This will be a simple Database system. 
It will include the following features

1) The ability to select, insert, update, and delete records
2) The ability to define tables as json files

This db is intended to be highly performant, lightweight, low to medium volume, and extremely reliable.
All columns will be indexed by default, unless specifically told not to be (do so for large blobs)


Key:
-> invokes
x exits

Structure:

Main.c  
    -> ReadSchema.c
    -> ProcessManager.c
        -> DataHost.c
        -> Interface.c
    x