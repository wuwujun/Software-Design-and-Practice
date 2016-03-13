# Software-Engineering-Homework
Task1
------------
    Task1 are Software Engineering Homework in the first two week, 
    which includes the skip list, k-m-p algorithm, priority queue, and the matrix transpose.
### SikpList
* Simple option list:

        printf("### Function Test ###\n");
        printf("Please chose one point:\n");
        printf("1.Insert\n");
        printf("2.Delete\n");
        printf("3.Search\n");
        printf("4.Exit\n");

`Every option is connected to a particular function.`
	
* Test example:

`For convenience, I set a array in code directly:`
        
        int num[7] = {4, 6, 3, 2, 5, 9, 7};
        
`Use this to initialize the skip list:`
        
        for (i = 1; i < 8; i++)
	    {
		    l = insert(l, num[i - 1], i);
	    }
        
    
    
    
