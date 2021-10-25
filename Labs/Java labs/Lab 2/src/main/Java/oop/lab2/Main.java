package oop.lab2;

import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
        char delimiter = ',';
        if (numbers.startsWith("//"))
        {
            delimiter = numbers.charAt(2);
            Pattern pattern = Pattern.compile("//.\n");
            Matcher matcher = pattern.matcher(numbers);
            while (matcher.find())
            {
                numbers = numbers.replace(numbers.substring(matcher.start(), matcher.end()), "");
            }
        }
        if (numbers.length() == 0)
        {
            return 0;
        }

        else
        {

            int result = 0;
            List <String> SplitComas = Arrays.stream(numbers.split(String.valueOf(delimiter))).toList();
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
