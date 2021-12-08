package org.fpm.di.exceptions;

public class ContainerHasNoAccessibleConstructorsException extends ContainersException
{
    public ContainerHasNoAccessibleConstructorsException(Class<?> clazz)
    {
        super("Class " + clazz.getName() + " has no usable constructors.\n");
    }
}
