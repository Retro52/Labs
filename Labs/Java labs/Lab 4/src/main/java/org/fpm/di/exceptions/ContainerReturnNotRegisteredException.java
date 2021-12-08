package org.fpm.di.exceptions;

public class ContainerReturnNotRegisteredException extends ContainersException
{
    public ContainerReturnNotRegisteredException(Class<?> clazz)
    {
        super("Required type " + clazz.getName() + " is not registered in container.");
    }
}
