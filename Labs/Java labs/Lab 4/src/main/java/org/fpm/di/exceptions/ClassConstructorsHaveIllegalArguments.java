package org.fpm.di.exceptions;

import java.lang.reflect.Constructor;
import java.util.ArrayList;

public class ClassConstructorsHaveIllegalArguments extends ContainersException
{
    public ClassConstructorsHaveIllegalArguments(ArrayList<Constructor<?>> constructors)
    {
        super("Classes constructors " + constructors.toString() + " have illegal arguments");
    }
}
