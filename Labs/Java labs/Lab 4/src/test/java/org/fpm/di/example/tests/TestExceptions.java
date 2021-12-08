package org.fpm.di.example.tests;

import org.fpm.di.containers.DefaultBinder;
import org.fpm.di.containers.DefaultContainer;
import org.fpm.di.containers.MutableContainer;
import org.fpm.di.example.classes.A;
import org.fpm.di.example.classes.ClassWithConstructorException;
import org.fpm.di.example.classes.ClassWithNoPublicConstructors;
import org.fpm.di.example.classes.UseA;
import org.fpm.di.exceptions.ClassConstructorsHaveIllegalArguments;
import org.fpm.di.exceptions.ContainerHasNoAccessibleConstructorsException;
import org.fpm.di.exceptions.ContainerInternalException;
import org.fpm.di.exceptions.ContainerReturnNotRegisteredException;
import org.junit.*;


public class TestExceptions
{
    @Before
    public void SetUp()
    {

    }

    @Test(expected = ContainerHasNoAccessibleConstructorsException.class)
    public void ShouldThrowContainerHasNoAccessibleConstructorsException()
    {
        DefaultBinder binder = new DefaultBinder();
        binder.bind(ClassWithNoPublicConstructors.class);
        MutableContainer container = new MutableContainer(binder);
        container.getComponent(ClassWithNoPublicConstructors.class);
    }

    @Test(expected = ContainerReturnNotRegisteredException.class)
    public void ShouldThrowContainerReturnNotRegisteredException()
    {
        MutableContainer container = new MutableContainer(new DefaultBinder());
        container.getComponent(String.class);
    }

    @Test(expected = ContainerInternalException.class)
    public void ShouldThrowContainerInternalException()
    {
        DefaultBinder binder = new DefaultBinder();
        binder.bind(ClassWithConstructorException.class);
        MutableContainer container = new MutableContainer(binder);
        container.getComponent(ClassWithConstructorException.class);
    }

    @Test(expected = ClassConstructorsHaveIllegalArguments.class)
    public void CheckNotRegisteredConstructorParams()
    {
        DefaultBinder binder = new DefaultBinder();
        binder.bind(UseA.class);

        DefaultContainer parent = new MutableContainer(binder);

        binder = new DefaultBinder();
        binder.bind(A.class);
        DefaultContainer child = new MutableContainer(binder);
        UseA obj = parent.getComponent(UseA.class);
    }

}
