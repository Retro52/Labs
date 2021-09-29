package com.company;

import java.io.File;
import java.io.*;
import java.util.Scanner;

public class Main
{
    public static void main(String[] argv) throws IOException
    {
        String FileToOpen = null, FileToWrite = null, delimiter = null, separator = null;

        // first arg - path to file for opening, second - path to file for writing, third one - delimiter, fourth - separator in final file
        int args = argv.length;

        switch (args)
        {
            case 1 -> FileToOpen = argv[0];
            case 2 ->
            {
                FileToOpen = argv[0];
                FileToWrite = argv[1];
            }
            case 3 ->
            {
                FileToOpen = argv[0];
                FileToWrite = argv[1];
                if (argv[2].length() > 1)
                {
                    System.out.println("Given delimiter is longer than one character, delimiters longer than 1 char are not supported");
                }
                else
                {
                    delimiter = argv[2];
                }
            }
            case 4 ->
            {
                FileToOpen = argv[0];
                FileToWrite = argv[1];
                if (argv[2].length() > 1)
                {
                    System.out.println("Given delimiter is longer than one character, delimiters longer than 1 char are not supported");
                }
                else
                {
                    delimiter = argv[2];
                }

                if (argv[3].length() > 1)
                {
                    System.out.println("Given separator is longer than one character, delimiters longer than 1 char are not supported");
                }
                else
                {
                    separator = argv[3];
                }
            }
            default ->
            {
            }
        }

        Scanner scanner = new Scanner(System.in);

        if (FileToOpen == null)
        {
            System.out.println("Enter path to *.csv file: ");
            FileToOpen = scanner.nextLine();
        }

        if (FileToWrite == null)
        {
            System.out.println("Enter path to output file: ");
            FileToWrite = scanner.nextLine();
        }

        while (delimiter == null)
        {
            System.out.println("Enter delimiter: ");
            String check = scanner.next();
            if (check.length() > 1)
            {
                System.out.println("Delimiters with more than one character are not supported for now, try again");
            }
            else
            {
                delimiter = check;
                break;
            }
        }

        while (separator == null)
        {
            System.out.println("Enter separator: ");
            String check = scanner.next();
            if (check.length() > 1)
            {
                System.out.println("Separators with more than one character are not supported for now, try again");
            }
            else
            {
                separator = check;
                break;
            }
        }

        FilesReader readfile = new FilesReader();
        FileInputStream fis = readfile.TryToReadFile(FileToOpen);
        if (fis == null)
        {
            System.exit(1);
        }

        FilesWriter writefile = new FilesWriter();
        FileOutputStream fos = writefile.OpenAndCreateIfNotExists(FileToWrite);
        if (fos == null)
        {
            System.exit(2);
        }

        int counter = 0;
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));

        while (true)
        {
            String result = readfile.ReadFileLines(FileToOpen, delimiter, separator, counter);
            if (result != null)
            {
                writefile.WriteStringToFile(result, bw);
                counter++;
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

        if (s.toCharArray()[s.length() - 1] == '"')
        {
            CurLength--;
        }

        result.append(CurLength + 1);

        return result.toString();
    }

    public String ReadFileLines(String filePath, String delimiter, String separator, int line)
    {
        String read = null, result;
        int counter = 0;
        if (Runtime.getRuntime().freeMemory() < 8192)
        {
            System.out.println("Not enough memory for buffer. Wtf did you do to your computer");
            return null;
        }
        try(BufferedReader bf = new BufferedReader(new FileReader(filePath)))
        {
            while((read = bf.readLine()) != null && counter != line)
            {
                counter++;
            }
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
    public void WriteStringToFile(String s, BufferedWriter bw)
    {
        try
        {
            bw.write(s);
            bw.newLine();
            bw.flush();
        }
        catch (IOException e)
        {
            System.out.println("Error while writing to file");
            System.err.println(e.getMessage());
            System.exit(3);
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