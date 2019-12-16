public class TwoArraysSameNum 
{
    public static final int ARRAY_RANGE = 10;
    public static final int VALUE_RANGE = 10;
    
    public static void main(String[] args) 
    {
        Thread.currentThread().setPriority(1);
        int[] a = {4, 3, 1, 2};
        int[] b = {4, 4, 1, 1, 1, 4, 2, 2, 1};
        printArray(compare(a,b));
        generateAndCompare();
    }   
    
    public static int[] compare(int[] a, int[] b)
    {
        int[] output = new int[a.length * 2];
        for (int i = 0; i < a.length; i++)
        {
            output[i] = a[i];
            for (int num : b)
                if (output[i] == num) output[i + a.length]++;
        }
        return output;
    }
    
    public static void printArray(int[] array)
    {
        for (int i = 0; i < array.length; i++)
        {
            if (i == array.length / 2) System.out.println();
            System.out.print(array[i] + " ");
        }
        System.out.println();
    }
    
    public static void printArray(int[] array, boolean standard)
    {
        if (array.length < 21)
            for (int a : array)
                System.out.print(a + " ");
        else
        {
            for (byte i = 0; i < 10; i++)
                System.out.print(array[i] + " ");
            System.out.print("... ");
            for (int i = array.length - 10; i < array.length; i++)
                System.out.print(array[i] + " ");
        }
        System.out.println();
    }
    
    public static void generateAndCompare()
    {
        boolean isFound = false;
        int counter = 0;
        while(isFound == false)
        {
            int[] a = new int[getRandomValue(ARRAY_RANGE, true)];
            int[] b = new int[getRandomValue(ARRAY_RANGE, true)];
            int[] result = new int[a.length * 2];
            setRandomArray(a, VALUE_RANGE);
            setRandomArray(b, VALUE_RANGE);
            result = compare(a,b);
            for(int i = a.length; i < result.length; i++)
            {
                if (result[i] != 0) 
                {
                    isFound = true;
                    break;
                }
            }
            if (isFound)
            {
                System.out.print("Массив A: ");
                printArray(a, true);
                System.out.print("Массив B: ");
                printArray(b, true);
                printArray(result);
                System.out.printf("Найден на итерации: %d%n", counter);
            }
            counter++;
        }
    }
    
    public static int getRandomValue(int range) { return new java.util.Random().nextInt(range * 2 + 1) - range; }
    
    public static int getRandomValue(int range, boolean isPositive) { return new java.util.Random().nextInt(range + 1); }
    
    public static void setRandomArray(int[] array, int range)
    {
        for (int i = 0; i < array.length; i++) 
            array[i] = getRandomValue(range);
    }
}
