package transpositions;

public class Transpositions 
{
    public static void main(String[] args) 
    {
        bitRep(6);
        fullRep(6);
        replacements(6);
    }   
    
    
    
    public static void bitRep(int size)
    {
        int[] a = new int[size]; //transposition
        for (int i = 0; i < size;) a[i] = ++i;
        int[] b = new int[size]; //copy
        Operations.duplicateArray(a, b);
        Operations.shuffle(b);
        Operations.printArray(a);
        Operations.printArray(b);
        //int[] a = {0, 1, 2, 3, 4, 5, 6};
        //int[] b = {2, 1, 6, 4, 0, 5, 3};
        
        for (int i = 0; i < a.length; i++) System.out.println(a[i] + " " + b[i] + " " + b[Operations.firstIndexOf(a, b[i])]);
    }
    public static void fullRep(int size)
    {
        int[] a = new int[size]; //transposition
        for (int i = 0; i < size;) a[i] = ++i;
        int[] b = new int[size]; //copy
        Operations.duplicateArray(a, b);
        Operations.shuffle(b);
        Operations.printArray(a);
        Operations.printArray(b);
        System.out.println();
        //int[] a = {0, 1, 2, 3, 4, 5, 6};
        //int[] b = {2, 1, 6, 4, 0, 5, 3};
        
        for (int i = 0; i < a.length; i++)
        {
            int iA = i;
            System.out.print(a[iA] + " ");
            for (int c = 0; c < 5; c++)
            {
                System.out.print(b[iA] + " ");
                iA = Operations.firstIndexOf(a, b[iA]);
            }
            System.out.println();
        }
    }
    
    public static void replacements(int size)
    {
        int[] a = {0, 1, 2, 3, 4, 5, 6};
        int[] b = {2, 1, 6, 4, 0, 5, 3};
        
        for (int i = 0; i < a.length; i++)
        {
            int iA = i, iB = iA;
            if (Operations.firstIndexOf(b, a[iA]) != -1)
            {
                System.out.print(a[iA] + " ");
                while(a[iA] != b[iB])
                {
                    if(b[iB] != Integer.MIN_VALUE && a[iA] != Integer.MIN_VALUE)
                    {
                    System.out.print(b[iB] + " ");
                    int copy = iB;
                    iB = Operations.firstIndexOf(a, b[iB]);
                    b[copy] = Integer.MIN_VALUE;
                    }
                    else break;
                }
                System.out.println();
            }
        }
    }
 }
