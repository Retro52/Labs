package org.fpm.di.example.classes;

import javax.inject.Inject;

public class ClassWithConstructorException
{
    @Inject
    public ClassWithConstructorException()
    {
        throw new RuntimeException("");
    }
}
