package oop.lab2;

import java.util.*;

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
            int result = 0;
            List <String> SplitComas = Arrays.stream(numbers.split(",")).toList();
            List <String> Final = new Vector<>();
            for (String s: SplitComas)
            {
                String[] temp = s.split("\n");
                Final.addAll(Arrays.asList(temp));
            }
            for (String s : Final)
            {
                result += Integer.parseInt(s);
            }
            return result;
        }
    }
}
