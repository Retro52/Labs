package com.company;

import java.io.File;
import java.io.*;
import java.util.Scanner;

public class Main
{
    public static void main(String[] argv) throws IOException
    {
        CLAHandler cla = new CLAHandler();
        String[] Args = cla.CheckArguments(argv);
        cla.ProcessArguments(Args);

        FilesReader readfile = new FilesReader();
        FileInputStream fis = readfile.TryToReadFile(Args[0]);
        if (fis == null)
        {
            return;
        }

        FilesWriter writefile = new FilesWriter();
        FileOutputStream fos = writefile.OpenAndCreateIfNotExists(Args[1]);
        if (fos == null)
        {
            return;
        }

        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));
        BufferedReader bf = new BufferedReader(new FileReader(Args[0]));

        while (true)
        {
            String result = readfile.ReadFileLines(bf, Args[2], Args[3]);
            if (result != null)
            {
                int code = writefile.WriteStringToFile(result, bw);
                if (code == 1)
                {
                    return;
                }
            }
            else
            {
                System.out.println("Program successfully finished");
                break;
            }
        }

        try { fis.close(); } catch(Throwable t) { /* ensure close happens */ }
        try { fos.close(); } catch(Throwable t) { /* ensure close happens */ }
        try { bw.close(); } catch(Throwable t) { /* ensure close happens */ }
    }
}

class FilesReader
{
    public FileInputStream TryToReadFile(String fname)
    {
        try
        {
            //constructor of file class having file as argument
            File file = new File(fname);
            return new FileInputStream(file);
        }
        catch(Exception e)
        {
            System.out.println("Could`t open file  " + fname + ". Check if file is in project directory and try again.");
            return null;
        }
    }

    public String CountChars(String s, String delimiter, String separator)
    {
        StringBuilder result = new StringBuilder();
        boolean InBrackets = false;
        int CurLength = 0;

        for (int i = 0; i < s.length() - 1; i++)
        {

            if (s.toCharArray()[i] == delimiter.charAt(0))
            {

                if (!InBrackets)
                {
                    result.append(CurLength);
                    result.append(separator);
                    CurLength = 0;
                    i++;
                }

                if (InBrackets && s.toCharArray()[i - 1] == '"')
                {
                    result.append(CurLength);
                    result.append(separator);
                    InBrackets = false;
                    CurLength = 0;
                    i++;
                }
            }

            if (s.toCharArray()[i] == '"')
            {

                if (CurLength == 0)
                {
                    i++;
                    InBrackets = true;
                }

                else if (s.toCharArray()[i + 1] == '"')
                {
                    i++;
                }

                else if (s.toCharArray()[i + 1] == delimiter.charAt(0) && InBrackets)
                {
                    result.append(CurLength);
                    result.append(separator);
                    InBrackets = false;
                    CurLength = 0;
                    i += 2;
                }
            }
            CurLength++;
        }

        if (s.toCharArray()[s.length() - 1] == '"' && InBrackets)
        {
            CurLength--;
        }

        result.append(CurLength + 1);

        return result.toString();
    }

    public String ReadFileLines(BufferedReader bf, String delimiter, String separator)
    {
        String read = null, result;

        if (Runtime.getRuntime().freeMemory() < 8192)
        {
            System.out.println("Not enough memory for buffer");
            return null;
        }

        try
        {
            read = bf.readLine();
        }
        catch(IOException e)
        {
            System.out.println("Unknown BufferReader error");
        }
        if (read != null)
        {
            result = CountChars(read, delimiter, separator);
            return result;
        }
        else
        {
            return null;
        }
    }
}

class FilesWriter
{
    public int WriteStringToFile(String s, BufferedWriter bw)
    {
        try
        {
            bw.write(s);
            bw.newLine();
            bw.flush();
            return 0;
        }
        catch (IOException e)
        {
            System.out.println("Error while writing to file");
            System.err.println(e.getMessage());
            return 1;
        }
    }

    public FileOutputStream OpenAndCreateIfNotExists(String fname)
    {
        File file = new File(fname);
        try
        {
            file.createNewFile();
        }
        catch (IOException e)
        {
            System.out.println("File for writing was not opened for unknown reason. Try to re-run program");
        }
        try
        {
            return new FileOutputStream(file,false);
        }
        catch (FileNotFoundException e)
        {
            System.out.println("File for writing was not opened for unknown reason. Try to re-run program");
            return null;
        }
    }
}

class CLAHandler
{
    public String[] CheckArguments(String[] argv)
    {
        String[] result = new String[4];

        int args = argv.length;

        switch (args)
        {
            case 1 -> result[0] = argv[0];
            case 2 ->
                    {
                        result[0] = argv[0];
                        result[1] = argv[1];
                    }
            case 3 ->
                    {
                        result[0] = argv[0];
                        result[1] = argv[1];
                        if (argv[2].length() > 1)
                        {
                            System.out.println("Given delimiter is longer than one character, delimiters longer than 1 char are not supported");
                        }
                        else
                        {
                            result[2] = argv[2];
                        }
                    }
            case 4 ->
                    {
                        result[0] = argv[0];
                        result[1] = argv[1];
                        if (argv[2].length() > 1)
                        {
                            System.out.println("Given delimiter is longer than one character, delimiters longer than 1 char are not supported");
                        }
                        else
                        {
                            result[2] = argv[2];
                        }

                        if (argv[3].length() > 1)
                        {
                            System.out.println("Given separator is longer than one character, delimiters longer than 1 char are not supported");
                        }
                        else
                        {
                            result[3] = argv[2];
                        }
                    }
            default ->
                    {
                    }
        }
        return result;
    }

    public void ProcessArguments(String[] CheckedArgv)
    {
        Scanner scanner = new Scanner(System.in);

        if (CheckedArgv[0] == null)
        {
            System.out.println("Enter path to *.csv file: ");
            CheckedArgv[0] = scanner.nextLine();
        }

        if (CheckedArgv[1] == null)
        {
            System.out.println("Enter path to output file: ");
            CheckedArgv[1] = scanner.nextLine();
        }

        while (CheckedArgv[2] == null)
        {
            System.out.println("Enter delimiter: ");
            String check = scanner.next();
            if (check.length() > 1)
            {
                System.out.println("Delimiters with more than one character are not supported for now, try again");
            }
            else
            {
                CheckedArgv[2] = check;
                break;
            }
        }

        while (CheckedArgv[3] == null)
        {
            System.out.println("Enter separator: ");
            String check = scanner.next();
            if (check.length() > 1)
            {
                System.out.println("Separators with more than one character are not supported for now, try again");
            }
            else
            {
                CheckedArgv[3] = check;
                break;
            }
        }
    }
}
