package org.fpm.di.example.tests;

import org.fpm.di.containers.DefaultBinder;
import org.fpm.di.containers.MutableContainer;
import org.fpm.di.example.classes.ClassWithSpecialAnnotation;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestAnnotation
{
    @Before
    public void SetUp()
    {

    }

    @Test
    public void testIgnoreAccessModifiers()
    {
        DefaultBinder binder = new DefaultBinder();
        binder.bind(ClassWithSpecialAnnotation.class);
        MutableContainer m = new MutableContainer(binder);
        ClassWithSpecialAnnotation c = m.getComponent(ClassWithSpecialAnnotation.class);
        assertEquals(c.getClass(), ClassWithSpecialAnnotation.class);
    }
}
