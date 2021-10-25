package oop.lab2;

public class Main
{
    public static void main(String[] args)
    {
	// write your code here
    }
}

class StringCalculator
{
    public static int Add(String numbers)
    {
        if (numbers.length() == 0)
        {
            return 0;
        }

        else
        {
            int result = 0, i = 0;
            while(i < numbers.length())
            {
                if (numbers.charAt(i) == ',')
                {
                    break;
                }
                else
                {
                    i++;
                }
            }

            result += Integer.parseInt(numbers.substring(0, i));
            if (i < numbers.length() - 1) result += Integer.parseInt(numbers.substring(i + 1));
            return result;
        }
    }
}
