package org.fpm.di.exceptions;

public class ContainersException extends RuntimeException
{
    public ContainersException(String message)
    {
        super("Container Exception: " + message);
    }
}
