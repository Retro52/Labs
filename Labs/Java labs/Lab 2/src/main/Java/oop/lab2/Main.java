package oop.lab2;

import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class StringCalculator
{
    public static int Add(String numbers) throws IllegalArgumentException
    {
        String delimiter = ",";
        if (numbers.startsWith("//"))
        {
            if (numbers.charAt(2) == '[')
            {
                Pattern pattern = Pattern.compile("//\\[.+\n");
                Matcher matcher = pattern.matcher(numbers);
                while (matcher.find())
                {
                    delimiter = numbers.substring(matcher.start(), matcher.end());
                    numbers = numbers.replace(delimiter, "");
                    delimiter = delimiter.replace("//[", "").replace("]\n", "");
                }
            }
            else
            {
                delimiter = "" + numbers.charAt(2);
                numbers = numbers.replace("//" + delimiter + "\n", "");
            }
        }
        if (numbers.length() == 0)
        {
            return 0;
        }
        else
        {

            int result = 0;
            delimiter = ProceedDelimiter(delimiter);
            List <String> SplitComas = Arrays.stream(numbers.split(String.valueOf(delimiter))).toList();
            List <String> Final = new Vector<>();
            List<Integer> negatives = new Vector<>();
            for (String s: SplitComas)
            {
                String[] temp = s.split("\n");
                Final.addAll(Arrays.asList(temp));
            }
            for (String s : Final)
            {
                int num = Integer.parseInt(s);
                num = (num > 1000) ? 0 : num;
                if (num < 0)
                {
                    negatives.add(num);
                }

                result += num;

            }
            if (negatives.size() > 0)
            {
                throw new IllegalArgumentException(formErrorMessage(negatives));
            }
            else
            {
                return result;
            }
        }
    }

    private static String ProceedDelimiter(String delimiter)
    {
        StringBuilder result = new StringBuilder();
        for(int i = 0; i < delimiter.length(); i++)
        {
            char c = delimiter.charAt(i);
            if (c == '+' || c == '*' || c == '?' || c == '|' || c == '^' || c == '$')
            {
                result.append("\\").append(delimiter.charAt(i));
            }
            else
            {
                result.append(delimiter.charAt(i));
            }
        }
        return result.toString();
    }
    private static String formErrorMessage(List<Integer> negatives)
    {
        StringBuilder message = new StringBuilder("Negatives not allowed [");
        ListIterator<Integer> iterator = negatives.listIterator();
        message.append(iterator.next());
        while (iterator.hasNext()) message.append("; ").append(iterator.next());
        message.append(']');
        return message.toString();
    }
}
